/*********编码设备统一接口 版本2.2.2017.0608***************/
/*更新说明：
*1.新增加信号量上报消息DVR_MESSAGE_SWITCH_REPORT和信号量上报结构体DVR_SWITCH_REPORT定义；
*2.统一调整环境量术语为模拟量。
*/

#ifndef PLATFORMDEF_H
#define PLATFORMDEF_H

#include "DVRWrapperDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DVR_MAX_MAP_ITEM                        128     //最大地图项数量
#define DVR_MAX_SCHEME_ITEM                     128     //最大轮巡预案项数量

//参数配置
#define DVR_GET_MAP_INFO_CFG                    1001    //获取地图信息配置
#define DVR_GET_MAP_ITEM_INFO_CFG               1002    //获取地图项信息配置
#define DVR_GET_SCENE_INFO_CFG                  1003    //获取监控场景信息配置
#define DVR_GET_SCHEME_INFO_CFG                 1004    //获取轮巡预案信息配置
#define DVR_GET_NETNODE_INFO_CFG                1005    //获取网管信息配置
#define DVR_GET_NETDATA_INFO_CFG                1006    //获取网管数据
#define DVR_GET_SERVICE_STATUS                  1007    //获取服务状态
#define DVR_SET_SERVICE_STATUS                  2008    //设置服务状态

//消息类型
#define DVR_MESSAGE_MSSTATUS_CHANGED            21      //服务主备状态改变通知

//客户端之间用户间音视频会话方式
#define DVR_AUDIO_SESSION                       0x01    //语音会话
#define DVR_VIDEO_SESSION                       0x02    //视频会话
#define DVR_AV_SESSION                          0x04    //音视频会话

//音视频会话响应状态
#define DVR_SESSION_TRYING                      0x01    //尝试中
#define DVR_SESSION_OK                          0x02    //成功
#define DVR_SESSION_TIMEOUT                     0x04    //等待超时
#define DVR_SESSION_REJECT                      0x08    //拒绝
#define DVR_SESSION_UNAUTHORIZED                0x10    //未授权
#define DVR_SESSION_SERVERERROR                 0x20    //服务错误

//服务种类
#define DVR_SERVER_UNKNOWN                      0UL     //未知服务
#define DVR_SERVER_DB_SERVER                    1UL     //数据库服务
#define DVR_SERVER_MANAGEMENT_SERVER            2UL     //管理服务
#define DVR_SERVER_DVR_PROXY_SERVER             3UL     //DVR代理服务
#define DVR_SERVER_ALARM_HOST_PROXY_SERVER      4UL     //报警主机代理服务
#define DVR_SERVER_DC_PROXY_SERVER              5UL     //门禁代理服务
#define DVR_SERVER_STREAM_SERVER                6UL     //流媒体服务
#define DVR_SERVER_ALARM_SERVER                 7UL     //报警服务
#define DVR_SERVER_CONTROL_SERVER               8UL     //控制服务
#define DVR_SERVER_RECORD_SERVER                9UL     //存储服务
#define DVR_SERVER_PLAYBACK_SERVER              10UL    //回放服务
#define DVR_SERVER_LINKAGE_SERVER               11UL    //联动服务
#define DVR_SERVER_DVR_REGISTER_SERVER          12UL    //DVR注册服务
#define DVR_SERVER_SCHEDULER_SERVER             13UL    //计划服务
#define DVR_SERVER_PLATFORM_GATEWAY_SERVER      14UL    //平台网关服务,如国网B接口
#define DVR_SERVER_LOCAL_HOST_SERVER            15UL    //本地主机服务
#define DVR_SERVER_NETWORK_MANEGEMENT_SERVER    16UL    //网管服务
#define DVR_SERVER_CLIENT_GATEWAY_SERVER        17UL    //客户端网关服务
#define DVR_SERVER_ALARM_GATEWAY_SERVER      	18UL    //报警网关服务
#define DVR_SERVER_LOCATION_SERVER              19UL    //定位服务
#define DVR_SERVER_ANTIFALLING_SERVER           20UL    //防坠服务

