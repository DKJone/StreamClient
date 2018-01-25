#ifndef STREAM_CLIENT_H
#define STREAM_CLIENT_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface StreamClient: NSObject
{
	bool _logined;

    bool _playing;

    bool _realPaused;

    bool _realDataSaving;

    bool _talking;

    bool _finding;

    bool _replaying;

    bool _downloading;

    long loginHandle;

    long voiceHandle;

    long realplayHandle;

    long findHandle;

    long playbackHandle;

    long downloadHandle;

    int _nodeId;

    UIView *uiView;
    
    UIImageView *imageView;

    int s_drawInitCount;
}

@property (nonatomic, readonly) bool logined;

@property (nonatomic, readonly) bool playing;

@property (nonatomic, readonly) bool realPaused;

@property (nonatomic, readonly) bool realDataSaving;

@property (nonatomic, readonly) bool talking;

@property (nonatomic, readonly) bool finding;

@property (nonatomic, readonly) bool replaying;

@property (nonatomic, readonly) bool downloading;

@property (nonatomic, readonly) int nodeId;

//返回最后一次错误号
- (NSString*)getLastError;

//登录服务器
- (bool)login:(NSString*)serverIP serverPort:(int)serverPort userName:(NSString*)userName password:(NSString*)password;

//注销登录
- (void)logout;

//打开一路实时视频
- (bool)startVideo:(int)nodeId streamOpenMode:(int)streamOpenMode view:(UIView*)view audioEnabled:(bool)audioEnabled;

//停止一路实时视频显示
- (bool)stopVideo;

//对一路实时视频抓图
- (bool)capturePictureJpeg:(NSString*)fullFileName;

//开始本地录像
- (bool)startSaveRealData:(NSString*)fullFileName;

//停止本地录像
- (bool)stopSaveRealData;

//开始语音对讲
- (bool)startVoiceCom:(int)nodeId voiceMode:(int)voiceMode;

//停止语音对讲
- (bool)stopVoiceCom;

//云台控制
- (bool)ptzControl:(int)nodeId ptzCommand:(int)ptzCommand  ptzSpeed:(int)ptzSpeed;

//预置点控制
- (bool)presetControl:(int)nodeId presetCommand:(int)presetCommand  presetIndex:(int)presetIndex;

//查找文件
- (bool)findFile:(int)nodeId fileType:(int)fileType  startTime:(NSString*)startTime  stopTime:(NSString*)stopTime  fileSource:(int)fileSource;

//关闭文件查找
- (bool)findClose;

//查找下一个文件
- (NSString*)findNextFile;

//按时间回放
- (bool)playbackByTime:(int)nodeId fileType:(int)fileType  startTime:(NSString*)startTime  stopTime:(NSString*)stopTime view:(UIView*)view fileSource:(int)fileSource;

//停止回放
- (bool)stopPlayback;

//回放控制
- (bool)playbackControl:(int)controlCommand inValue:(int)inValue;

//获取回放控制状态(-1:取得失败; 其他值为正常值)
- (int)playbackGetControl:(int)controlCommand;

//根据时间下载文件
- (bool)getFileByTime:(int)nodeId fileType:(int)fileType  startTime:(NSString*)startTime  stopTime:(NSString*)stopTime fileName:(NSString*)fileName fileSource:(int)fileSource;

//停止下载文件
- (bool)stopGetFile;

//返回下载进度(-1:取得失败; 0--100下载进度)
- (int)getDownloadPos;
  
@end

#endif
