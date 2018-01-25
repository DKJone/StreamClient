/*********编码设备统一接口 版本2.2.2017.0608***************/
/*更新说明：
*1.新增加信号量上报消息DVR_MESSAGE_SWITCH_REPORT和信号量上报结构体DVR_SWITCH_REPORT定义；
*2.统一调整环境量术语为模拟量。
*/


#ifndef DVRWRAPPER_H
#define DVRWRAPPER_H

#include "DVRWrapperDef.h"
#include "DVRPlayer.h"
#include "PlatformDef.h"

#ifdef __cplusplus
extern "C" {
#endif

//获取错误信息代码
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetLastError(unsigned int* puiErrorCode);

//获取错误信息描述
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetLastErrorText(char* pBuf,unsigned int uiBufSize);

//获取设备ID使用模式
DVRWRAPPERSHARED_EXPORT unsigned long DVR_GetDevIDMode();

//初始化
DVRWRAPPERSHARED_EXPORT BOOL DVR_Init();

//反初始化
DVRWRAPPERSHARED_EXPORT BOOL DVR_Cleanup();

//登录
DVRWRAPPERSHARED_EXPORT long DVR_Login(PDVR_LOGININFO pLoginInfo);

//登录
DVRWRAPPERSHARED_EXPORT long DVR_Login_V20(PDVR_LOGININFO_V20 pLoginInfo);

//注销
DVRWRAPPERSHARED_EXPORT BOOL DVR_Logout(long lUserHandle);

//重启
DVRWRAPPERSHARED_EXPORT BOOL DVR_Reboot(long lUserHandle);

//关机
DVRWRAPPERSHARED_EXPORT BOOL DVR_ShutDown(long lUserHandle);

//初始化画布
DVRWRAPPERSHARED_EXPORT BOOL DVR_DrawAreaInit(PDVR_INITINFO pInitInfo);

//释放画布
DVRWRAPPERSHARED_EXPORT BOOL DVR_DrawAreaRelease();

//设置画布区域
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetDrawArea(int iWidth, int iHeight);

//打开流
DVRWRAPPERSHARED_EXPORT long DVR_OpenStream(long lUserHandle, PDVR_CLIENTINFO lpClientInfo);

//关闭流
DVRWRAPPERSHARED_EXPORT BOOL DVR_CloseStream(long lStreamHandle);

//设置播放窗体
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetPlayHWND(long lStreamHandle, DVR_HWND hPlayWnd);

//设置播放缩放窗口区域，实现局部放大
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetPlayRegion(long lStreamHandle, DVR_RECT *pRegion, BOOL bEnable);

//设置播放缩放窗口区域，实现局部放大(pRegion指针为空表示恢复原始大小)
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetDisplayZoom(long lStreamHandle,DVR_HWND hPlayWnd, DVR_RECT *pRegion);

//播放流
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartVideo(long lStreamHandle, DVR_HWND hPlayWnd);

//停止播放流
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopVideo(long lStreamHandle);

//播放音频流
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartAudio(long lStreamHandle);

//停止音频流
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopAudio(long lStreamHandle);

//设置音频流音量(范围0--255)
DVRWRAPPERSHARED_EXPORT BOOL DVR_AudioVolume(long lStreamHandle, int iVolume);

//获取视频参数(范围0--100)
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetVideoEffect(long lStreamHandle, long *pBrightness, long *pContrast, long *pSaturation, long *pHue);

//设置视频参数(0--100)
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetVideoEffect(long lStreamHandle, long lBrightness, long lContrast, long lSaturation, long lHue);

//设置流回调函数
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetRealDataCallBack(long lStreamHandle, DVR_REALDATA_CALLBACK fnRealDataCallBack, unsigned long ulUserData);

//获取视频丢包率(0-100%)
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetLostRate(long lStreamHandle, unsigned long *pRate);

//设置实时视频图像显示缓冲帧数(缺省为15)
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetPainterBuf(long lStreamHandle,unsigned long ulFrameCount);

//获取实时视频图像显示缓冲帧数
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetPainterBuf(long lStreamHandle,unsigned long* pFrameCount);
	
//抓图
DVRWRAPPERSHARED_EXPORT BOOL DVR_CapturePicture(long lStreamHandle, char *szPicFileName);

//抓图
DVRWRAPPERSHARED_EXPORT BOOL DVR_CapturePictureJpeg(long lStreamHandle, long lQuality, char *szPicFileName);

//开始本地录像
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartSaveRealData(long lStreamHandle, char *szFileName);

//结束本地录像
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopSaveRealData(long lStreamHandle);

//开始语音对讲
DVRWRAPPERSHARED_EXPORT long DVR_StartVoiceCom(long lUserHandle, PDVR_VOICEINFO pVoiceInfo, DVR_VOICEDATA_CALLBACK fnVoiceDataCallback, unsigned long ulUserData);

//停止语音对讲
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopVoiceCom(long lVoiceHandle);

//启动语音转发
DVRWRAPPERSHARED_EXPORT long DVR_StartVoiceCom_MR(long lUserHandle, PDVR_VOICEINFO pVoiceInfo, DVR_VOICEDATA_CALLBACK fnVoiceDataCallback, unsigned long ulUserData);

//转发语音数据
DVRWRAPPERSHARED_EXPORT BOOL DVR_VoiceComSendData(long lVoiceHandle, char *pBuf, long lBufSize);

//云台控制
DVRWRAPPERSHARED_EXPORT BOOL DVR_PTZControl(long lUserHandle, DVR_DEV_ID lChannel, unsigned long ulPTZCommand, unsigned long ulSpeed);

//扩展云台控制
DVRWRAPPERSHARED_EXPORT BOOL DVR_PTZControlEx(long lUserHandle, DVR_DEV_ID lChannel, PDVR_PTZCTLEX pInfo);

//虚拟云台控制
DVRWRAPPERSHARED_EXPORT BOOL DVR_VPTZControl(long lStreamHandle, unsigned long ulPTZCommand, unsigned long ulSpeed);

//预置点控制（预置点序号从1开始）
DVRWRAPPERSHARED_EXPORT BOOL DVR_PTZPreset(long lUserHandle, DVR_DEV_ID lChannel, unsigned long ulPTZPresetCmd, unsigned long ulPresetIndex);

//设置信号量输出（报警输出端口,从1开始,0表示全部;lDigitalValue:报警输出信号量数值,0-分开,1-闭合,2-脉冲闭合,3-脉冲分开）
//报警输出状态和信号量值是不同的概念，闭合、分开是两种信号量状态，闭合不代表一定是打开设备，常闭模式下分开才是打开设备
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetAlarmOut(long lUserHandle, DVR_DEV_ID lAlarmOutPort, long lDigitalValue);

//设置模拟量输出
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetEnvAlarmOut(long lUserHandle, DVR_DEV_ID lAlarmOutPort, double fEnvValue);

//查找文件
#ifdef __cplusplus
DVRWRAPPERSHARED_EXPORT long DVR_FindFile(long lUserHandle, DVR_DEV_ID lChannel, unsigned long ulFileType, PDVR_TIME pStartTime, PDVR_TIME pStopTime,long lFileSource = DVR_FILE_SOURCE_DVR);
#else
DVRWRAPPERSHARED_EXPORT long DVR_FindFile(long lUserHandle, DVR_DEV_ID lChannel, unsigned long ulFileType, PDVR_TIME pStartTime, PDVR_TIME pStopTime,long lFileSource);
#endif

//关闭文件查找
DVRWRAPPERSHARED_EXPORT BOOL DVR_FindClose(long lFindHandle);

//查找下一个文件(注意：返回值为查找状态，非句柄，请参考宏定义)
DVRWRAPPERSHARED_EXPORT long DVR_FindNextFile(long lFindHandle, PDVR_FIND_DATA pFindData);

//回放
#ifdef __cplusplus
DVRWRAPPERSHARED_EXPORT long DVR_PlayBack(long lUserHandle, PDVR_FIND_DATA pData, DVR_HWND hPlayWnd,long lFileSource = DVR_FILE_SOURCE_DVR);

//按文件名回放
DVRWRAPPERSHARED_EXPORT long DVR_PlayBackByName(long lUserHandle, char *szPlayBackFileName, DVR_HWND hPlayWnd,long lFileSource = DVR_FILE_SOURCE_DVR);

//按时间回放
DVRWRAPPERSHARED_EXPORT long DVR_PlayBackByTime(long lUserHandle, DVR_DEV_ID lChannel, PDVR_TIME pStartTime, PDVR_TIME pStopTime, DVR_HWND hPlayWnd,long lFileSource = DVR_FILE_SOURCE_DVR);
#else
DVRWRAPPERSHARED_EXPORT long DVR_PlayBack(long lUserHandle, PDVR_FIND_DATA pData, DVR_HWND hPlayWnd,long lFileSource);

//按文件名回放
DVRWRAPPERSHARED_EXPORT long DVR_PlayBackByName(long lUserHandle, char *szPlayBackFileName, DVR_HWND hPlayWnd,long lFileSource);

//按时间回放
DVRWRAPPERSHARED_EXPORT long DVR_PlayBackByTime(long lUserHandle, DVR_DEV_ID lChannel, PDVR_TIME pStartTime, PDVR_TIME pStopTime, DVR_HWND hPlayWnd,long lFileSource);
#endif

//停止回放
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopPlayBack(long lPlayBackHandle);

//回放控制
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackControl(long lPlayBackHandle, unsigned long ulControlCode, unsigned long ulInValue, unsigned long *pOutValue);

//取得回放视频参数
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackGetVideoEffect(long lPlayBackHandle, long *pBrightness, long *pContrast, long *pSaturation, long *pHue);

//设置回放视频参数
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackSetVideoEffect(long lPlayBackHandle, long lBrightness, long lContrast, long lSaturation, long lHue);

//设置回放回调
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetPlayBackDataCallBack(long lPlayBackHandle, DVR_REALDATA_CALLBACK fnRealDataCallBack, unsigned long ulUserData);

//获取视频丢包率(0-100%)
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackGetLostRate(long lPlayBackHandle, unsigned long *pRate);

//回放抓图
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackCaptureFile(long lPlayBackHandle, char *szFileName);

//回放抓图
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackCaptureJpeg(long lPlayBackHandle, long lQuality, char *szFileName);

//设置回放窗体
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackSetHWND(long lPlayBackHandle, DVR_HWND hPlayWnd);

//设置回放区域，实现局部放大
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackSetRegion(long lPlayBackHandle, DVR_RECT *pRegion, BOOL bEnable);

//设置回放缩放窗口区域，实现局部放大(pRegion指针为空表示恢复原始大小)
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackSetDisplayZoom(long lPlayBackHandle,DVR_HWND hPlayWnd, DVR_RECT *pRegion);

//设置录像回放视频图像显示缓冲帧数(缺省为15)
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackSetPainterBuf(long lPlayBackHandle,unsigned long ulFrameCount);

//获取录像回放视频图像显示缓冲帧数
DVRWRAPPERSHARED_EXPORT BOOL DVR_PlayBackGetPainterBuf(long lPlayBackHandle,unsigned long* pFrameCount);

//下载
DVRWRAPPERSHARED_EXPORT long DVR_GetFile(long lUserHandle, PDVR_FIND_DATA pData, char *szSavedFileName);

//根据名称下载文件
DVRWRAPPERSHARED_EXPORT long DVR_GetFileByName(long lUserHandle, char *szDVRFileName, char *szSavedFileName);

//根据时间下载文件
DVRWRAPPERSHARED_EXPORT long DVR_GetFileByTime(long lUserHandle, DVR_DEV_ID lChannel, PDVR_TIME pStartTime, PDVR_TIME pStopTime, char *szSavedFileName);

//停止文件下载
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopGetFile(long lGetFileHandle);

//获取下载的进度(-1:取得失败; 0--100下载进度)
DVRWRAPPERSHARED_EXPORT long DVR_GetDownloadPos(long lGetFileHandle);

//建立报警通道
DVRWRAPPERSHARED_EXPORT long DVR_SetupAlarmChan(long lUserHandle);

//关闭报警通道
DVRWRAPPERSHARED_EXPORT BOOL DVR_CloseAlarmChan(long lAlarmChanHandle);

//设置消息回调函数
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetDVRMessageCallBack(DVR_MESSAGE_CALLBACK fnMsgCB, unsigned long ulUserData);

//获取设备状态（llDevId为0，表示该类型所有设备）
//实际设备: ulDevType为DVR_DVR时，lChannel值忽略
//平台或代理：ulDevType为DVR_DVR时，lChannel值为平台、代理、实际DVR设备的全局编码
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetDeviceState(long lUserHandle, unsigned long ulDevType, DVR_DEV_ID lChannel, char *pOutBuffer, unsigned long ulOutBufferSize, unsigned long *pBytesReturned);

//流量查询（llSrcDevId为0，表示所有源设备）
//实际设备：该接口忽略；
//平台或代理：用以查询任意平台与平台、平台与设备之间的网络流量
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetFlow(long lUserHandle, DVR_DEV_ID llSrcDevId, DVR_DEV_ID llDestDevId,DVR_WORKSTATE *pWorkState);

//设备在线率查询（以天为单位，llDevId为0，表示该类型所有设备）
//实际设备: ulDevType为DVR_DVR时，lChannel值忽略
//平台或代理：ulDevType为DVR_DVR时，lChannel值为平台、代理、实际DVR设备的全局编码；ulDevType为区域时，则返回属于该区域下的所有类型设备
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetDeviceOnline(long lUserHandle, unsigned long ulDevType, DVR_DEV_ID lChannel, PDVR_TIME pQueryDate, char *pOutBuffer, unsigned long ulOutBufferSize, unsigned long *pBytesReturned);

//取得DVR配置
//实际设备: ulDevType为DVR_DVR时，lChannel值忽略
//平台或代理：ulDevType为DVR_DVR时，lChannel值为平台、代理、实际DVR设备的全局编码
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetDVRConfig(long lUserHandle, unsigned long ulCommand, DVR_DEV_ID lChannel, char *pOutBuffer, unsigned long ulOutBufferSize, unsigned long *pBytesReturned);

//设置DVR配置
//实际设备: ulDevType为DVR_DVR时，lChannel值忽略
//平台或代理：ulDevType为DVR_DVR时，lChannel值为平台、代理、实际DVR设备的全局编码
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetDVRConfig(long lUserHandle, unsigned long ulCommand, DVR_DEV_ID lChannel, char *pInBuffer, unsigned long ulInBufferSize);

//取得DVR配置(扩展)
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetDVRConfigEx(long lUserHandle, unsigned long ulCommand, PDVR_CONFIG_IN_PARAM pInParam, char *pOutBuffer, unsigned long ulOutBufferSize, unsigned long *pBytesReturned);

//设置DVR配置(扩展)
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetDVRConfigEx(long lUserHandle, unsigned long ulCommand, PDVR_CONFIG_IN_PARAM pInParam, char *pInBuffer, unsigned long ulInBufferSize);

//注册Draw回调函数
DVRWRAPPERSHARED_EXPORT BOOL DVR_RegisterDrawCallback(long lStreamHandle, DVR_DRAW_CALLBACK fnDrawCallback, unsigned long ulUserData);

//注册解码回调函数
DVRWRAPPERSHARED_EXPORT BOOL DVR_RegisterDecodeCallback(long lStreamHandle, DVR_DECODE_CALLBACK fnDecodeCallback, unsigned long ulUserData);

//开始DVR录像
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartDVRRecord(long lUserHandle, DVR_DEV_ID lChannel, long lRecordType);

//结束DVR录像
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopDVRRecord(long lUserHandle, DVR_DEV_ID lChannel);

//查找DVR log
DVRWRAPPERSHARED_EXPORT long DVR_FindDVRLog(long lUserHandle, DVR_DEV_ID lChannel, long lSelectMode, long lMajorType, long lMinorType, PDVR_TIME pStartTime, PDVR_TIME pStopTime);

//查找DVR 下一条log
DVRWRAPPERSHARED_EXPORT long DVR_FindNextLog(long lFindLogHandle, PDVR_LOG pLogInfo);

//关闭查找
DVRWRAPPERSHARED_EXPORT BOOL DVR_FindLogClose(long lFindLogHandle);

//开始监听
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartListen (char *szLocalIP, long lLocalPort);

//停止监听
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopListen();

//建立透明通道（网络型）
DVRWRAPPERSHARED_EXPORT long DVR_NetStart(long lUserHandle, DVR_NETDATA_CALLBACK fnNetDataCallBack, unsigned long ulUserData);

//通过透明通道向设备发送数据（网络型）(其中llDevId参数为目标网络设备的识别标识，内容可自定义）
DVRWRAPPERSHARED_EXPORT BOOL DVR_NetSend(long lNetHandle, DVR_DEV_ID llDevId, char *pBuffer, unsigned long ulBufSize);

//断开透明通道（网络型）
DVRWRAPPERSHARED_EXPORT BOOL DVR_NetStop(long lNetHandle);

//建立透明通道（串口型）
DVRWRAPPERSHARED_EXPORT long DVR_SerialStart(long lUserHandle, long lSerialPort, DVR_SERIALDATA_CALLBACK fnSerialDataCallBack, unsigned long ulUserData);

//通过透明通道向设备发送数据（串口型）
DVRWRAPPERSHARED_EXPORT BOOL DVR_SerialSend(long lSerialHandle, char *pBuffer, unsigned long ulBufSize);

//断开透明通道（串口型）
DVRWRAPPERSHARED_EXPORT BOOL DVR_SerialStop(long lSerialHandle);

//升级
//实际设备: ulDevType为DVR_DVR时，lChannel值忽略；ulDevType为DVR_CAMERA时，仅对IPC有效
//平台或代理：ulDevType为DVR_DVR时，lChannel值为平台、代理、实际DVR设备的全局编码；ulDevType为DVR_CAMERA时，仅对IPC有效
DVRWRAPPERSHARED_EXPORT long DVR_Upgrade(long lUserHandle,unsigned long ulDevType, DVR_DEV_ID llChannel, const char *pszFileName);

//返回升级状态(注意：返回值为升级状态，非句柄，请参考“任务执行状态”宏定义)
DVRWRAPPERSHARED_EXPORT int DVR_GetUpgradeState(long lUpgradeHandle);

//返回升级进度(0-100)
DVRWRAPPERSHARED_EXPORT unsigned int DVR_GetUpgradeProgress(long lUpgradeHandle);

//结束升级
DVRWRAPPERSHARED_EXPORT BOOL DVR_CloseUpgradeState(long lUpgradeHandle);

//获取配置文件(pszFullFileName参数含路径)
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetConfigFile(long lUserHandle,const char* pszFullFileName);

//导入配置文件(pszFullFileName参数含路径)
DVRWRAPPERSHARED_EXPORT BOOL DVR_SetConfigFile(long lUserHandle,const char* pszFullFileName);

//恢复缺省配置
DVRWRAPPERSHARED_EXPORT BOOL DVR_RestoreConfig(long lUserHandle);

//通过解析服务器返回Dvr地址和端口
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetDvrIPByResolveSvr(const char *pszServerIp, int iServerPort, const char* pszDvrName,
		char* pDvrSerialNumber, unsigned int uiDvrSerialLen, char* pDvrIp, unsigned int uiDvrIpBufSize,int* piPort);
		
//////////////////////////////////////////////////////////////////////////////////////////////////////
//智能分析相关类型定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//人脸识别相关
//增加人员信息
DVRWRAPPERSHARED_EXPORT BOOL DVR_AddPersonInfo(long lUserHandle,
                                               DVR_IVS_PERSON_INFO* pPersonInfo,
                                               DVR_IVS_PERSON_REGISTER_DATA_INFOS* pPersonRegisterDataInfos);
											   
//增加人员信息扩展
DVRWRAPPERSHARED_EXPORT BOOL DVR_AddPersonInfoEx(long lUserHandle,
                                                 DVR_IVS_PERSON_INFO* pPersonInfo,
												 DVR_IVS_PERSON_EXPAND_INFO* pPersonExpandInfo,
                                                 DVR_IVS_PERSON_REGISTER_DATA_INFOS* pPersonRegisterDataInfos);

//增加人员注册数据
DVRWRAPPERSHARED_EXPORT BOOL DVR_AddPersonRegisterData(long lUserHandle,
                                                       DVR_IVS_PERSON_REGISTER_DATA_INFO* pPersonRegisterDataInfo,
                                                       char* pPersonRegisterData);

//删除人员信息（0表示所有人员）
DVRWRAPPERSHARED_EXPORT BOOL DVR_DelPersonInfo(long lUserHandle,DVR_DEV_ID llPersonID,PDVR_TIME pStartTime, PDVR_TIME pStopTime);

//删除人员比对记录（0表示所有人员）
DVRWRAPPERSHARED_EXPORT BOOL DVR_DelPersonVerifyRecord(long lUserHandle, DVR_DEV_ID llPersonID,PDVR_TIME pStartTime, PDVR_TIME pStopTime);

//开始查找人员信息（0表示所有人员）
DVRWRAPPERSHARED_EXPORT long DVR_FindPersonInfo(long lUserHandle,DVR_DEV_ID llPersonID,PDVR_TIME pStartTime, PDVR_TIME pStopTime);

//查找下一条人员
//ulOutBufferSize为DVR_IVS_PERSON_REGISTER_DATA_INFOS* pPersonRegisterDataInfos指向缓冲区的长度
DVRWRAPPERSHARED_EXPORT long DVR_FindNextPersonInfo(long lPersonFindHandle,
                                                    DVR_IVS_PERSON_INFO* pPersonInfo,
                                                    DVR_IVS_PERSON_REGISTER_DATA_INFOS* pPersonRegisterDataInfos,
                                                    unsigned long ulOutBufferSize,
                                                    unsigned long *pBytesReturned);

//结束查找人员信息
DVRWRAPPERSHARED_EXPORT BOOL DVR_CloseFindPersonInfo(long lPersonFindHandle);

//获取人员注册数据
//ulOutBufferSize为char *pOutBuffer指向缓冲区的长度
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetPersonRegisterData(long lPersonFindHandle,
                                                       DVR_IVS_PERSON_REGISTER_DATA_INFO* pPersonRegisterDataInfo,
                                                       char *pOutBuffer,
                                                       unsigned long ulOutBufferSize,
                                                       unsigned long *pBytesReturned);

//开始查找人员比对记录（0表示所有人员）
DVRWRAPPERSHARED_EXPORT long DVR_FindPersonVerifyRecord(long lUserHandle,DVR_DEV_ID llPersonID,PDVR_TIME pStartTime, PDVR_TIME pStopTime);

//查找下一条人员比对记录
//ulOutBufferSize为DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS* pPersonVerfiyRecordDataInfos指向缓冲区的长度
DVRWRAPPERSHARED_EXPORT long DVR_FindNextPersonVerifyRecord(long lPersonVerifyRecordFindHandle,
                                                            DVR_IVS_PERSON_VERIFY_RECORD* pPersonVerifyRecord,
                                                            DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS* pPersonVerfiyRecordDataInfos,
                                                            unsigned long ulOutBufferSize,
                                                            unsigned long *pBytesReturned);

//结束查找人员比对记录
DVRWRAPPERSHARED_EXPORT BOOL DVR_CloseFindPersonVerifyRecord(long lPersonVerifyRecordFindHandle);

//获取人员比对记录数据的数据
//ulOutBufferSize为char *pOutBuffer指向缓冲区的长度
DVRWRAPPERSHARED_EXPORT BOOL DVR_GetPersonVerifyRecordData(long lUserHandle,
                                                           DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO* pPersonVerfiyRecordDataInfo,
                                                           char *pOutBuffer,
                                                           unsigned long ulOutBufferSize,
                                                           unsigned long *pBytesReturned);
														   					   
//启动终端采集(适用于手动启动模式终端，可以是一个终端的全部通道或某几个通道)
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartTerminalCapture(long lUserHandle,
                                                      DVR_IVS_TERMINAL_CAPTURE_CFG* pTerminalCaptureCfg);

//停止终端采集
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopTerminalCapture(long lUserHandle);
		
////////////////////////////////////////////////////////////////////////////////////////////////////////
//*********************中心比对服务接口****************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////////////
//启动人员比对任务（基于区域）
//uiPriority-比对优先级支持0-100，数值越大则优先级最高
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartVerifyTask(long lUserHandle,
                                                 DVR_DEV_ID llTaskID,
												 unsigned int uiPriority,				
												 DVR_IVS_REGION_INFOS* pRegionInfos);
												 
//启动人员比对任务（基于人员）
//uiPriority-比对优先级支持0-100，数值越大则优先级最高
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartVerifyTask2(long lUserHandle,
                                                  DVR_DEV_ID llTaskID,
												  unsigned int uiPriority,
												  DVR_IVS_PERSON_IDS* pPersonIDs);
												 
//发送人员比对数据
//首个比对数据偏移地址=DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS结构对象指针
//                     +sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS)
//                     +N*sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO)
//其中N为DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS结构对象中的iCount字段值，以下类推。
//比对数据数据长度为DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS结构包含的N个DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO结构对象iDataLen字段的数值之和
//数据总长度=sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS) 
//           +N*sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO)
//			 +DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO[1].iDataLen
//           +...
//			 +DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO[N].iDataLen 
DVRWRAPPERSHARED_EXPORT BOOL DVR_SendVerifyDataInfo(long lUserHandle,
                                                    DVR_DEV_ID llTaskID,
													char szHostIP[20],			
													int iHostChannelNum,
													char* pszCardNum,
													DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS* pPersonVerfiyRecordDataInfos);
													
//停止人员比对任务
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopVerifyTask(long lUserHandle,
                                                DVR_DEV_ID llTaskID);
												

////////////////////////////////////////////////////////////////////////////////////////////////////////
//*********************特征提取服务接口****************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////////////
//传入照片，申请生成特征数据
//uiPriority-比对优先级支持0-100，数值越大则优先级最高
//uiFeatureCount-生成特征数，只能填1或2。
//ulOutBufferSize为DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS* pPersonVerfiyRecordDataInfos指向缓冲区的长度
//申请特征数据后返回的DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS对象指针，不管返回特征数据数量多少，始终包含两个DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO对象
//首个特征数据偏移地址=DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS结构对象指针
//                     +sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS)
//                     +2*sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO)
//特征数据长度为DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS结构包含的两个DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO结构对象iDataLen字段的数值之和
//数据总长度=sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS) 
//           +2*sizeof(DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO)
//			 +DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO[1].iDataLen
//			 +DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO[2].iDataLen 
DVRWRAPPERSHARED_EXPORT BOOL DVR_RequestFaceFeatrue(long lUserHandle,
													unsigned int uiPriority,
													unsigned int uiFeatureCount,
												    char* pPhoto,
													unsigned int uiPhotoSize,
												    DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS* pPersonVerfiyRecordDataInfos,
												    unsigned long ulOutBufferSize,
                                                    unsigned long *pBytesReturned);												

#ifdef __cplusplus
}
#endif

#endif // DVRWRAPPER_H