#define DVR_SERVER_CLIENT                       51UL    //监控客户端
#define DVR_SERVER_CONFIG_CLIENT                52UL    //配置客户端
#define DVR_SERVER_MD_CLIENT                    53UL    //大屏解码客户端
#define DVR_SERVER_MD_MANAGER                   54UL    //大屏管理端

#define DVR_SERVER_LAUNCHER                     70UL    //启动服务
#define DVR_SERVER_SERVICE_MANAGER           	71UL    //服务管理服务

#define DVR_OTHER_SERVER                        200     //其他服务
#define DVR_ALL_SERVER                          255     //所有服务

//服务运行状态
#define DVR_RUN_UNKNOWN                         0       //未知
#define DVR_RUN_ONLINE                          1       //在线
#define DVR_RUN_EXCEPTION                       2       //异常
#define DVR_RUN_OFFLINE                         3       //离线
#define DVR_RUN_ALL                             99      //所有状态

//服务主备状态
#define DVR_MS_UNKNOWN                          0       //未知
#define DVR_MS_MASTER                           1       //主状态
#define DVR_MS_SLAVE                            2       //备状态
#define DVR_MS_SWITCHING                        3       //主备切换状态
#define DVR_MS_ALL                              99      //所有状态

//地图项种类
#define DVR_MI_PICTURE                 			0UL     //图片
#define DVR_MI_CIRCLE                   		1UL     //圆（矢量图形）
#define DVR_MI_ELLIPSE                         	2UL     //椭圆（矢量图形）
#define DVR_MI_RECTANGLE                       	3UL     //矩形（矢量图形）
#define DVR_MI_POLYGON                         	4UL     //多边形（矢量图形）
#define DVR_MI_WIDGET                           5UL     //窗口
#define DVR_MI_LINE                             6UL     //线（矢量图形）
#define DVR_MI_PATH                             7UL     //路径（矢量图形）
#define DVR_MI_TEXT                             8UL     //文本
#define DVR_MI_ALL                              0xffffUL//所有


//摄像机可视区域
struct CameraVisibleArea
{
    float fOriginX;                                     //椭圆原点x坐标（单位：像素）
    float fOriginY;                                     //椭圆原点y坐标（单位：像素）
    int iStartAngle;                                    //开始角度(0-360)
    int iEndAngle;                                      //结束角度(0-360)
    float fXRadius;                                     //椭圆x轴半径（单位：像素）
    float fYRadius;                                     //椭圆y轴半径（单位：像素）
};

//地图信息
typedef struct
{
    DVR_DEV_ID      llMapId;                            //地图Id(全局编号)
    char            szName[128];                        //地图名称
    int             iStatus;                            //状态（保留）
    DVR_DEV_ID      llParentMapId;                      //父地图Id(全局编号)
    char            szMapCode[16];                      //地图编码
    char            szPictureUrl[256];                  //背景图片文件下载URL
    unsigned short  uiImageWidth;                       //图片宽度（单位：像素）
    unsigned short  uiImageHeight;                      //图片高度（单位：像素）
    float           fRealWorldWidth;                    //真实世界宽度（单位：米）
    float           fRealWorldHeight;                   //真实世界高度（单位：米）
    unsigned int    uiReserved;                         //保留
} DVR_MAP_INFO, *PDVR_MAP_INFO;

//地图信息数组
typedef struct
{
    unsigned int    uiMapInfoCount;                     //地图信息数量
    DVR_MAP_INFO    mapInfos[];                         //地图信息数组
} DVR_MAP_INFOS, *PDVR_MAP_INFOS;

