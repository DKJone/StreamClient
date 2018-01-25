
#import "StreamClient.h"

#define BOOL
#include "DVRWrapper.h"


//
//int StreamClient::s_drawInitCount = 0;

@interface StreamClient()
{

}
@end

@implementation StreamClient

@synthesize logined = _logined;
@synthesize playing = _playing;
@synthesize realPaused = _realPaused;
@synthesize realDataSaving = _realDataSaving;
@synthesize talking = _talking;
@synthesize finding = _finding;
@synthesize replaying = _replaying;
@synthesize downloading = _downloading;
@synthesize nodeId = _nodeId;


-(instancetype)init
{
   self = [super init];
   //
   _logined = false;
   _playing = false;
   _realPaused = true;
   _realDataSaving = false;
   _talking = false;
   _finding = false;
   _replaying = false;
   loginHandle = 0;
   voiceHandle = 0;
   realplayHandle = 0;
   findHandle = 0;
   playbackHandle = 0;
   downloadHandle = 0;
   _nodeId = 0;
   uiView = NULL;
   imageView = NULL;

   return self;
}

-(void)dealloc
{
    [self stopVideo];

    [self logout];

#if(!__has_feature(objc_arc))
    [super dealloc];
#endif
}

- (NSString*)getLastError
{
	char szBuf[256] = "none";
    bool bRet = DVR_GetLastErrorText(szBuf,sizeof(szBuf)) ? true:false;
	if(bRet)
	{
		 return [NSString stringWithUTF8String:szBuf];
	}
	
	return [NSString stringWithUTF8String:"exception"];
}

//登录服务器
- (bool)login:(NSString*)serverIP serverPort:(int)serverPort userName:(NSString*)userName password:(NSString*)password
{
	if (_logined)
        return true;
	
	//库初始化
    if (!DVR_Init()) {
        return false;
    }
	
	DVR_LOGININFO loginInfo;
	memset(&loginInfo,0,sizeof(DVR_LOGININFO));
	strcpy(loginInfo.szDvrIP,[serverIP UTF8String]);
    loginInfo.usDvrPort = serverPort;
	strcpy(loginInfo.szDvrUserName,[userName UTF8String]);
	strcpy(loginInfo.szDvrPassword,[password UTF8String]);
	long tempLoginHandle = DVR_Login(&loginInfo);
	if(tempLoginHandle == -1) {
		DVR_Cleanup();

		return false;
	}
	
	loginHandle = tempLoginHandle + 1;
	_logined = true;

	return true;
}

//注销登录
- (void)logout
{
	//
    if (!_logined)
        return;
	
	DVR_Logout(loginHandle - 1);

    loginHandle = 0;
    _logined = false;

	DVR_Cleanup();
}

//打开一路实时视频
- (bool)startVideo:(int)nodeId streamOpenMode:(int)streamOpenMode view:(UIView*)view audioEnabled:(bool)audioEnabled
{
    if(s_drawInitCount == 0)
    {
        DVR_INITINFO initInfo;
        memset(&initInfo,0,sizeof(DVR_INITINFO));
        if(!DVR_DrawAreaInit(&initInfo))
            return false;
        else
            ++s_drawInitCount;
    }
    else
        ++s_drawInitCount;

    //
    DVR_CLIENTINFO clientInfo;
    memset(&clientInfo,0,sizeof(DVR_CLIENTINFO));
    clientInfo.lLinkMode = DVR_CONNECT_MODE_TCP;
    clientInfo.lVideoFlag = streamOpenMode;
    clientInfo.lChannel = nodeId;
    
    //判断传入窗口对象类型为UIView还是UIImageView
    if([view isKindOfClass:[UIImageView class]])
    {
        uiView = NULL;
        imageView = (UIImageView*)view;
    }
    else  //创建一个UIImageView用来绘图
    {
        uiView = view;
        imageView = [[UIImageView alloc] initWithFrame: CGRectMake(0, 0, view.frame.size.width, view.frame.size.height)];
        
        [imageView setBackgroundColor:[UIColor darkGrayColor]];
        imageView.contentMode = UIViewContentModeScaleAspectFit;
        [view addSubview: imageView];
        
        NSLog(@"wndId is UIView and UIImageView need to be created in iosimageview_create function!");
    }

    clientInfo.hPlayWnd = (DVR_HWND)NULL;

    //
    long tempRealplayHandle = DVR_OpenStream(loginHandle - 1,&clientInfo);
    if (tempRealplayHandle == -1) {
        return false;
    }

    //
    //__bridge :CF和OC对象转化时只涉及对象类型不涉及对象所有权的转化,因为在OC与CF的转化时只涉及到对象类型没有涉及到对象所有权的转化，所以上述代码不需要对CF的对象进行释放，即不需要添加CFRelease
    bool ret = DVR_StartVideo(tempRealplayHandle,(__bridge DVR_HWND)imageView);
    if (!ret) {
        DVR_CloseStream(tempRealplayHandle);
        return false;
    }

    realplayHandle = tempRealplayHandle + 1;
    _nodeId = nodeId;
    _playing = true;
    _realPaused = false;

    return true;
}

