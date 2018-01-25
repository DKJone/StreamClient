/*********编码设备统一接口 版本2.2.2017.0608***************/
/*更新说明：
*1.新增加信号量上报消息DVR_MESSAGE_SWITCH_REPORT和信号量上报结构体DVR_SWITCH_REPORT定义；
*2.统一调整环境量术语为模拟量。
*/

#ifndef DVRPLAYER_H
#define DVRPLAYER_H

#include "DVRWrapperDef.h"

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//以下为播放库接口
//初始化播放库
DVRWRAPPERSHARED_EXPORT BOOL PLAY_DrawAreaInit(PDVR_INITINFO pInitInfo);

//反初始化播放库
DVRWRAPPERSHARED_EXPORT BOOL PLAY_DrawAreaRelease();

//打开播放文件（pszDecoderName允许为空，表示自动选择解码器）
DVRWRAPPERSHARED_EXPORT long PLAY_OpenFile(char *szFileName,const char* pszDecoderName);

//关闭播放文件
DVRWRAPPERSHARED_EXPORT BOOL PLAY_CloseFile(long lPlayHandle);

//播放文件
DVRWRAPPERSHARED_EXPORT BOOL PLAY_Play(long lPlayHandle, DVR_HWND hWnd);

//停止播放
DVRWRAPPERSHARED_EXPORT BOOL PLAY_StopPlay(long lPlayHandle);

//回放控制
DVRWRAPPERSHARED_EXPORT BOOL PLAY_PlayControl(long lPlayHandle, unsigned long ulControlCode, unsigned long ulInValue, unsigned long *pOutValue);

//以bmp格式抓图
DVRWRAPPERSHARED_EXPORT BOOL PLAY_CaptureBmp(long lPlayHandle, char *szFileName);

//以jpeg格式抓图(lQuality:0--100，越大质量越好)
DVRWRAPPERSHARED_EXPORT BOOL PLAY_CaptureJpeg(long lPlayHandle, long lQuality, char *szFileName);

//设置回放区域，实现局部放大
DVRWRAPPERSHARED_EXPORT BOOL PLAY_SetPlayRegion(long lPlayHandle, DVR_RECT *pRegion, BOOL bEnable);

//打开流（pszDecoderName允许为空，表示自动选择解码器）
DVRWRAPPERSHARED_EXPORT long PLAY_OpenStream(char *pHeadBuf, long lHeadBufSize, long lStreamBufSize,const char* pszDecoderName);

//关闭流(播放句柄不再可用)
DVRWRAPPERSHARED_EXPORT BOOL PLAY_CloseStream(long lPlayHandle);

//输入流数据
DVRWRAPPERSHARED_EXPORT BOOL PLAY_InputData(long lPlayHandle, char *pBuf, long lSize);

//返回视频参数(范围0--100)
DVRWRAPPERSHARED_EXPORT BOOL PLAY_GetVideoEffect(long lPlayHandle, long *pBrightness, long *pContrast, long *pSaturation, long *pHue);

//设置视频参数(范围0--100)
DVRWRAPPERSHARED_EXPORT BOOL PLAY_SetVideoEffect(long lPlayHandle, long lBrightness, long lContrast, long lSaturation, long lHue);

//虚拟PTZ控制
DVRWRAPPERSHARED_EXPORT BOOL PLAY_PTZControl(long lPlayHandle, unsigned long ulPTZCommand, unsigned long ulSpeed);

#ifdef __cplusplus
}
#endif

#endif // DVRWRAPPER_H