//地图项信息
typedef struct                                    
{
    DVR_DEV_ID      llDevId;                            //地图项Id(全局编号)（摄像机/报警器/地图等）
    char            szName[128];                        //名称
    int             iStatus;                            //状态（保留）
    unsigned short  usItemKind;                         //地图项种类
    unsigned short  usResouceKind;                      //资源种类
    unsigned short  usResouceSubType;                   //资源子类型
    DVR_DEV_ID      llResouceID;                        //资源ID
    float           fImagePosX;                         //图片x坐标（单位：像素）
    float           fImagePosY;                         //图片y坐标（单位：像素）
    unsigned short  usWidth;                            //地图项宽度（单位：像素，位图：图片宽度，矢量图：bounding宽度）
    unsigned short  usHeight;                           //地图项高度（单位：像素，位图：图片高度，矢量图：bounding高度）
	unsigned int    uiPointOffsetCount;                 //点相对坐标数量
    float           pointOffset[16][2];                 //点相对坐标集合（单位：像素，相对原点坐标，仅对矢量图有效）
    DVR_DEV_ID      llMapId;                            //地图Id(全局编号)
    unsigned int    uiReserved;                         //保留
    union
    {
        struct CameraVisibleArea   cvaCameraVisibleArea;//摄像机可视区域
    };
}DVR_MAP_ITEM_INFO;

//地图项信息数组
typedef struct
{
    unsigned int        uiMapItemInfoCount;             //地图项信息数量
    DVR_MAP_ITEM_INFO   mapItemInfos[];                 //地图项信息数组
} DVR_MAP_ITEM_INFOS, *PDVR_MAP_ITEM_INFOS;

//监控场景信息
typedef struct
{
    DVR_DEV_ID         llSceneId;                        //监控场景全局编码
    char               szName[128];                      //监控场景名称
    int                iStatus;                          //状态（保留）
    DVR_DEV_ID         llRegionId;                       //归属区域全局编码
    char               szRegionName[128];                //归属区域名称
    unsigned int       uiReserved;                       //保留
    unsigned int       uiPresetInfoCount;                //预置点数量
    DVR_PTZPRESETINFO  presetInfos[DVR_MAX_PRESET];      //预置点信息数组
} DVR_SCENEINFO, *PDVR_SCENEINFO;

//监控场景信息数组
typedef struct
{
    unsigned int       uiSceneCount;                     //监控场景信息数量
    DVR_SCENEINFO      sceneInfos[];                     //监控场景信息数组
} DVR_SCENEINFOS, *PDVR_SCENEINFOS;

//轮巡预案项信息
typedef struct
{
    DVR_PTZPRESETINFO  presetInfo;                       //预置点信息
    DVR_DEV_ID         llPanelID;                        //视频面板ID
} DVR_SCHEME_ITEM_INFO, *PDVR_SCHEME_ITEM_INFO;

//轮巡预案信息
typedef struct
{
    DVR_DEV_ID         llSchemeId;                      //轮巡预案全局编码
    char               szName[128];                     //轮巡预案显示名
    int                iStatus;                         //状态（保留）
    int                iType;                           //表示区域或轮巡预案
    DVR_DEV_ID         llRegionId;                      //归属区域全局编码
    char               szRegionName[128];               //归属区域名称
    unsigned int       uiCycleInterval;                 //轮巡周期
    unsigned int       uiCycleTimes;                    //轮巡次数
    unsigned int       uiReserved;                      //保留
    unsigned int       uiSchemeItemInfoCount;           //轮巡预案项数量
    DVR_SCHEME_ITEM_INFO itemInfos[DVR_MAX_SCHEME_ITEM];//轮巡预案项信息数组
} DVR_SCHEME_INFO, *PDVR_SCHEME_INFO;

//轮巡预案信息数组
typedef struct
{
    unsigned int        uiSchemeCount;                  //轮巡预案信息数量
    DVR_SCHEME_INFO     SchemeInfos[];                  //轮巡预案信息数组
} DVR_SCHEME_INFOS, *PDVR_SCHEME_INFOS;

//音视频会话信息
typedef struct  
{
    DVR_DEV_ID         llToUserId;                      //被叫用户地址编码
    unsigned int       uiSessionMode;                   //会话模式
    DVR_HWND           hVideoWnd;                       //视频窗口
    unsigned int       uiWaitTimeout;                   //等待超时
    unsigned int       uiReserved;                      //保留
} DVR_AV_SESSION_INFO,*PDVR_AV_SESSION_INFO;