//停止一路实时视频显示
- (bool)stopVideo
{
    //
    if (!_playing)
        return false;

    //停止视频显示
    if (!_realPaused) {
        DVR_StopVideo(realplayHandle - 1);
        _realPaused = true;
    }

    //关闭流
    DVR_CloseStream(realplayHandle - 1);
    _playing = false;
    realplayHandle = 0;
    
    //
    if (uiView != NULL && imageView != NULL) {
        [imageView removeFromSuperview];
        imageView = nil;
    }

    return true;
}

//对一路实时视频抓图
- (bool)capturePictureJpeg:(NSString*)fullFileName
{
    //
    if (!_playing || _realPaused)
        return false;

    //
    if (!DVR_CapturePicture(realplayHandle - 1, [fullFileName UTF8String])) {
#if(!__has_feature(objc_arc))
        [fullFileName release];
#endif
        return false;
    } else {
#if(!__has_feature(objc_arc))
        [fullFileName release];
#endif
        
        return true;
    }
}

//开始本地录像
- (bool)startSaveRealData:(NSString*)fullFileName
{
    //
    if (!_playing || _realPaused)
        return false;

    //
    if (!DVR_StartSaveRealData(realplayHandle - 1, [fullFileName UTF8String])) {
#if(!__has_feature(objc_arc))
        [fullFileName release];
#endif
        return false;
    } else {
#if(!__has_feature(objc_arc))
        [fullFileName release];
#endif
        _realDataSaving = true;

        return true;
    }
}

//停止本地录像
- (bool)stopSaveRealData
{
    //
    if (!_realDataSaving)
        return false;

    //
    if (!DVR_StopSaveRealData(realplayHandle - 1)) {
        return false;
    } else {
        _realDataSaving = false;

        return true;
    }
}

//开始语音对讲
- (bool)startVoiceCom:(int)nodeId voiceMode:(int)voiceMode
{
    //
    if (!_logined)
        return false;

    //
    DVR_VOICEINFO voiceInfo;
    voiceInfo.lChannel = (long)nodeId;
    voiceInfo.lMode = (long)voiceMode;
    long tempVoiceHandle = DVR_StartVoiceCom(loginHandle - 1,&voiceInfo,NULL,0);
    if (tempVoiceHandle == -1) {
        return false;
    } else {
        voiceHandle = tempVoiceHandle + 1;
        _talking = true;

        return true;
    }
}

//停止语音对讲
- (bool)stopVoiceCom
{
    //
    if (!_talking)
        return false;

    //
    if (!DVR_StopVoiceCom(voiceHandle - 1)) {
        return false;
    } else {
        _talking = false;
        voiceHandle = 0;

        return true;
    }
}

//云台控制
- (bool)ptzControl:(int)nodeId ptzCommand:(int)ptzCommand  ptzSpeed:(int)ptzSpeed
{
    //
    if (!_logined)
        return false;

    return DVR_PTZControl(loginHandle - 1,nodeId,ptzCommand,ptzSpeed) ? true:false;
}

//预置点控制
- (bool)presetControl:(int)nodeId presetCommand:(int)presetCommand  presetIndex:(int)presetIndex
{
    //
    if (!_logined)
        return false;

    return DVR_PTZPreset(loginHandle - 1,nodeId,presetCommand,presetIndex) ? true:false;
}