//服务状态
typedef struct 
{
    int  iServiceType;                                   //服务类型
    int  iRunState;                                      //运行状态
	int  iMSState;                                       //主备状态
	unsigned int uiReserved;
}DVR_SERVICE_STATUS, *PDVR_SERVICE_STATUS;

//网管资源信息
typedef struct
{
    DVR_DEV_ID         llNetNodeId;                     //全局编号（服务器时填写，服务可不填写）
    char               szName[128];                     //显示名
    char               szIP[128];                       //IP地址
    DVR_DEV_ID         llParentId;                      //父设备Id(全局编号，服务所属服务器ID）
    int                iStatus;                         //活动状态（1表示在线，详见“设备在线状态”定义）
    int                iNodeType;                       //节点类型（服务类型，100表示服务器,0－99表示服务）
    unsigned int       uiReserved;                      //保留
} DVR_NETNODEINFO, *PDVR_NETNODEINFO;

//网管资源信息数组
typedef struct
{
    unsigned int       	uiNetNodeCount;                 //网络资源信息数量
    DVR_NETNODEINFO     netNodeInfos[];                 //网络资源信息数组
} DVR_NETNODEINFOS, *PDVR_NETNODEINFOS;

//网管数据信息
typedef struct
{
    DVR_DEV_ID         llNetNodeId;                     //全局编号（服务器时填写，服务可不填写）
    char               szName[128];                     //显示名
    char               szIP[128];                       //IP地址
    DVR_DEV_ID         llParentId;                      //父设备Id(全局编号，服务所属服务器ID）
    float              fCpuValue;                       //CPU使用率
    float              fCpuMaxValue;                    //CPU最大使用率
    float              fCpuMinValue;                    //CPU最小使用率
    float              fMemValue;                       //内存使用量
    float              fMemMaxValue;                    //最大内存使用量
    float              fMemMinValue;                    //最小内存使用量
    int                iNodeType;                       //节点类型（服务类型，100表示服务器,0－99表示服务）
    DVR_TIME           dtDate;                          //上报时间
    unsigned int       uiReserved;                      //保留
} DVR_NETDATAINFO, *PDVR_NETDATAINFO;

//网管数据信息数组
typedef struct
{
    unsigned int       uiNetDataCount;                  //网络资源信息数量
    DVR_NETDATAINFO    netDataInfos[];                  //网络资源信息数组
} DVR_NETDATAINFOS, *PDVR_NETDATAINFOS;


//音视频会话回调函数
typedef void(*DVR_AVSESSIOIN_RESP_CALLBACK)(DVR_DEV_ID llFromUserId,const char* pszRemoteIp,unsigned long* pulResponseState);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//以下为平台专用接口
//开始音视频对讲
DVRWRAPPERSHARED_EXPORT long DVR_StartAVSession(long lUserHandle, PDVR_AV_SESSION_INFO pAVSessionInfo, DVR_VOICEDATA_CALLBACK fnDataCallback, unsigned long ulUserData);

//返回音视频对讲状态
DVRWRAPPERSHARED_EXPORT unsigned long DVR_GetAVSessionState(long lAVSessionHandle);

//停止音视频对讲
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopAVSession(long lAVSessionHandle);

//启动音视频对讲侦听
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartAVSessionListen(char *szLocalIP, long lLocalPort, DVR_AVSESSIOIN_RESP_CALLBACK fnAVSessionRespCallBack);

//停止音视频对讲侦听
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopAVSessionListen();


//
//启动服务状态上报（iReportInterval表示上报时间间隔，单位为毫秒）
DVRWRAPPERSHARED_EXPORT BOOL DVR_StartServiceStatusReport(int iServiceType,int iReportInterval);

//停止服务状态上报
DVRWRAPPERSHARED_EXPORT BOOL DVR_StopServiceStatusReport();


#ifdef __cplusplus
}
#endif

#endif // DVRWRAPPERDEF_H