//查找文件
- (bool)findFile:(int)nodeId fileType:(int)fileType  startTime:(NSString*)startTime  stopTime:(NSString*)stopTime  fileSource:(int)fileSource
{
    //
    if (!_logined)
        return false;

    DVR_TIME dtStartTime;
    DVR_TIME dtStopTime;
    const char *nativeStartTime = [startTime UTF8String];
    const char *nativeStopTime = [stopTime UTF8String];
#if(!__has_feature(objc_arc))
    [startTime release];
    [stopTime release];
#endif
    //按照特定时间格式将字符串转换为时间类型
    char fmt[] = "%Y-%m-%d %H:%M:%S";
    struct tm tm1;
    if (strptime(nativeStartTime, fmt, &tm1) == NULL)
        goto end;
    else
    {
        dtStartTime.ulYear = tm1.tm_year;
        dtStartTime.ulMonth = tm1.tm_mon;
        dtStartTime.ulDay = tm1.tm_mday;
        dtStartTime.ulHour = tm1.tm_hour;
        dtStartTime.ulMinute = tm1.tm_min;
        dtStartTime.ulMinute = tm1.tm_sec;
    }

    if (strptime(nativeStopTime, fmt, &tm1) == NULL)
        goto end;
    else
    {
        dtStopTime.ulYear = tm1.tm_year;
        dtStopTime.ulMonth = tm1.tm_mon;
        dtStopTime.ulDay = tm1.tm_mday;
        dtStopTime.ulHour = tm1.tm_hour;
        dtStopTime.ulMinute = tm1.tm_min;
        dtStopTime.ulMinute = tm1.tm_sec;
    }

    long tempFindHandle = DVR_FindFile(loginHandle - 1,nodeId,fileType,&dtStartTime,&dtStopTime,fileSource);
    if(tempFindHandle == -1)
        return false;

    findHandle = tempFindHandle + 1;
    _finding = true;
end:

    return _finding;
}

//关闭文件查找
- (bool)findClose
{
    if(!_finding)
        return false;

    bool bRet = DVR_FindClose(findHandle - 1) ? true:false;
    _finding = false;

    return bRet;
}

//查找下一个文件
- (NSString*)findNextFile
{
    char szFileInfo[1024] = "\0";
    if(!_finding)
        return [NSString stringWithUTF8String:szFileInfo];

    DVR_FIND_DATA findData;
    memset(&findData,0,sizeof(DVR_FIND_DATA));
    long iRet = DVR_FindNextFile(findHandle - 1,&findData);
    if(iRet == DVR_FILE_SUCCESS)
    {
        snprintf(szFileInfo,
                 sizeof(szFileInfo),
                 "{\"filename\":\"%s\",\"nodeid\":%lld,\"starttime:\":\"%04lu-%02lu-%02lu %02lu:%02lu:%02lu\",\"stoptime:\":\"%04lu-%02lu-%02lu %02lu:%02lu:%02lu\",\"filetype\":%lu,\"filesize\":%lu}",
                 findData.szFileName,
                 findData.lChannel,
                 findData.timeStart.ulYear,
                 findData.timeStart.ulMonth,
                 findData.timeStart.ulDay,
                 findData.timeStart.ulHour,
                 findData.timeStart.ulMinute,
                 findData.timeStart.ulSecond,
                 findData.timeStop.ulYear,
                 findData.timeStop.ulMonth,
                 findData.timeStop.ulDay,
                 findData.timeStop.ulHour,
                 findData.timeStop.ulMinute,
                 findData.timeStop.ulSecond,
                 findData.ulFileType,
                 findData.unFileSize);
    }

    return [NSString stringWithUTF8String:szFileInfo];
}

//按时间回放
- (bool)playbackByTime:(int)nodeId fileType:(int)fileType  startTime:(NSString*)startTime  stopTime:(NSString*)stopTime view:(UIView*)view fileSource:(int)fileSource
{
    //
    if (!_logined)
        return false;

    DVR_TIME dtStartTime;
    DVR_TIME dtStopTime;
    const char *nativeStartTime = [startTime UTF8String];
    const char *nativeStopTime = [stopTime UTF8String];
#if(!__has_feature(objc_arc))
    [startTime release];
    [stopTime release];
#endif
    //按照特定时间格式将字符串转换为时间类型
    char fmt[] = "%Y-%m-%d %H:%M:%S";
    struct tm tm1;
    if (strptime(nativeStartTime, fmt, &tm1) == NULL)
        goto end;
    else
    {
        dtStartTime.ulYear = tm1.tm_year;
        dtStartTime.ulMonth = tm1.tm_mon;
        dtStartTime.ulDay = tm1.tm_mday;
        dtStartTime.ulHour = tm1.tm_hour;
        dtStartTime.ulMinute = tm1.tm_min;
        dtStartTime.ulMinute = tm1.tm_sec;
    }

    if (strptime(nativeStopTime, fmt, &tm1) == NULL)
        goto end;
    else
    {
        dtStopTime.ulYear = tm1.tm_year;
        dtStopTime.ulMonth = tm1.tm_mon;
        dtStopTime.ulDay = tm1.tm_mday;
        dtStopTime.ulHour = tm1.tm_hour;
        dtStopTime.ulMinute = tm1.tm_min;
        dtStopTime.ulMinute = tm1.tm_sec;
    }

    long tempPlaybackHandle = DVR_PlayBackByTime(loginHandle - 1,nodeId,&dtStartTime,&dtStopTime,(__bridge DVR_HWND)view,fileSource);
    if(tempPlaybackHandle == -1)
        return false;

    playbackHandle = tempPlaybackHandle + 1;
    _replaying = true;
end:

    return _replaying;
}

//停止回放
- (bool)stopPlayback
{
    if(!_replaying)
        return false;

    bool bRet = DVR_StopPlayBack(playbackHandle - 1) ? true:false;
    _replaying = false;

    return bRet;
}

//回放控制
- (bool)playbackControl:(long)controlCommand inValue:(int)inValue
{
    if(!_replaying)
        return false;

    int outValue = 0;
    bool bRet = DVR_PlayBackControl(playbackHandle - 1,controlCommand,inValue,&outValue) ? true:false;

    return bRet;
}

//获取回放控制状态(-1:取得失败; 其他值为正常值)
- (int)playbackGetControl:(int)controlCommand
{
    if(!_replaying)
        return -1;

    int inValue = 0;
    int outValue = 0;
    bool bRet = DVR_PlayBackControl(playbackHandle - 1,controlCommand,inValue,&outValue) ? true:false;
    if(bRet)
        return outValue;
    else
        return -1;
}

//根据时间下载文件
- (bool)getFileByTime:(int)nodeId fileType:(int)fileType  startTime:(NSString*)startTime  stopTime:(NSString*)stopTime fileName:(NSString*)fileName fileSource:(int)fileSource
{
    //
    if (!_logined)
        return false;

    DVR_TIME dtStartTime;
    DVR_TIME dtStopTime;
    const char *nativeStartTime = [startTime UTF8String];
    const char *nativeStopTime = [stopTime UTF8String];
    const char *nativeFileName = [fileName UTF8String];
    //按照特定时间格式将字符串转换为时间类型
    char fmt[] = "%Y-%m-%d %H:%M:%S";
    struct tm tm1;
    if (strptime(nativeStartTime, fmt, &tm1) == NULL)
        goto end;
    else
    {
        dtStartTime.ulYear = tm1.tm_year;
        dtStartTime.ulMonth = tm1.tm_mon;
        dtStartTime.ulDay = tm1.tm_mday;
        dtStartTime.ulHour = tm1.tm_hour;
        dtStartTime.ulMinute = tm1.tm_min;
        dtStartTime.ulMinute = tm1.tm_sec;
    }

    if (strptime(nativeStopTime, fmt, &tm1) == NULL)
        goto end;
    else
    {
        dtStopTime.ulYear = tm1.tm_year;
        dtStopTime.ulMonth = tm1.tm_mon;
        dtStopTime.ulDay = tm1.tm_mday;
        dtStopTime.ulHour = tm1.tm_hour;
        dtStopTime.ulMinute = tm1.tm_min;
        dtStopTime.ulMinute = tm1.tm_sec;
    }

    long tempDownloadHandle = DVR_GetFileByTime(loginHandle - 1,nodeId,&dtStartTime,&dtStopTime,(char*)nativeFileName);
    if(tempDownloadHandle == -1)
        return false;

    downloadHandle = tempDownloadHandle + 1;
    _downloading = true;

end:
    return _downloading;
}

//停止下载文件
- (bool)stopGetFile
{
    if(!_downloading)
        return false;

    bool bRet = DVR_StopGetFile(downloadHandle - 1) ? true:false;
    _downloading = false;

    return bRet;
}

//返回下载进度(-1:取得失败; 0--100下载进度)
- (int)getDownloadPos
{
    if(!_downloading)
        return -1;

    return (int)DVR_GetDownloadPos(downloadHandle - 1);
}

@end
