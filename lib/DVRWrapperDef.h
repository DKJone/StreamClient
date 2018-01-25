/*********编码设备统一接口 版本2.2.2017.0608***************/
/*更新说明：
*1.新增加信号量上报消息DVR_MESSAGE_SWITCH_REPORT和信号量上报结构体DVR_SWITCH_REPORT定义；
*2.统一调整环境量术语为模拟量。
*/

#ifndef DVRWRAPPERDEF_H
#define DVRWRAPPERDEF_H

#if defined(DVRWRAPPER_LIBRARY)
#include <QtCore/qglobal.h>
#  define DVRWRAPPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DVRWRAPPERSHARED_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
//WIN32平台宏定义
#include <windows.h>
#elif defined(__ANDROID__)
#elif defined(__APPLE__)
#elif defined(__linux__)
#endif

#define DVRWRAPPERAPI
#define DVRWRAPPER_CALLBACK

//按4字节对齐
#pragma pack(4)

//数据类型
#define DVR_INVALID_HANDLE          (-1)            //无效句柄

#if defined(_MSC_VER)
    #define DVR_DEV_ID __int64                      //设备ID类型
#elif defined(__GNUC__)
    #define DVR_DEV_ID long long                    //设备ID类型
#else
    #define DVR_DEV_ID __int64                      //设备ID类型
#endif

#ifndef BOOL
typedef int BOOL;
#define TRUE 	1
#define FALSE 	0
#endif

//区域
typedef struct {
     int x;
     int y;
     int width;
     int height;
}DVR_RECT, *PDVR_RECT;

//HWND、HDC
#ifdef _WIN32
    typedef HWND            DVR_HWND;               //窗口句柄
    typedef HDC             DVR_HDC;                //DC句柄
#elif defined(__ANDROID__)
    typedef void*           DVR_HWND;               //窗口句柄
    typedef void*           DVR_HDC;                //DC句柄
#elif defined(__APPLE__)
    typedef void*           DVR_HWND;               //窗口句柄
    typedef void*           DVR_HDC;                //DC句柄
#else
    typedef DVR_RECT        DVR_HWND;               //窗口句柄
    typedef struct
    {
        void* surface;                              //SDL surface
        DVR_HWND hWnd;                              //窗口句柄
    }DVR_DC, *DVR_HDC;                              //DC句柄
#endif

//数据长度
#define DVR_SERIALNO_LEN            48              //序列号长度
#define DVR_IP_LEN                  16              //IP地址长度
#define DVR_USR_LEN                 32              //用户名长度
#define DVR_PASS_LEN                32              //密码长度
#define DVR_FILENAME_LEN            256             //文件名长度
#define DVR_DEVNUM_MAX              99999           //设备最大数量
#define DVR_MAX_PRESET              64              //最大预置点数量

//连接模式
#define DVR_CONNET_DIRECT           0               //直连模式
#define DVR_CONNET_PROXY            1               //转发模式

//连接方式
#define DVR_CONNECT_MODE_TCP        0               //TCP方式连接
#define DVR_CONNECT_MODE_UDP        1               //UDP方式连接
#define DVR_CONNECT_MODE_MUTI       2               //组播方式连接

//流数据类型（用于实时流回调、语音对讲回调）
#define DVR_HEADER              0x01                //头数据
#define DVR_VIDEOSTREAM         0x02                //视频流数据（SDK内部封装）
#define DVR_AUDIOSTREAM_IN      0x03                //输入语音流（设备采集，发送到本地）
#define DVR_AUDIOSTREAM_OUT     0x04                //输出语音流（本地采集，发送到设备）
#define DVR_RPU_STREAM_PGSP     0x05                //PGSP封装视频流
#define DVR_RTPSTREAM           0x06                //RTP封装视频流
#define DVR_PRIMVIDEOSTREAM     0x07                //原始视频数据
#define DVR_PRIMAUDIOSTREAM     0x08                //原始音频数据
#define DVR_AUDIOSTREAM_MIXER   0x09                //语音混音流

//编码格式
#define DVR_COMPRESSION_MPEG4   98                  //MPEG4
#define DVR_COMPRESSION_AVS     99                  //AVS
#define DVR_COMPRESSION_H264    100                 //H264

//分辨率
#define DVR_RESOLUTION_D1           1               //704x576
#define DVR_RESOLUTION_HD1          2
#define DVR_RESOLUTION_BCIF         3
#define DVR_RESOLUTION_CIF          4               //352x288
#define DVR_RESOLUTION_QCIF         5               //176x144
#define DVR_RESOLUTION_VGA          6               //640x480
#define DVR_RESOLUTION_QVGA         7               //320x240
#define DVR_RESOLUTION_SVCD         8
#define DVR_RESOLUTION_XGA          9               //1024x768
#define DVR_RESOLUTION_720          200             //1280x720
#define DVR_RESOLUTION_960          201             //1280x960
#define DVR_RESOLUTION_1080         202             //1920x1080
#define DVR_RESOLUTION_1200         203             //1600x1200
#define DVR_RESOLUTION_1536         204             //2048x1536
#define DVR_RESOLUTION_1920         205             //2560x1920

//帧图像结构
#define DVR_FRAME_YUV12           1                 //YV12
#define DVR_FRAME_RGB24           2                 //RGB24
#define DVR_FRAME_RGB32           3                 //RGB32

//码流控制模式
#define DVR_BRC_CBR               0                 //固定码流
#define DVR_BRC_VBR               1                 //可变码流
#define DVR_BRC_MBR               2                 //多码流

//设备ID使用模式
#define DVR_PHYSICAL_NUM        0x1                 //设备物理编号
#define DVR_GLOBAL_CODE         0x2                 //全局逻辑编号

//语音对讲模式
#define DVR_VOICE_TALKBACK      0x1                 //双向语音对讲
#define DVR_VOICE_TALK          0x2                 //广播
#define DVR_VOICE_LISTEN        0x3                 //监听

//录像文件类型
#define DVR_FILE_TYPE_UNKNOWN       0x00            //未知的录像类型
#define DVR_FILE_TYPE_NORMAL        0x01            //普通录像
#define DVR_FILE_TYPE_MOTION        0x02            //动态侦测录像
#define DVR_FILE_TYPE_ALARM         0x03            //报警录像
#define DVR_FILE_TYPE_TIMER         0x04            //定时录像
#define DVR_FILE_TYPE_LOSS          0x05            //视频丢失报警录像
#define DVR_FILE_TYPE_HIDE          0x06            //视频遮挡报警录像
#define DVR_FILE_TYPE_ALL           0x10            //所有类型的录像

//文件来源
#define DVR_FILE_SOURCE_DVR         0x00            //文件位于DVR
#define DVR_FILE_SOURCE_PLATFORM    0x01            //文件位于PLATFORM
#define DVR_FILE_SOURCE_ALL         0x10            //所有

//文件查找返回结果
#define DVR_FILE_FAILURE            0               //查找失败
#define DVR_FILE_SUCCESS            1000            //查找成功
#define DVR_ISFINDING               1002            //查找正在进行中
#define DVR_NOMOREFILE              1003            //没有更多的文件

//任务执行状态
#define DVR_EXECUTE_FAILURE   DVR_FILE_FAILURE      //执行失败
#define DVR_EXECUTE_SUCCESS   DVR_FILE_SUCCESS      //执行成功
#define DVR_EXECUTING         DVR_ISFINDING         //正在进行中

//PTZ命令
#define DVR_PTZ_STOP_ALL             0x0300         //停止所有

#define DVR_PTZ_MOVE_UP              0x0301         //上
#define DVR_PTZ_MOVE_DOWN            0x0302         //下
#define DVR_PTZ_MOVE_LEFT            0x0303         //左
#define DVR_PTZ_MOVE_RIGHT           0x0304         //右
#define DVR_PTZ_STOP_UP              0x0305         //停止上
#define DVR_PTZ_STOP_DOWN            0x0306         //停止下
#define DVR_PTZ_STOP_LEFT            0x0307         //停止左
#define DVR_PTZ_STOP_RIGHT           0x0308         //停止右

#define DVR_PTZ_MOVE_LEFTUP          0x0401         //移动左上
#define DVR_PTZ_MOVE_LEFTDOWN        0x0402         //移动左下
#define DVR_PTZ_MOVE_RIGHTUP         0x0403         //移动左上
#define DVR_PTZ_MOVE_RIGHTDOWN       0x0404         //移动右下
#define DVR_PTZ_STOP_LEFTUP          0x0405         //停止左上
#define DVR_PTZ_STOP_LEFTDOWN        0x0406         //停止左下
#define DVR_PTZ_STOP_RIGHTUP         0x0407         //停止左上
#define DVR_PTZ_STOP_RIGHTDOWN       0x0408         //停止右下

#define DVR_PTZ_ZOOM_IN              0x0501         //放大
#define DVR_PTZ_ZOOM_OUT             0x0502         //缩小
#define DVR_PTZ_STOP_ZOOM_IN         0x0503         //停止放大
#define DVR_PTZ_STOP_ZOOM_OUT        0x0504         //停止缩小

#define DVR_PTZ_FOCUS_IN             0x0601         //拉远
#define DVR_PTZ_FOCUS_OUT            0x0602         //拉近
#define DVR_PTZ_STOP_FOCUS_IN        0x0603         //停止拉远
#define DVR_PTZ_STOP_FOCUS_OUT       0x0604         //停止拉近
#define DVR_PTZ_AUTO_FOCUS_ON        0x0701         //自动调焦开
#define DVR_PTZ_AUTO_FOCUS_OFF       0x0702         //自动调焦关
#define DVR_PTZ_AUTO_ZOOM_ON         0x0801         //自动变倍开
#define DVR_PTZ_AUTO_ZOOM_OFF        0x0802         //自动变倍关
#define DVR_PTZ_APERTURE_INCREASE    0x0901         //光圈放大
#define DVR_PTZ_APERTURE_DECREASE    0x0902         //光圈缩小
#define DVR_PTZ_APERTURE_STOP_INCREASE      0x0903  //停止光圈缩小
#define DVR_PTZ_APERTURE_STOP_DECREASE      0x0904  //停止光圈缩小
#define DVR_PTZ_AUTO_APERTURE_ON     0x0a01         //自动光圈开
#define DVR_PTZ_AUTO_APERTURE_OFF    0x0a02         //自动光圈关
#define DVR_PTZ_AUXON               0x0b01          //擦拭启动
#define DVR_PTZ_AUXOFF              0x0b02          //擦拭停止
#define DVR_PTZ_AUTOPANON           0x0b03          //水平巡航启动
#define DVR_PTZ_AUTOPANOFF          0x0b04          //水平巡航停止
#define DVR_PTZ_LIGHT_ON            0x0b05          //灯光开启
#define DVR_PTZ_LIGHT_OFF           0x0b06          //灯光关闭
#define DVR_PTZ_STARTTOUR           0x0b07          //开始自动巡航
#define DVR_PTZ_STOPTOUR            0x0b08          //停止自动巡航

#define DVR_PTZ_HOT_OPEN            0x0c01          //加热开
#define DVR_PTZ_HOT_STOP            0x0c02          //加热关
#define DVR_PTZ_INFRARED_OPEN       0x0d01          //红外开
#define DVR_PTZ_INFRARED_CLOSE      0x0d02          //红外关
#define DVR_PTZ_SCAN_STAR           0x0e01          //线性扫描开始
#define DVR_PTZ_SCAN_STOP           0x0e02          //线性扫描停止
#define DVR_PTZ_TRACK_START         0x0f01          //轨迹巡航开始
#define DVR_PTZ_TRACK_STOP          0x0f02          //轨迹巡航停止
#define DVR_PTZ_PRESET_START        0x1001          //预置位巡航开始
#define DVR_PTZ_PRESET_STOP         0x1002          //预置位巡航停止
#define DVR_PTZ_LOCK                0x1101          //云台锁定
#define DVR_PTZ_UNLOCK              0x1102          //云台解锁

//PTZ预置点
#define DVR_PTZ_MOVE_PRESET         0x1201          //调用预置点
#define DVR_PTZ_SET_PRESET          0x1202          //设置预置点
#define DVR_PTZ_DEL_PRESET          0x1203          //删除预置点

//轨道机控制
#define DVR_PTZ_TRAIN_LEFT          0x1301          //轨道机左
#define DVR_PTZ_TRAIN_RIGHT         0x1302          //轨道机右
#define DVR_PTZ_TRAIN_RESET         0x1303          //轨道机复位
#define DVR_PTZ_TRAIN_MOVE_PRESET   0x1304          //调用轨道机预置点
#define DVR_PTZ_TRAIN_SET_PRESET    0x1305          //设置轨道机预置点
#define DVR_PTZ_TRAIN_DEL_PRESET    0x1306          //删除轨道机预置点
#define DVR_PTZ_TRAIN_LEFT_STOP   	0x1307          //轨道机左停止
#define DVR_PTZ_TRAIN_RIGHT_STOP    0x1308          //轨道机右停止
#define DVR_PTZ_TRAIN_UP          	0x1309          //轨道机上
#define DVR_PTZ_TRAIN_DOWN         	0x130a          //轨道机下
#define DVR_PTZ_TRAIN_UP_STOP       0x130b          //轨道机上停止
#define DVR_PTZ_TRAIN_DOWN_STOP     0x130c          //轨道机下停止

//扩增PTZ命令
#define DVR_PTZEXT_FASTPOSITION     0x0001          //快速定位

//图像校正PTZ命令（基于鱼眼全景高清摄像机实现）
#define DVR_PTZ_FILTER_NONE              0x2000     //无校正
#define DVR_PTZ_FILTER_AREACORRECTED     0x2001     //
#define DVR_PTZ_FILTER_SURROUND          0x2002     //
#define DVR_PTZ_FILTER_PANORAMA          0x2003     //
#define DVR_PTZ_FILTER_PANORAMA_FOCUS    0x2004     //
#define DVR_PTZ_FILTER_DOUBLE_PANORAMA   0x2005     //
#define DVR_PTZ_RESET                    0x2006     //恢复云台默认位置
#define DVR_PTZ_ROTATE_LEFT              0x2007     //左旋
#define DVR_PTZ_ROTATE_RIGHT             0x2008     //右旋

//PTZ速度
#define DVR_PTZ_SPEED_MIN           0
#define DVR_PTZ_SPEED_MAX           10

//录像回放控制码
#define DVR_PLAYBACK_START           1              //开始播放
#define DVR_PLAYBACK_STOP            2              //停止播放
#define DVR_PLAYBACK_PAUSE           3              //暂停播放
#define DVR_PLAYBACK_RESTART         4              //恢复播放
#define DVR_PLAYBACK_FAST            5              //快放
#define DVR_PLAYBACK_SLOW            6              //慢放
#define DVR_PLAYBACK_NORMAL          7              //正常速度
#define DVR_PLAYBACK_FRAME           8              //单帧放
#define DVR_PLAYBACK_STARTAUDIO      9              //开始播放音频
#define DVR_PLAYBACK_STOPAUDIO       10             //结束播放音频
#define DVR_PLAYBACK_AUDIOVOLUME     11             //设置音频音量
#define DVR_PLAYBACK_SETTIMEPOS      12             //设置回放时间(绝对时间)
#define DVR_PLAYBACK_GETTIMEPOS      13             //获取回放时间(绝对时间)
#define DVR_PLAYBACK_GETPOS          14             //获取回放百分比
#define DVR_PLAYBACK_SETPOS          15             //设置回放百分比
#define DVR_PLAYBACK_GETPLAYTIME     16             //获取当前已经播放的时间(按文件回放时有效)
#define DVR_PLAYBACK_GETPLAYFRAME    17             //获取当前已经播放的帧数(按文件回放时有效)
#define DVR_PLAYBACK_GETTOTALTIME    18             //获取当前播放文件总的时间(按文件回放时有效)
#define DVR_PLAYBACK_GETTOTALFRAMES  19             //获取当前播放文件总的帧数(按文件回放时有效)

//消息类型
#define DVR_MESSAGE_ALARM               0           //报警信息
#define DVR_MESSAGE_ENV_REPORT          1           //模拟量上报
#define DVR_MESSAGE_USER_REGISTER       2           //主动注册
#define DVR_MESSAGE_USER_UNREGISTER     3           //主动反注册
#define DVR_MESSAGE_DEVICE_REPORT       4           //设备资源上报
#define DVR_MESSAGE_STATUS_REPORT       5           //设备在线状态上报
#define DVR_MESSAGE_MAP_REPORT          7           //地图资源上报
#define DVR_MESSAGE_SCHEME_REPORT       8           //监控场景资源上报
#define DVR_MESSAGE_PTZPRESET_REPORT    9           //预置点上报
#define DVR_MESSAGE_DEVICE_ONLINE_REPORT 10         //设备在线率上报
#define DVR_MESSAGE_DEVICE_REPORT_V15   11          //设备资源上报V1.5版
#define DVR_MESSAGE_STATUS_REPORT_V15   12          //设备在线状态上报V1.5版
#define DVR_MESSAGE_DEVICE_REPORT_V20   13          //设备资源上报V2.0版
#define DVR_MESSAGE_SWITCH_REPORT       21          //信号量上报


//////////////////////////////////////////////////////////////////////////////////////////////////////
//智能分析相关类型定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//人脸识别相关
#define DVR_MESSAGE_IVS_PERSON_INFO_REPORT             		100   	//新增人员信息上报
#define DVR_MESSAGE_IVS_PERSON_REGISTER_DATA_REPORT         101   	//新增人员注册数据上报（包含实际文件数据如特征码、照片等）
#define DVR_MESSAGE_IVS_PERSON_VERIFY_RECORD_REPORT 		102		//新增人员比对记录上报
#define DVR_MESSAGE_IVS_PERSON_VERIFY_RECORD_DATA_REPORT    103     //新增人员比对记录数据上报（包含实际文件数据如特征码、照片等）
#define DVR_MESSAGE_IVS_PERSON_EXPAND_INFO_REPORT           104   	//新增人员扩展信息上报
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位相关类型定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define DVR_MESSAGE_LOCATION_REPORT_REPORT             		200   	//定位信息上报
//////////////////////////////////////////////////////////////////////////////////////////////////////


//设备类型
#define DVR_DVR                      0              //编码设备
#define DVR_CAMERA                   1              //摄像机
#define DVR_ALARM                    2              //报警器
#define DVR_OUTPUT                   3              //报警输出
#define DVR_NET_DEVICE               4              //网络设备
#define DVR_PC_HOST                  5              //PC主机
#define DVR_STORAGE                  6              //存储设备
#define DVR_AUX                      10             //辅助设备
#define DVR_DC                       11             //门禁控制器
#define DVR_DOOR                     12             //门
#define DVR_LOCATION                 13             //定位标签
#define DVR_PERSON                   100            //人员
#define DVR_DUTY                 	 101            //岗位
#define DVR_DEPARTMENT               102            //机构

#define DVR_SOFTWARE_MODULE          251            //软件模块
#define DVR_SCHEME                   252            //轮巡预案
#define DVR_EMAP                     253            //电子地图
#define DVR_SCENE                    254            //监控场景
#define DVR_REGION                   255            //区域

//设备子类型
#define DVR_SUB_TYPE_UNKNOWN         65535          //未定义

//DVR设备类型
#define DVR_DVR_TYPE_EDVR             0             //嵌入式DVR设备
#define DVR_DVR_TYPE_PC_DVR           1             //PC式DVR
#define DVR_DVR_TYPE_IPC              2             //网络摄像机
#define DVR_DVR_TYPE_DVS              3             //视频服务器
#define DVR_DVR_TYPE_PC               4             //PC
#define DVR_DVR_TYPE_NET_AUX          5             //网络辅助设备
#define DVR_DVR_TYPE_NET_ALARM        6             //网络报警设备
#define DVR_DVR_TYPE_PLATFORM         7             //平台
#define DVR_DVR_TYPE_DC               8             //门禁控制器
#define DVR_DVR_TYPE_OHTER            99            //其他DVR

//摄像机类型
#define DVR_CAMERA_TYPE_NET_HIGHSPEED_DOME  0       //网络高速球
#define DVR_CAMERA_TYPE_NET_MIDSPEED_DOME   1       //网络中速球
#define DVR_CAMERA_TYPE_NET_CAMERA          2       //网络固定摄像机
#define DVR_CAMERA_TYPE_HIGHSPEED_DOME      3       //高速球
#define DVR_CAMERA_TYPE_MIDSPEED_DOME       4       //中速球
#define DVR_CAMERA_TYPE_CAMERA              5       //固定摄像机
#define DVR_CAMERA_TYPE_PTZ_CAMERA          6       //云台摄像机
#define DVR_CAMERA_TYPE_NET_HD_CAMERA       7       //网络高清固定摄像机
#define DVR_CAMERA_TYPE_INFRARED_DOME       9       //红外球机
#define DVR_CAMERA_TYPE_NFRARED_CAMERA      10      //红外固定摄像机
#define DVR_CAMERA_TYPE_NET_HD_DOME         11      //网络高清球机
#define DVR_CAMERA_TYPE_INFRARED_IMAGER     12      //红外热成像仪
#define DVR_CAMERA_TYPE_RAIL_CAMERA         13      //轨道机摄像机
#define DVR_CAMERA_TYPE_FULL_VIEW_HD_CAMERA 14      //高清全景摄像机
#define DVR_CAMERA_TYPE_OHTER               99      //其他摄像机

//报警器类型
#define DVR_ALARM_TYPE_WATER_DETECT   0             //水浸
#define DVR_ALARM_TYPE_INFRARED       1             //红外对射
#define DVR_ALARM_TYPE_DOOR           2             //门
#define DVR_ALARM_TYPE_SMOKE_SENSOR   3             //烟感
#define DVR_ALARM_TYPE_SCADA          4             //综自系统
#define DVR_ALARM_TYPE_FIRE           5             //消防系统
#define DVR_ALARM_TYPE_INFRARED_PAIR  6             //红外双鉴
#define DVR_ALARM_TYPE_RAIL           7             //电子围栏
#define DVR_ALARM_TYPE_POWER_DI       8             //通信电源(遥信量)
#define DVR_ALARM_TYPE_BATTERY_DI     9             //蓄电池(遥信量)
#define DVR_ALARM_TYPE_SWITCH         10            //开关
#define DVR_ALARM_TYPE_RUN_STATUS     11            //运行状态(运行中或停止运行）
#define DVR_ALARM_TYPE_OTHER_SIGNAL   49            //其他信号量

#define DVR_ALARM_TYPE_TEMPERATURE    50            //温度
#define DVR_ALARM_TYPE_HUMIDITY       51            //湿度
#define DVR_ALARM_TYPE_SF6            52            //SF6
#define DVR_ALARM_TYPE_WINDSPEED      53            //风速
#define DVR_ALARM_TYPE_CURRENT        54            //电流
#define DVR_ALARM_TYPE_VOLTAGE        55            //电压
#define DVR_ALARM_TYPE_EFFICIENCY     56            //功率
#define DVR_ALARM_TYPE_FREQUENCY      57            //频率
#define DVR_ALARM_TYPE_LOAD           58            //负载率（负荷率）
#define DVR_ALARM_TYPE_PRESSURE       59            //压力
#define DVR_ALARM_TYPE_TIME           60            //时间
#define DVR_ALARM_TYPE_SPEED          61            //速度
#define DVR_ALARM_TYPE_POWER_AI       62            //通信电源(遥测量)
#define DVR_ALARM_TYPE_BATTERY_AI     63            //蓄电池(遥测量)
#define DVR_ALARM_TYPE_ENERGY         64            //电量
#define DVR_ALARM_TYPE_DISTANCE       65            //距离
#define DVR_ALARM_TYPE_OTHER_ENV      99            //其他模拟量

//报警输出类型
#define DVR_OUTPUT_TYPE_LIGHT         0             //灯光照明
#define DVR_OUTPUT_TYPE_WARNING       1             //声光告警
#define DVR_OUTPUT_TYPE_RING          2             //警笛
#define DVR_OUTPUT_TYPE_AIRCON        3             //空调
#define DVR_OUTPUT_TYPE_DOOR          4             //门
#define DVR_OUTPUT_TYPE_SWITCH        5             //开关
#define DVR_OUTPUT_TYPE_OTHER_SIGNAL  49            //其他信号量

#define DVR_OUTPUT_TYPE_TEMPERATURE   50            //温度
#define DVR_OUTPUT_TYPE_HUMIDITY      51            //湿度
#define DVR_OUTPUT_TYPE_OTHER_ENV     99            //其他模拟量

//网络设备类型
#define DVR_NETDEV_TYPE_SWITCH        0             //交换机
#define DVR_NETDEV_TYPE_FIREWALL      1             //防火墙
#define DVR_NETDEV_TYPE_ROUTER        2             //路由器
#define DVR_NETDEV_TYPE_OTHER         99            //其他网络设备

//门禁控制器类型
#define DVR_DC_TYPE_DOOR_CONTROLLER    0            //门禁控制器
#define DVR_DC_TYPE_DOOR_READER        1            //门禁读卡器
#define DVR_DC_TYPE_DOOR_OPEN_BUTTON   2            //开门按钮
#define DVR_DC_TYPE_DOOR_ALARM_IN      3            //门禁报警输入
#define DVR_DC_TYPE_DOOR_ALARM_OUT     4            //门禁报警输出
#define DVR_DC_TYPE_DOOR_LOCKER        5            //门锁
#define DVR_DC_TYPE_DOOR_MAGNETOMETER  6            //门磁
#define DVR_DC_TYPE_DOOR_CARD_READER   7            //发卡器
#define DVR_DC_TYPE_OTHER              99           //其他门禁控制器设备

//门类型
#define DVR_DOOR_DOOR                 0             //门

//门操作种类
#define DVR_DOOR_NONE                 0             //无动作
#define DVR_DOOR_OPEN                 1             //开门
#define DVR_DOOR_CLOSE                2             //关门
#define DVR_DOOR_FORCED_OPEN          4             //强制开门
#define DVR_DOOR_REMOTE_OPEN          5             //远程开门
#define DVR_DOOR_PWD_OPEN             6             //密码开门
#define DVR_DOOR_FORCE_OPEN           7             //胁迫码开门
#define DVR_DOOR_DI_OPEN              8             //自定义输入开门
#define DVR_DOOR_BUTTON_OEPN          9             //按扭开门
#define DVR_DOOR_REMOTE_CLOSE         10            //远程关门
#define DVR_DOOR_URGENT_OPEN          11            //紧急开门
#define DVR_DOOR_URGENT_CLOSE         12            //紧急关门
#define DVR_DOOR_FORCE_CLOSE          13            //强制关门
#define DVR_DOOR_CANCEL_FORCE_CLOSE   14            //取消强制关门
#define DVR_DOOR_BUTTION_CLOSE        15            //按扭关门
#define DVR_DOOR_CARD_OPEN            16            //刷卡开门
#define DVR_DOOR_NOT_AUTHORIZED       17            //未授权卡
#define DVR_DOOR_CARD_EXPIRED         18            //卡过期
#define DVR_DOOR_INCORRECT_PASS       19            //错误密码
#define DVR_DOOR_BACK_FORBIDDEN       20            //违反反潜回规则

//定位类型
#define DVR_LOCATION_PERSON           0             //人(移动)
#define DVR_LOCATION_VEHICLE          1             //车(移动)
#define DVR_LOCATION_OBJECT           50            //物体(固定)

//人员类型
#define DVR_PERSON_STAFF              0             //内部员工
#define DVR_PERSON_GUEST              1             //外来人员
#define DVR_PERSON_INSPECTOR          2             //巡视人员

//设备在线状态
#define DVR_STATUS_ENABLED           1              //可用
#define DVR_STATUS_DISABLED          2              //不可用
#define DVR_STATUS_REMOVED           3              //移除

//报警器报警状态（包括模拟量和信号量）
#define DVR_ALMSTATE_OFF                0           //正常状态或报警取消
#define DVR_ALMSTATE_ON                 1           //报警状态或产生报警

//报警输出-信号量输出状态
#define DVR_ALMOUT_STATUS_OFF           0           //关状态或输出关
#define DVR_ALMOUT_STATUS_ON            1           //开状态或输出开

//闭合、分开是两种信号量状态，闭合不代表一定是打开设备，常闭模式下分开才是打开设备
//查询返回值状态只有ON和OFF两种状态，其他值仅作命令
#define DVR_ALMOUT_VALUE_OFF           	0U          //分开（命令和状态,适用于常开、常闭控制方式）
#define DVR_ALMOUT_VALUE_ON            	1U          //闭合（命令和状态,适用于常开、常闭控制方式）
#define DVR_ALMOUT_VALUE_PLUSE_OFF      3U          //输出脉冲分开（仅命令,适用于常闭闪开控制方式）
#define DVR_ALMOUT_VALUE_PLUSE_ON       2U          //输出脉冲闭合（仅命令,适用于常开闪闭控制方式）
#define DVR_ALMOUT_VALUE_ALWAYS_OFF 	4U          //常开（仅命令）
#define DVR_ALMOUT_VALUE_ALWAYS_ON      5U          //常闭（仅命令）
#define DVR_ALMOUT_VALUE_RESTORE_NORMAL 6U          //恢复普通模式（仅命令,允许开关）

//报警事件类型
#define DVR_ALMTYPE_NONE                0           //无报警
#define DVR_ALMTYPE_DEVICE_FAIL         1           //设备故障
#define DVR_ALMTYPE_HIDE_DETECT         2           //视频遮挡告警
#define DVR_ALMTYPE_LOSS_DETECT         3           //视频丢失告警
#define DVR_ALMTYPE_MOTION_DETECT       4           //视频移动侦测告警
#define DVR_ALMTYPE_DISK_FULL           5           //磁盘满告警
#define DVR_ALMTYPE_DISK_ERROR          6           //磁盘出错告警
#define DVR_ALMTYPE_DISK_NOFORAMT       7           //磁盘没有格式化
#define DVR_ALMTYPE_HIGH_CPU_USEAGE     8           //CPU占用率过高
#define DVR_ALMTYPE_HIGH_MEM_USEAGE     9           //内存占用率过高
#define DVR_ALMTYPE_ACCESS_OVERFLOW     10       
//网络流量过大
#define DVR_ALMTYPE_ANALOG_ALARM        11          //模拟量输入报警
#define DVR_ALMTYPE_SWITCH_ALARM        12          //信号量输入报警
#define DVR_ALMTYPE_DOOR_SWITCH         13          //门开关操作
#define DVR_ALMTYPE_DOOR_ALARM          14          //门状态异常
#define DVR_ALMTYPE_ANALOG_VALUE_CHANGE 15          //模拟量输入数值变化（事件非报警）
#define DVR_ALMTYPE_SWITCH_STATUS_CHANGE 16         //信号量输入状态变化（事件非报警）
#define DVR_ALMTYPE_FIRE                17          //火警
#define DVR_ALMTYPE_PREALARM            18          //预警

//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位相关类型定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位事件
#define DVR_ALMTYPE_LN_TRIP             30      	//目标跨越警戒线
#define DVR_ALMTYPE_LN_ENTER            31          //目标进入区域
#define DVR_ALMTYPE_LN_EXIT             32      	//目标离开区域
#define DVR_ALMTYPE_LN_APPEAR           33          //目标出现
#define DVR_ALMTYPE_LN_DISAPPEAR        34          //目标消失
#define DVR_ALMTYPE_LN_LEFT             35      	//目标滞留（一定时间内移动距离小于规定要求）
#define DVR_ALMTYPE_LN_SOS              36      	//SOS求助
//////////////////////////////////////////////////////////////////////////////////////////////////////

//其他
#define DVR_ALMTYPE_LOSS_PHASE          46          //欠相
#define DVR_ALMTYPE_RESERVED_PHASE      47          //逆相
#define DVR_ALMTYPE_ABNORMAL_FREQUENCY  48          //频率异常
#define DVR_ALMTYPE_HIGH_VOLTAGE        49          //过压
#define DVR_ALMTYPE_LOW_VOLTAGE 		50      	//欠压（低电压）
#define DVR_ALMTYPE_BROKEN 			    51      	//设备被拆
#define DVR_ALMTYPE_SHORT_CIRCUIT 		52      	//设备短路
#define DVR_ALMTYPE_OPEN_CIRCUIT 		53      	//设备开路(掉电)

#define DVR_ALMTYPE_SLAVE_DEVICE_FAIL   60          //备用设备故障

//////////////////////////////////////////////////////////////////////////////////////////////////////
//智能分析相关类型定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define DVR_ALMTYPE_IVS_TRIP            115  	    //目标跨越警戒线
#define DVR_ALMTYPE_IVS_ENTER           116      	//目标进入区域
#define DVR_ALMTYPE_IVS_EXIT            117 	    //目标离开区域
#define DVR_ALMTYPE_IVS_APPEAR          118         //目标出现
#define DVR_ALMTYPE_IVS_DISAPPEAR       119     	//目标消失
#define DVR_ALMTYPE_IVS_MOVEAROUND      120  	    //目标徘徊
#define DVR_ALMTYPE_IVS_FACEDETECTION   121      	//人脸识别（分析目标仅针对人）
#define DVR_ALMTYPE_IVS_FACECAMPARE     122  	    //人脸比对（分析目标仅针对人）
#define DVR_ALMTYPE_IVS_LEFT            123  	    //目标滞留
#define DVR_ALMTYPE_IVS_CARCARDDETECTION 124        //车牌识别（分析目标仅针对车）
#define DVR_ALMTYPE_IVS_REVERSE         125      	//逆向
#define DVR_ALMTYPE_IVS_COUNT           126      	//数量统计
#define DVR_ALMTYPE_IVS_DENSITY         127      	//密度统计
#define DVR_ALMTYPE_IVS_GATHER          128      	//目标聚集
#define DVR_ALMTYPE_IVS_MOVE_UNEXPECTED 129      	//目标突然移动
//////////////////////////////////////////////////////////////////////////////////////////////////////


//模拟量输入报警标志
#define DVR_ANALOG_OVER_LOW_LIMIT1           1      //模拟量超下限1告警
#define DVR_ANALOG_OVER_HIGH_LIMIT1          2      //模拟量超上限1告警
#define DVR_ANALOG_OVER_LOW_LIMIT2           3      //模拟量超下限2告警
#define DVR_ANALOG_OVER_HIGH_LIMIT2          4      //模拟量超上限2告警

//参数配置：对应DVR_GetDVRConfig/DVR_SetDVRConfig
#define DVR_GET_TIMECFG                     1       //获取时间（对应数据结构为日期时间DVR_TIME）
#define DVR_SET_TIMECFG                     2       //设置时间（对应数据结构为日期时间DVR_TIME）
#define DVR_SET_DEPLOYALARMCFG              3       //设置布撤防信息（对应数据结构为布撤防信息DVR_ALARM_DEPLOYCFG）
#define DVR_GET_DEPLOYALARMCFG              4       //获取布撤防信息（对应数据结构为布撤防信息DVR_ALARM_DEPLOYCFG）
#define DVR_SET_SUBSCRIALARMCFG             5       //设置订阅告警信息（对应数据结构为告警事件订阅信息DVR_ALARM_SUBSCRIPTIONCFG）
#define DVR_GET_SUBSCRIALARMCFG             6       //获取订阅告警信息（对应数据结构为告警事件订阅信息DVR_ALARM_SUBSCRIPTIONCFG）
#define DVR_GET_OSDCFG                      7       //获取OSD配置（对应数据结构为OSD配置信息DVR_OSDCFG）
#define DVR_SET_OSDCFG                      8       //设置OSD配置（对应数据结构为OSD配置信息DVR_OSDCFG）
#define DVR_SET_PRESETCFG                   9       //设置预置点配置（对应数据结构为预置点配置信息DVR_PTZPRESETINFO）
#define DVR_GET_REGISTER_INFO_CFG           10      //获取DVR注册信息配置（对应数据结构为注册信息DVR_REGISTER_INFO）
#define DVR_GET_DEVICE_INFO_CFG             11      //获取设备资源列表配置（包括区域、摄像机、报警器、报警输出等逻辑设备资源列表）
#define DVR_GET_DEVICE_INFO_CFG_EX          12      //获取设备资源列表配置扩展（除逻辑设备，另含DVR、PCHost、门禁控制器等物理设备资源列表）
#define DVR_GET_DEVICE_INFO_CFG_V15         13      //获取设备资源列表配置V1.5版（包括区域、摄像机、报警器、报警输出等逻辑设备资源列表）
#define DVR_GET_DEVICE_INFO_CFG_V20         14      //获取设备资源列表配置V2.0版（包括区域、摄像机、报警器、报警输出等逻辑设备资源列表）
#define DVR_GET_RECORDCFG                   16      //获取录像配置
#define DVR_SET_RECORDCFG                   17      //设置录像配置
#define DVR_SET_SUBSCRISTATUSCFG            18      //设置订阅设备在线状态信息（对应数据结构为设备在线状态订阅信息DVR_STATUS_SUBSCRIPTIONCFG）
#define DVR_GET_SUBSCRISTATUSCFG            19      //获取订阅设备在线状态信息（对应数据结构为设备在线状态订阅信息DVR_STATUS_SUBSCRIPTIONCFG）
#define DVR_GET_PRESETINFOS                 20      //获取摄像机预置点数组信息（对应数据结构为预置点配置数组信息DVR_PTZPRESETINFOS）
#define DVR_SET_REGISTERSERVERCFG           21      //设置注册服务器配置（对应数据结构为注册服务器信息DVR_REGISTERSERVERINFO）
#define DVR_SET_AIRCONDITION_CFG            22      //设置空调配置（对应数据结构为空调参数配置DVR_AIR_CONDITION_CFG）
#define DVR_GET_AIRCONDITION_CFG            23      //获取空调配置（对应数据结构为空调参数配置DVR_AIR_CONDITION_CFG）
#define DVR_GET_PTZ_PATROL_CFG              24      //获取云台巡航配置（对应数据结构为云台巡航配置DVR_PTZ_PATROL_INFO）
#define DVR_SET_PTZ_PATROL_CFG              25      //设置云台巡航配置（对应数据结构为云台巡航配置DVR_PTZ_PATROL_INFO）
#define DVR_GET_PTZ_RESET_CFG               26      //获取云台守望配置（对应数据结构为云台守望配置参数DVR_PTZRESETINFO）
#define DVR_SET_PTZ_RESET_CFG               27      //设置云台守望配置（对应数据结构为云台守望配置参数DVR_PTZRESETINFO）
#define DVR_GET_IVS_CFG              		28      //获取智能视频分析配置（对应数据结构为智能视频分析配置DVR_IVS_CONFIG）
#define DVR_SET_IVS_CFG              		29      //设置智能视频分析配置（对应数据结构为智能视频分析配置DVR_IVS_CONFIG）
#define DVR_GET_TIME_SYNC_CFG               30      //获取对时时间配置（对应数据结构为系统对时参数DVR_TIME_SYNC）
#define DVR_SET_TIME_SYNC_CFG               31      //设置对时时间配置（对应数据结构为系统对时参数DVR_TIME_SYNC）
#define DVR_GET_ENCODE_CFG                  32      //获取视频编码配置（对应数据结构为编码配置信息DVR_VIDEO_ENCODECFG）
#define DVR_SET_ENCODE_CFG                  33      //设置视频编码配置（对应数据结构为编码配置信息DVR_VIDEO_ENCODECFG）
#define DVR_GET_HIDEAREA_CFG                34      //获取视频遮挡区域配置（对应数据结构为遮挡区域配置信息DVR_VIDEO_HIDEAREA）
#define DVR_SET_HIDEAREA_CFG                35      //设置视频遮挡区域配置（对应数据结构为遮挡区域配置信息DVR_VIDEO_HIDEAREA）
#define DVR_GET_ALM_MOTION_CFG              36      //获取视频移动侦测报警配置（对应数据结构为视频移动侦测报警参数DVR_ALM_VIDEO_MOTION）
#define DVR_SET_ALM_MOTION_CFG              37      //设置视频移动侦测报警配置（对应数据结构为视频移动侦测报警参数DVR_ALM_VIDEO_MOTION）
#define DVR_GET_ALM_HIDE_CFG                38      //获取视频遮挡检测报警配置（对应数据结构为视频遮挡侦测报警参数DVR_ALM_VIDEO_HIDE）
#define DVR_SET_ALM_HIDE_CFG                39      //设置视频遮挡检测报警配置（对应数据结构为视频遮挡侦测报警参数DVR_ALM_VIDEO_HIDE）
#define DVR_SET_ENV_ALARM_CFG               40      //设置模拟量告警参数（对应数据结构为模拟量告警参数DVR_ENV_ALARM_CFG）
#define DVR_GET_ENV_ALARM_CFG               41      //获取模拟量告警参数（对应数据结构为模拟量告警参数DVR_ENV_ALARM_CFG）
#define DVR_SET_SUBSCRI_DATA_CFG            42      //设置订阅数据信息（对应数据结构为数据订阅信息DVR_DATA_SUBSCRIPTIONCFG）
#define DVR_GET_SUBSCRI_DATA_CFG            43      //获取订阅数据信息（对应数据结构为数据订阅信息DVR_DATA_SUBSCRIPTIONCFG）

//参数配置(扩展)：对应DVR_GetDVRConfigEx/DVR_SetDVRConfigEx
#define DVR_GET_DEVICE_NAME_CFG_EX          100     //获取设备名称配置（包括摄像机、报警器、报警输出等逻辑设备）
#define DVR_SET_DEVICE_NAME_CFG_EX          101     //设置设备名称配置（包括摄像机、报警器、报警输出等逻辑设备）

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//空调控制相关定义
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DVR_GET_AC_CMD_CFG                  200    	//获取空调指令配置（对应数据结构为空调指令配置数组DVR_AC_CMD_CFGS）
#define DVR_SET_AC_CMD_CFG                  201    	//设置空调指令配置（对应数据结构为空调指令配置数组DVR_AC_CMD_CFGS）
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//门禁相关定义
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DVR_GET_DC_CAPABILITY               300    	//获取门禁能力（对应数据结构为门禁指令配置数组DVR_DC_CAPABILITY）
#define DVR_GET_DC_CFG                      301    	//获取门禁主机配置（对应数据结构为门禁主机配置DVR_DC_CONFIG）
#define DVR_GET_DC_DOOR_CFG                 302    	//获取门配置（对应数据结构为门配置DVR_DC_DOOR_CONFIG）
#define DVR_GET_DC_CARD_CFG                 303    	//获取门禁卡配置（对应数据结构为门禁卡配置DVR_DC_CARD_CONFIG）

#define DVR_SET_DC_CFG                      350    	//设置门禁主机配置（对应数据结构为门禁主机配置DVR_DC_CONFIG）
#define DVR_SET_DC_DOOR_CFG                 351    	//设置门配置（对应数据结构为门配置DVR_DC_DOOR_CONFIG）
#define DVR_SET_DC_CARD_CFG                 352    	//设置门禁卡配置（对应数据结构为门禁卡配置DVR_DC_CARD_CONFIG）
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//查找日志类型
#define DVR_LOG_ALL                         0       //所有日志
#define DVR_LOG_TYPE                        1       //按类型查找
#define DVR_LOG_TIME                        2       //按时间查找

//报警日志
#define DVR_MAJOR_ALARM                     0x1
#define DVR_MINOR_ALARM_IN                  0x1       //报警输入
#define DVR_MINOR_ALARM_OUT                 0x2       //报警输出
#define DVR_MINOR_MOTDET_START              0x3       //移动侦测报警开始
#define DVR_MINOR_MOTDET_STOP               0x4       //移动侦测报警结束
#define DVR_MINOR_HIDE_ALARM_START          0x5       //遮挡报警开始
#define DVR_MINOR_HIDE_ALARM_STOP           0x6       //遮挡报警结束
#define DVR_MINOR_SELF_DEF                  0x7       //自定义报警（16）
#define DVR_MINOR_ENLARGE_ALARM             0x8       //Ene扩展IO设备故障报警（1）
#define DVR_MINOR_ENLARGE_64_ALARM          0x9       //Ene64路IO扩展输入报警（16）
#define DVR_MINOR_ANALOG_ALARM              0xa       //模拟量设备故障报警（1）
#define DVR_MINOR_ANALOG_16_ALARM           0xb       //1～16路模拟量设备超限报警（16）
#define DVR_MINOR_ANALOG_SENSOR             0xc       //1～16路模拟量传感器故障报警（2）
#define DVR_MINOR_VIEW_DIVIDER              0xd       //外接画面分割器视频丢失报警（1）

 //异常日志
#define DVR_MAJOR_EXCEPTION                 0x2
#define DVR_MINOR_VI_LOST                   0x21      //视频信号丢失
#define DVR_MINOR_ILLEGAL_ACCESS            0x22      //非法访问
#define DVR_MINOR_HD_FULL                   0x23      //硬盘满
#define DVR_MINOR_HD_ERROR                  0x24      //硬盘错误
#define DVR_MINOR_DCD_LOST                  0x25      //MODEM 掉线(保留不使用)
#define DVR_MINOR_IP_CONFLICT               0x26      //IP地址冲突
#define DVR_MINOR_NET_BROKEN                0x27      //网络断开
#define DVR_MINOR_REC_ERROR                 0x28      //录像出错--获取录像文件失败
#define DVR_MINOR_IPC_NO_LINK               0x29      //IPC连接断开
#define DVR_MINOR_VI_EXCEPTION              0x2a      //视频输入异常

//操作日志
#define DVR_MAJOR_OPERATION                 0x3
#define DVR_MINOR_START_DVR                 0x41      //开机
#define DVR_MINOR_STOP_DVR                  0x42      //本地关机
#define DVR_MINOR_STOP_ABNORMAL             0x43      //非法关机
#define DVR_MINOR_REBOOT_DVR                0X44      //本地重启
#define DVR_MINOR_LOCAL_LOGIN               0x50      //本地登陆
#define DVR_MINOR_LOCAL_LOGOUT              0x51      //本地注销
#define DVR_MINOR_LOCAL_CFG_PARM            0x52      //本地参数配置
#define DVR_MINOR_LOCAL_PLAYBYFILE          0x53      //本地按文件回放
#define DVR_MINOR_LOCAL_PLAYBYTIME          0x54      //本地按时间回放
#define DVR_MINOR_LOCAL_START_REC           0x55      //本地开始录像
#define DVR_MINOR_LOCAL_STOP_REC            0x56      //本地停止录像
#define DVR_MINOR_LOCAL_PTZCTRL             0x57      //本地云台控制
#define DVR_MINOR_LOCAL_PREVIEW             0x58      //本地预览 (保留不使用)
#define DVR_MINOR_LOCAL_MODIFY_TIME         0x59      //本地修改时间(保留不使用)
#define DVR_MINOR_LOCAL_UPGRADE             0x5a      //本地升级
#define DVR_MINOR_LOCAL_RECFILE_OUTPUT      0x5b      //本地备份录象文件
#define DVR_MINOR_LOCAL_FORMAT_HDD          0x5c      //本地初始化硬盘
#define DVR_MINOR_LOCAL_CFGFILE_OUTPUT      0x5d      //地导出配置文件
#define DVR_MINOR_LOCAL_CFGFILE_INPUT       0x5e      //本地导入配置文件
#define DVR_MINOR_LOCAL_COPYFILE            0x5f      //本地备份文件
#define DVR_MINOR_LOCAL_LOCKFILE            0x60      //本地锁定录像文件
#define DVR_MINOR_LOCAL_UNLOCKFILE          0x61      //本地解锁录像文件
#define DVR_MINOR_LOCAL_DVR_ALARM           0x62      //本地手动清除和触发报警
#define DVR_MINOR_IPC_ADD                   0x63      //本地添加IPC
#define DVR_MINOR_IPC_DEL                   0x64      //本地删除IPC
#define DVR_MINOR_IPC_SET                   0x65      //本地设置IPC
#define DVR_MINOR_REMOTE_LOGIN              0x70      //远程登录
#define DVR_MINOR_REMOTE_LOGOUT             0x71      //远程注销
#define DVR_MINOR_REMOTE_START_REC          0x72      //远程注销
#define DVR_MINOR_REMOTE_STOP_REC           0x73      //远程注销
#define DVR_MINOR_START_TRANS_CHAN          0x74      //开始透明传输
#define DVR_MINOR_STOP_TRANS_CHAN           0x75      //停止透明传输
#define DVR_MINOR_REMOTE_GET_PARM           0x76      //远程获取参数
#define DVR_MINOR_REMOTE_CFG_PARM           0x77      //远程配置参数
#define DVR_MINOR_REMOTE_GET_STATUS         0x78      //远程获取状态
#define DVR_MINOR_REMOTE_ARM                0x79      //远程布防
#define DVR_MINOR_REMOTE_DISARM             0x7a      //远程撤防
#define DVR_MINOR_REMOTE_REBOOT             0x7b      //远程重启
#define DVR_MINOR_START_VT                  0x7c      //开始语音对讲
#define DVR_MINOR_STOP_VT                   0x7d      //停止语音对讲
#define DVR_MINOR_REMOTE_UPGRADE            0x7e      //远程升级
#define DVR_MINOR_REMOTE_PLAYBYFILE         0x7f      //远程按文件回放或下载
#define DVR_MINOR_REMOTE_PLAYBYTIME         0x80      //远程按时间回放或下载
#define DVR_MINOR_REMOTE_PTZCTRL            0x81      //远程云台控制
#define DVR_MINOR_REMOTE_FORMAT_HDD         0x82      //远程格式化硬盘
#define DVR_MINOR_REMOTE_STOP               0x83      //远程关机
#define DVR_MINOR_REMOTE_LOCKFILE           0x84      //远程锁定文件
#define DVR_MINOR_REMOTE_UNLOCKFILE         0x85      //远程解锁文件
#define DVR_MINOR_REMOTE_CFGFILE_OUTPUT     0x86      //远程导出配置文件
#define DVR_MINOR_REMOTE_CFGFILE_INPUT      0x87      //远程导入配置文件
#define DVR_MINOR_REMOTE_RECFILE_OUTPUT     0x88      //远程导出录象文件
#define DVR_MINOR_REMOTE_DVR_ALARM          0x89      //远程手动清除和触发报警
#define DVR_MINOR_REMOTE_IPC_ADD            0x8a      //远程添加IPC
#define DVR_MINOR_REMOTE_IPC_DEL            0x8b      //远程删除IPC
#define DVR_MINOR_REMOTE_IPC_SET            0x8c      //远程设置

//信息日志
#define DVR_MAJOR_INFORMATION               0x4
#define DVR_MINOR_HDD_INFO                  0xa1      //硬盘信息
#define DVR_MINOR_SMART_INFO                0xa2      //SMART信息
#define DVR_MINOR_REC_START                 0xa3      //开始录像
#define DVR_MINOR_REC_STOP                  0xa4      //停止录像
#define DVR_MINOR_REC_OVERDUE               0xa5      //过期录像删除
#define DVR_MINOR_ANALOG_DATA               0xa6      //模拟量数据

#define DVR_MAJOR_HD_EXC                    0x80      //减少硬盘消息--硬盘格式化或硬盘错误
#define DVR_MAJOR_NEW_HD                    0x81      //增加硬盘消息--刚刚格式化过的硬盘

//空调工作模式
#define DVR_AC_WORK_UNKOWN                  -1        //未知
#define DVR_AC_WORK_COLD                    0         //制冷
#define DVR_AC_WORK_WARM                    1         //制热
#define DVR_AC_WORK_RMHUM                   2         //除湿
#define DVR_AC_WORK_WIND                    3         //送风
#define DVR_AC_WORK_AUTO                    4         //自动

//空调计划模式
#define DVR_AC_PLAN_NONE                    0         //恒定
#define DVR_AC_PLAN_BY_MONTH                1         //按月
#define DVR_AC_PLAN_BY_SEASON               2         //按季

//////////////////////////////////////////////////////////////////////////////////////////////////////
//智能分析相关类型定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//智能视频分析目标类型
#define DVR_IVS_TARGET_UNKNOWN              0x0       //未指定
#define DVR_IVS_TARGET_HUMAN                0x1       //人
#define DVR_IVS_TARGET_VEHICLE              0x2       //车
#define DVR_IVS_TARGET_FIRE                 0x4  	  //火
#define DVR_IVS_TARGET_HEAT                 0x8  	  //热
#define DVR_IVS_TARGET_LIGHT                0x10 	  //光
#define DVR_IVS_TARGET_SMOKE                0x20 	  //烟
#define DVR_IVS_TARGET_OBJECT               0x40 	  //物体

//////////////////////////////////////////////////////////////////////////////////////////////////////
//人脸识别相关
//人员类型
#define DVR_IVS_FACE_PERSON_UNKNOWN     	0x00       //未知
#define DVR_IVS_FACE_PERSON_RESIDENT    	0x01       //常驻人员
#define DVR_IVS_FACE_PERSON_IMPORTANT    	0x02       //重点人员
#define DVR_IVS_FACE_PERSON_ESCAPEE       	0x03       //在逃人员
#define DVR_IVS_FACE_PERSON_FLOW       		0x04       //流动人员
#define DVR_IVS_FACE_PERSON_NACOTICS_RELATED    0x05   //涉毒人员
#define DVR_IVS_FACE_PERSON_COLLECTION     	0x06       //实时采集人员


#define DVR_IVS_FACE_PERSON_TERRORIST       0x07       //涉恐人员库
#define DVR_IVS_FACE_PERSON_PETITIONER      0x08       //涉访人员库
#define DVR_IVS_FACE_PERSON_REACTIONIST     0x09       //涉稳人员库
#define DVR_IVS_FACE_PERSON_SINKIANG        0x0A       //涉疆人员库

//以下定义仅适用于司法监管场所
#define DVR_IVS_FACE_PERSON_POLICE     		0x51       //内部民警
#define DVR_IVS_FACE_PERSON_EMPLOYEE     	0x52       //内部职员
#define DVR_IVS_FACE_PERSON_INTERVIEW     	0x53       //探视人员
#define DVR_IVS_FACE_PERSON_OUTCOMER     	0x54       //外来人员
#define DVR_IVS_FACE_PERSON_FOREIGN_DRIVER 	0x55       //外来司机
#define DVR_IVS_FACE_PERSON_INTERNAL_DRIVER	0x56       //内部司机
#define DVR_IVS_FACE_PERSON_PRISONER		0x57       //服刑人员

//人脸数据类型
#define DVR_IVS_FACE_DATA_DISPLAY_PHOTO     0x00       //显示用人脸照片（JPG格式）
#define DVR_IVS_FACE_DATA_CARD_PHOTO        0x01       //身份证小照片（BMP格式）
#define DVR_IVS_FACE_DATA_REGISTER_PHOTO    0x02       //注册人脸图片（JPG格式）
#define DVR_IVS_FACE_DATA_VERIFY_PHOTO      0x03       //认证人脸照片（JPG格式）
#define DVR_IVS_FACE_DATA_VERIFY_PICTURE    0x04       //认证原始图片（JPG格式）
#define DVR_IVS_FACE_DATA_FEATURE           0x05       //用户特征码文件
#define DVR_IVS_FACE_DATA_FEATURE2          0x06       //用户特征码文件2
//////////////////////////////////////////////////////////////////////////////////////////////////////


//
//登录信息
typedef struct
{
    char szDvrIP[DVR_IP_LEN];                       //IP地址
    unsigned short usDvrPort;                       //端口
    unsigned short usReserved;
    char szDvrUserName[DVR_USR_LEN];                //用户名
    char szDvrPassword[DVR_PASS_LEN];               //密码
    //保留参数
    char szDvrIP2[DVR_IP_LEN];                      //IP地址
    unsigned short usDvrPort2;                      //端口
    unsigned short usReserved2;
} DVR_LOGININFO, *PDVR_LOGININFO;

//登录信息_V20
typedef struct
{
    char szDvrIP[DVR_FILENAME_LEN];                	//IP地址或设备访问Url
    unsigned short usDvrPort;                       //端口
    unsigned short usReserved;
    char szDvrUserName[DVR_USR_LEN];                //用户名
    char szDvrPassword[DVR_PASS_LEN];               //密码
    //保留参数
    char szDvrIP2[DVR_IP_LEN];                      //IP地址
    unsigned short usDvrPort2;                      //端口
    unsigned short usReserved2;
} DVR_LOGININFO_V20, *PDVR_LOGININFO_V20;

//绘图初始化信息
typedef struct
{
    unsigned long winid;                            //窗口ID
    int width;                                      //窗口宽度
    int height;                                     //窗口高度
}DVR_INITINFO, *PDVR_INITINFO;

//帧结构信息
typedef struct
{
    int iWidth;                                     //图像宽度
    int iHeight;                                    //图像高度
    int iFrameType;                                 //图像格式
    void* data[4];                                  //图像数据
    int linesize[4];                                //图像行大小
    unsigned int uiTimeStamp;                       //帧时间戳(time_t秒)
    unsigned int uiTimeStampExt;                    //帧时间戳(毫秒)
    unsigned int uiSequence;                        //帧序号
} DVR_FRAMEINFO;    

//编码配置信息
typedef struct
{
    DVR_DEV_ID        iVideoId;                     //视频ID(实际设备：物理编号，从1开始；代理或平台：全局编号）
    struct
    {
        int           iEnable;                      //是否使能（0-否，1-是）
        int           iCompression;                 //压缩模式
        int           iResolution;                  //分辨率
        int           iBitRateControl;              //码流控制模式，
        int           iQuality;                     //码流画质 [1,6]
        int           iFPS;                         //帧率值 [1,25]
        int           iBitRate;                     //码流值（kbps）
        int           iGOP;                         //I 帧之间的 P帧个数[0,149]
        int           iFlag;                        //主辅码流标记，0-主码流,1-第1辅码流,2-第2辅码流,3-第3辅码流
    } EncodeCfg[4];
} DVR_VIDEO_ENCODECFG, *PDVR_VIDEO_ENCODECFG;                 

//遮挡区域配置信息
typedef struct
{
    DVR_DEV_ID        iVideoId;                     //视频ID(实际设备：物理编号，从1开始；代理或平台：全局编号）
    struct
    {
        int           iEnable;                       //是否使能区域屏蔽（0-否，1-是）
        int           iX;                            //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iY;                            //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iWidth;                        //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iHeight;                       //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
    } Area[4];
} DVR_VIDEO_HIDEAREA, *PDVR_VIDEO_HIDEAREA;              

//视频移动侦测报警参数
typedef struct
{
    DVR_DEV_ID        iVideoId;                      //视频ID(实际设备：物理编号，从1开始；代理或平台：全局编号）
    struct
    {
        int           iEnable;                       //是否使能移动侦测（0-否，1-是）
        int           iSensitivity;                  //移动侦测灵敏度(1--8)
        int           iX;                            //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iY;                            //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iWidth;                        //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iHeight;                       //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
    } Area[4];
} DVR_ALM_VIDEO_MOTION, *PDVR_ALM_VIDEO_MOTION;

//遮挡检测报警参数
typedef struct      
{
    DVR_DEV_ID        iVideoId;                      //视频ID(实际设备：物理编号，从1开始；代理或平台：全局编号）
    struct
    {
        int           iEnable;                       //是否使能遮挡检测报警（0-否，1-是）
        int           iX;                            //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iY;                            //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iWidth;                        //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
        int           iHeight;                       //坐标按图像左上角（0，0），右下角（704，576）的比例进行映射换算
    } Area[4];
} DVR_ALM_VIDEO_HIDE, *PDVR_ALM_VIDEO_HIDE;

//模拟量告警参数
typedef struct
{
	DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int iDevSubType;                                //设备子类型
    int iAlmState;                                  //布撤防状态(1-布防,0-撤防)
    float fMaxValue1;                               //超上限1告警
    float fMaxValue2;                               //超上限2告警
    float fMinValue1;                               //超下限1告警
    float fMinValue2;                               //超下限2告警
}DVR_ENV_ALARM_CFG,*PDVR_ENV_ALARM_CFG;

//日期时间
typedef struct
{
    unsigned long ulYear;                           //年
    unsigned long ulMonth;                          //月
    unsigned long ulDay;                            //日
    unsigned long ulHour;                           //小时
    unsigned long ulMinute;                         //分钟
    unsigned long ulSecond;                         //秒
} DVR_TIME, *PDVR_TIME;

//系统对时参数
typedef struct
{
    DVR_TIME			Time;
    char   	            szNtpServerAddr1[32];
    char                szNtpServerAddr2[32];
    char                szNtpServerAddr3[32];
    int    				iTimeZone;                  //GMT时区,[-12, 12]
} DVR_TIME_SYNC, *PDVR_TIME_SYNC;

//客户端信息
typedef struct
{
     DVR_DEV_ID lChannel;                           //通道号(实际设备：物理编号，从1开始；代理或平台：全局编号）
     long lLinkMode;                                //连接方式 0:TCP方式; 1:UDP 方式; 2:多播方式; 3:RTP方式; 4:音频分开
     long lVideoFlag;                               //主副码流 0:主码流；1:子码流1；2:子码流2；3:子码流2
     char szMultiCastIP[DVR_IP_LEN];                //多播组地址
     DVR_HWND hPlayWnd;                             //播放窗口句柄
 } DVR_CLIENTINFO, *PDVR_CLIENTINFO;

//扩增云台控制信息
//命令类型             m_iParam1      m_iParam2        m_iParam3      m_iParam4      m_iParam5      m_iParam6
//上下左右方向控制     速度 
//斜角方向控制         水平速度       垂直速度
//预置位控制           预置位号
//3D定位               左上角X坐标    左上角Y坐标      右下角X坐标    右下角Y坐标    画面宽度       画面高度
typedef struct 
{
    int             m_iPtzCmd;                      //控制命令
    int             m_iParam1;                      //控制命令的参数1
    int             m_iParam2;                      //控制命令的参数2
    int             m_iParam3;                      //控制命令的参数3
    int             m_iParam4;                      //控制命令的参数4
    int             m_iParam5;                      //控制命令的参数5
    int             m_iParam6;                      //控制命令的参数6
    int             m_iParam7;                      //控制命令的参数7
    int             m_iParam8;                      //控制命令的参数8
} DVR_PTZCTLEX, *PDVR_PTZCTLEX;

//云台预置点信息
typedef struct
{
    int             iIndex;                         //预置点序号，从1开始
    char            szName[128];                    //预置点名称
    DVR_DEV_ID      lChannel;                       //视频通道号(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int             iStatus;                        //状态
} DVR_PTZPRESETINFO, *PDVR_PTZPRESETINFO;

//云台预置点信息数组
typedef struct
{
    unsigned int         uiPresetCount;             //预置点数量
    DVR_PTZPRESETINFO    presetInfos[];             //预置点信息数组
} DVR_PTZPRESETINFOS, *PDVR_PTZPRESETINFOS;

//云台巡航点配置信息
typedef struct  
{
    int             iIndex;                         //预置点序号，从1开始
    int             iDuration;                      //持续时间（秒）
    int             iSpeed;                         //切换运行速度（1-8）
} DVR_PTZ_PATROL_POINT_INFO;

//云台巡航配置信息
typedef struct  
{
    DVR_DEV_ID      lChannel;                       //视频通道号(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int             iPatrolId;                      //巡航编号
    int             iPointCount;                    //巡航点个数
    DVR_PTZ_PATROL_POINT_INFO PointInfos[];         //巡航点配置信息数组
} DVR_PTZ_PATROL_INFO;

//录像查找信息
typedef struct
{
     char szFileName[DVR_FILENAME_LEN];             //文件名
     DVR_TIME timeStart;                            //文件开始时间
     DVR_TIME timeStop;                             //文件结束时间
     unsigned long unFileSize;                      //文件大小(单位：KB）
     unsigned int uiDecodeType;                     //解码器类型
     DVR_DEV_ID lChannel;                           //通道号(实际设备：物理编号，从1开始；代理或平台：全局编号）
     long lFileSource;                              //文件源
     unsigned long ulFileType;                      //文件类型
     char szFileUrl[DVR_FILENAME_LEN];              //录像访问URL 
} DVR_FIND_DATA, *PDVR_FIND_DATA;

//语音对讲信息
typedef struct
{
    DVR_DEV_ID lChannel;                            //通道号(实际设备：物理编号，从1开始；代理或平台：全局编号）
    long lMode;                                     //模式（1:对讲;2:广播;3:监听）
} DVR_VOICEINFO, *PDVR_VOICEINFO;

//设备状态
typedef struct
{
    DVR_DEV_ID  llDevId;                            //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
	int         iStatus;                            //在线状态
	float fCPU;                                     //CPU 使用率
    float fMem;                                     //内存使用率
    float fDisk;                                    //硬盘使用率
    DVR_TIME timeState;                             //机器时间
    unsigned long ulTotalBand;                      //总带宽（值为-1，表示不支持）
    unsigned long ulFreeBand;                       //空闲带宽（值为-1，表示不支持）
    unsigned long ulLoginCount;                     //登录用户数（值为-1，表示不支持）
    unsigned long ulStreamCount;                    //流传输数（值为-1，表示不支持）
}DVR_WORKSTATE, *PDVR_WORKSTATE;

//DVR设备状态数组
typedef struct
{
    unsigned int         uiDVRCount;               //DVR数量
    DVR_WORKSTATE        workStates[];             //DVR状态数组
} DVR_WORKSTATES, *PDVR_WORKSTATES;

//摄像机状态
typedef struct
{
    DVR_DEV_ID  llDevId;                           //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevSubType;                              //设备子类型
    unsigned int uiReserved;                       //保留
    int iRecordStatus;                             //通道是否在录像：0－未知；1－录像；2-不录像
    int iVideoLost;                                //视频状态：0－未知；1－正常，2－信号丢失
    int iVideoCovered;                             //视频遮挡状态：0－未知；1－正常，2－遮挡
    int iMotionDection;                            //动态侦测状态：0－未知；1－正常，2－侦测
    int iDSPStatus;                                //DSP状态：0－未知；1－正常，2－异常
    unsigned long ulLinkNum;                       //连接客户端个数
} DVR_CAMERASTATE, *PDVR_CAMERASTATE;

//摄像机状态数组
typedef struct
{
    unsigned int         uiCameraCount;            //摄像机数量
    DVR_CAMERASTATE      cameraStates[];           //摄像机状态数组
} DVR_CAMERASTATES, *PDVR_CAMERASTATES;

//模拟量报警信息
typedef struct
{
    double dEnvData;                                //当前模拟量的值
    int  iAlmFlag;                                  //1:超下限1告警;2:超上限1告警;3:超下限2告警;4:超上限2告警
} DVR_ENV_ALARM_INFO, *PDVR_ENV_ALARM_INFO;

//门报警信息
typedef struct
{
    int  iDevStatus;                                //门状态
    unsigned int OperationKind;                     //门操作种类 
    char szCardNo[32];                              //卡号，刷卡开门有效
    char szName[16];                                //姓名，刷卡开门有效
    char szRes[24];                                 //额外信息
	unsigned int uiDirection;                     	//进出方向,0：未知，1：进，2：出
	unsigned int uiReserved2;                       //保留2
} DVR_DOOR_ALARM_INFO, *PDVR_DOOR_ALARM_INFO;

//SCADA报警信息
typedef struct
{
    char  szSwitchId[32];                           //开关刀闸代码及名称描述
    short shType;                                   //联动类型，0:遥控预置 1:遥信变位
    unsigned short usReserved;                      //保留
} DVR_SCADA_ALARM_INFO, *PDVR_SCADA_ALARM_INFO;

//消防系统报警信息
typedef struct 
{
    int iAddrId; 		                            //设备Id（探测器1-99，模块101-199）
    int iZoneNo; 		                            //区域Id（从0开始0-19）
    int iBuildingNo;	                            //栋Id（从0开始0-19）
    int iFloorNo;  	                                //层Id（-10-200层）
    int iRoomNo;   	                                //房间（0-255）
    char szDesc[64];								//位置描述，长度为64，以0结尾的字符串
} DVR_FIRE_ALARM_INFO;

//智能视频分析报警信息
typedef struct 
{
	int iTargetId;                                  //目标ID
    short shTargetType;                             //目标类型（详见“智能视频分析目标类型”宏定义）
    short shRuleId;                                 //分析规则ID
    char szDesc[64];								//详细描述，长度为64，以0结尾的字符串
} DVR_ANALYSE_ALARM_INFO;

//报警器状态
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevSubType;                               //设备子类型
    int  iAlarmState;                               //报警状态，0-正常状态，1-报警状态
    int  iAlarmType;                                //报警事件类型
    char szAlarmInfo[64];                           //事件信息描述
    unsigned int uiDigitalValue;                    //将保留字段用作信号量输入状态，0-表示开启，1-表示闭合
    //以下数据部分内容仅发生报警后生效
    union
    {
        DVR_ENV_ALARM_INFO evnInfo;                 //模拟量报警信息
        DVR_DOOR_ALARM_INFO doorInfo;               //门报警信息
        DVR_SCADA_ALARM_INFO scadaInfo;             //SCADA报警信息
		DVR_FIRE_ALARM_INFO fireInfo;               //消防报警信息
		DVR_ANALYSE_ALARM_INFO AnalyseInfo;         //智能视频分析报警信息
    };
} DVR_ALARMSTATE, *PDVR_ALARMSTATE;

//报警器状态数组
typedef struct
{
    unsigned int        uiAlarmCount;               //报警器数量
    DVR_ALARMSTATE      alarmStates[];              //报警器状态数组
} DVR_ALARMSTATES, *PDVR_ALARMSTATES;

//报警输出状态
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevSubType;                               //设备子类型
	union
	{
		struct
		{
			int  iAlarmState;                       //输出状态,1-打开，0-关闭
			unsigned int uiDigitalValue;            //信号量输出数值
        };
		double fValue;								//模拟量数值
    };
} DVR_OUTPUTSTATE, *PDVR_OUTPUTSTATE;

//报警输出状态数组
typedef struct
{
    unsigned int        uiOutputCount;              //报警输出数量
    DVR_OUTPUTSTATE     OutputStates[];             //报警输出状态数组
} DVR_OUTPUTSTATES, *PDVR_OUTPUTSTATES;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位相关结构定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位报警信息
typedef struct
{
	DVR_DEV_ID llMapId;    			                //地图Id(全局编号)
    float fRealWorldPosX;                           //真实世界x坐标(单位:米)
    float fRealWorldPosY;                           //真实世界y坐标(单位:米)
	short shRuleId;                                 //报警规则ID
} DVR_LOCATION_ALARM_INFO;

//定位节点状态
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevSubType;                               //设备子类型
    int  iAlarmState;                               //报警状态，0-正常状态，1-报警状态
    int  iAlarmType;                                //报警事件类型
    char szAlarmInfo[64];                           //事件信息描述
    DVR_LOCATION_ALARM_INFO locationInfo;           //定位信息
} DVR_LOCATIONSTATE, *PDVR_LOCATIONSTATE;

//定位节点状态数组
typedef struct
{
    unsigned int        uiLocationCount;            //定位节点数量
    DVR_LOCATIONSTATE   locationStates[];           //定位节点状态数组
} DVR_LOCATIONSTATES, *PDVR_LOCATIONSTATES;
//////////////////////////////////////////////////////////////////////////////////////////////////////


//设备报警上传信息（适用于所有类型设备）
typedef struct
{
    DVR_DEV_ID  llDevId;                            //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevType;                                  //设备类型，选择使用
    int  iDevSubType;                               //设备子类型，选择使用
    int  iAlarmState;                               //报警状态，0-正常状态，1-报警状态
    int  iAlarmType;                                //报警事件类型
    char szAlarmInfo[64];                           //事件信息描述
    unsigned int uiDigitalValue;                    //将保留字段用作信号量输入状态，0-表示开启，1-表示闭合
    union
    {
        DVR_ENV_ALARM_INFO evnInfo;                 //模拟量报警信息
        DVR_DOOR_ALARM_INFO doorInfo;               //门报警信息
        DVR_SCADA_ALARM_INFO scadaInfo;             //SCADA报警信息
		DVR_FIRE_ALARM_INFO fireInfo;               //消防报警信息
		DVR_ANALYSE_ALARM_INFO AnalyseInfo;         //智能视频分析报警信息
        DVR_LOCATION_ALARM_INFO locationInfo;       //定位信息
    };
} DVR_ALARM_INFO, *PDVR_ALARM_INFO;

//模拟量数据上报
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevType;                                  //设备类型
    int  iDevSubType;                               //设备子类型
    double dEnvData;                                //模拟量数值
} DVR_ENV_REPORT;

//信号量数据上报
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevType;                                  //设备类型
    int  iDevSubType;                               //设备子类型
    unsigned int uiDigitalValue;                    //信号量输入状态，0-表示开启，1-表示闭合
} DVR_SWITCH_REPORT;

//摄像机联动信息
typedef struct      
{
    DVR_DEV_ID llDevId;                             //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int        iPresetIndex;                        //摄像机预置点，从1开始
    int        iRecord;                             //录像状态，0-不录像，1-录像
    int        iCapture;                            //抓图，0-不抓图，1-抓图
} DVR_CAMERA_LINKAGE_INFO;

//报警输出联动信息
typedef struct      
{
    DVR_DEV_ID llDevId;                            //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevSubType;                              //设备子类型
    int  iAlarmState;                              //输出状态
} DVR_OUTPUT_LINKAGE_INFO;

//布撤防信息
typedef struct
{
    unsigned int uiDevType;                         //设备类型，0xffffffff表示所有类型
    unsigned int uiDevSubType;                      //设备子类型，0xffffffff表示所有子类型
    DVR_DEV_ID llDevId;                             //设备Id,0表示该类型所有设备(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int iAlmState;                                  //布撤防状态(1-布防,0-撤防)
    unsigned int uiCameraCount;                     //联动摄像机数量
    unsigned int uiOutputCount;                     //联动报警输出数量
    DVR_CAMERA_LINKAGE_INFO CameraLinkageInfos[16]; //摄像机联动信息数组
    DVR_OUTPUT_LINKAGE_INFO OutputLinkageInfos[16]; //报警输出联动信息数组
} DVR_ALARM_DEPLOYCFG, *PDVR_ALARM_DEPLOYCFG;

//告警事件订阅信息
typedef struct
{
    unsigned int uiDevType;                         //设备类型，0xffffffff表示所有类型
    unsigned int uiDevSubType;                      //设备子类型，0xffffffff表示所有子类型
    DVR_DEV_ID llDevId;                             //设备Id，0表示该类型所有设备(实际设备：物理编号，从1开始；代理或平台：全局编号）
    unsigned int uiAlmeEventType;                   //告警事件类型，0xffffffff表示所有告警事件
    unsigned int uiExpires;                         //订阅期限（秒），0xffffffff表示无限期
} DVR_ALARM_SUBSCRIPTIONCFG, *PDVR_ALARM_SUBSCRIPTIONCFG;

//设备在线状态订阅信息
typedef struct
{
    unsigned int uiDevType;                         //设备类型，0xffffffff表示所有类型
    unsigned int uiDevSubType;                      //设备子类型，0xffffffff表示所有子类型
    DVR_DEV_ID llDevId;                             //设备Id，0表示该类型所有设备(实际设备：物理编号，从1开始；代理或平台：全局编号）
    unsigned int uiExpires;                         //订阅期限（秒），0xffffffff表示无限期
} DVR_STATUS_SUBSCRIPTIONCFG, *PDVR_STATUS_SUBSCRIPTIONCFG;

//数据订阅信息
typedef struct
{
    unsigned int uiDevType;                         //设备类型，0xffffffff表示所有类型
    unsigned int uiDevSubType;                      //设备子类型，0xffffffff表示所有子类型
    DVR_DEV_ID llDevId;                             //设备Id，0表示该类型所有设备(实际设备：物理编号，从1开始；代理或平台：全局编号）
    unsigned int uiDataType;                        //数据类型，0xffffffff表示所有类型数据,0表示模拟量,1表示设备运行数据
    unsigned int uiExpires;                         //订阅期限（秒），0xffffffff表示无限期
} DVR_DATA_SUBSCRIPTIONCFG, *PDVR_DATA_SUBSCRIPTIONCFG;

//日志信息
typedef struct
{
    long lMajorType;                                //主类型
    long lMinorType;                                //次类型
    DVR_TIME logTime;                               //log发生时间
    DVR_DEV_ID llDevId;                             //设备Id(实际设备：未使用；代理或平台：全局编号）
    char szUser[64];                                //用户
    char szHostIp[DVR_IP_LEN];                      //主机IP
    char szLogData[368];                            //log内容
} DVR_LOG, *PDVR_LOG;

//OSD配置信息
typedef struct
{
    DVR_DEV_ID  iVideoId;                           //视频ID(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iOsd_1_x;                                  //x和y坐标和宽高按图像左上角（0，0），右下角（704，576）的比例进行映射换算。
    int  iOsd_1_y;
    char szOsd_1_text[128];                         //字符数为0表示无OSD
    unsigned int uiOsd_1_BGColor;                   //OSD1背景色（缺省值为0xaarrggbb）
    int  iOsd_2_x;
    int  iOsd_2_y;
    char szOsd_2_text[128];
    unsigned int uiOsd_2_BGColor;                   //OSD2背景色
    int  iOsd_3_x;
    int  iOsd_3_y;
    char szOsd_3_text[128];
    unsigned int uiOsd_3_BGColor;                   //OSD3背景色
    int  iOsd_4_x;
    int  iOsd_4_y;
    char szOsd_4_text[128];
    unsigned int uiOsd_4_BGColor;                   //OSD4背景色
} DVR_OSDCFG, *PDVR_OSDCFG;

//注册信息
typedef struct
{
    DVR_DEV_ID          llDevId;                    //设备Id(全局编号）
    char                szName[128];                //设备名称
    int                 iDvrType;                   //Dvr类型
    char                szIp[32];                   //设备IP
    int                 iPort;                      //设备网络端口
    char                szServerIp[32];             //服务器IP
    int                 iServerPort;                //服务器网络端口
    int                 iMajorType;                 //主类型
    int                 iMinorType;                 //子类型
    char                szModel[32];                //型号
    char                szSerialId[64];             //序列号
    char                szVersion[64];              //版本号
    int                 iHeartBeatInterval;         //心跳间隔（秒）
    char                szRemark[64];               //描述
} DVR_REGISTER_INFO,*PDVR_REGISTER_INFO;

//摄像机扩展数据
struct CameraExtData
{
    char szDecoderName[64];                         //解码器名称
};

//定位标签扩展数据
struct LocationExtData
{
	DVR_DEV_ID llRegionId;    			            //区域Id(全局编号)
	DVR_DEV_ID llMapId;    			                //地图Id(全局编号)
	DVR_DEV_ID llPersonId;    			            //人员Id(全局编号)
    float fRealWorldPosX;							//真实世界x坐标(单位:米)
    float fRealWorldPosY;							//真实世界y坐标(单位:米)
};

//人员扩展数据
struct PersonExtData
{
    char szWorkNum[8];                              //工号
    char szPersonNum[19];                         	//身份证号
    char szCardNum[9];                           	//卡号
	DVR_DEV_ID llDutyId;    			           	//岗位Id(全局编号)
	DVR_DEV_ID llDepartmentId;    			        //机构Id(全局编号)
    unsigned short usSex;						    //性别,0-男,1-女，,255-其他
    unsigned short usAge;						    //年龄
	unsigned int uiRegisterDateTime;				//登记日期时间
	unsigned short usValidDay;				        //有效天数，0表示不限制
	unsigned short usRemainDay;				        //剩余天数,0表示已过期
};

//上传设备信息（适用于监控场景、电子地图以外类型的设备）
typedef struct
{
    DVR_DEV_ID          llDevId;                    //设备Id(全局编号）
    char                szName[128];                //设备名称
    int                 iDevType;                   //设备类型
    DVR_DEV_ID          llParentDevId;              //父设备Id(全局编号）
    int                 iStatus;                    //在线状态
    unsigned int        uiAlarmLevel;               //告警级别
    unsigned int        uiReserved;                 //保留
    union
    {
        struct CameraExtData   cedCameraExtData;
        struct LocationExtData ledLocationExtData;
        struct PersonExtData   pedPersonExtData;
    };
} DVR_DEVICEINFO, *PDVR_DEVICEINFO;

//上传设备信息数组
typedef struct
{
    unsigned int        uiDeviceCount;              //设备数量
    DVR_DEVICEINFO      DeviceInfos[];              //设备数组
} DVR_DEVICEINFOS, *PDVR_DEVICEINFOS;


//上传设备信息V1.5版（适用于监控场景、电子地图以外类型的设备）
typedef struct
{
    DVR_DEV_ID          llDevId;                    //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号)
    char                szName[128];                //设备名称
    int                 iDevType;                   //设备类型
	int                 iDevSubType;                //设备子类型
    DVR_DEV_ID          llParentDevId;              //父设备Id(全局编号）
    int                 iStatus;                    //在线状态
    unsigned int        uiAlarmLevel;               //告警级别
	DVR_DEV_ID          llGlobalCode;               //全局编号
    unsigned int        uiReserved;                 //保留
    union
    {
        struct CameraExtData   cedCameraExtData;
        struct LocationExtData ledLocationExtData;
        struct PersonExtData   pedPersonExtData;
    };
} DVR_DEVICEINFO_V15, *PDVR_DEVICEINFO_V15;

//上传设备信息数组V1.5版
typedef struct
{
    unsigned int        uiDeviceCount;              //设备数量
    DVR_DEVICEINFO_V15  DeviceInfos[];              //设备数组
} DVR_DEVICEINFOS_V15, *PDVR_DEVICEINFOS_V15;

//上传设备信息V2.0版（适用于监控场景、电子地图以外类型的设备）
typedef struct
{
    DVR_DEV_ID          llDevId;                    //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号)
    char                szName[128];                //设备名称
    int                 iDevType;                   //设备类型
    int                 iDevSubType;                //设备子类型
    DVR_DEV_ID          llParentDevId;              //父设备Id(全局编号）
    int                 iStatus;                    //在线状态
    unsigned int        uiAlarmLevel;               //告警级别
    DVR_DEV_ID          llGlobalCode;               //全局编号
    unsigned int        uiReserved;                 //保留
    float               fLongitude;                 //经度
    float               fLatitude;                  //纬度
    char                szManufacturer[64];         //制造商

    union
    {
        struct CameraExtData   cedCameraExtData;
        struct LocationExtData ledLocationExtData;
        struct PersonExtData   pedPersonExtData;
    };
} DVR_DEVICEINFO_V20, *PDVR_DEVICEINFO_V20;

//上传设备信息数组V2.0版
typedef struct
{
    unsigned int        uiDeviceCount;              //设备数量
    DVR_DEVICEINFO_V20  DeviceInfos[];              //设备数组
} DVR_DEVICEINFOS_V20, *PDVR_DEVICEINFOS_V20;

//设备名称（适用于摄像机、报警器、报警输出等逻辑设备）
typedef struct
{
    DVR_DEV_ID          llDevId;                    //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    char                szName[128];                //设备名称
    int                 iDevType;                   //设备类型
    int                 iDevSubType;                //设备子类型，选择使用
} DVR_DEVICE_NAME, *PDVR_DEVICE_NAME;

//注册接入服务器信息
typedef struct
{
    int             iServerKind;                    //0:注册服务器；1:接入服务器
    char            szServerIP[DVR_IP_LEN];         //注册服务器地址
    unsigned short  usServerPort;                   //注册服务器端口
    unsigned short  usReserved;                     //保留
    char            szServerUserName[DVR_USR_LEN];  //注册用户名
    char            szServerPassword[DVR_PASS_LEN]; //注册密码
} DVR_REGISTERSERVERINFO, *PDVR_REGISTERSERVERINFO;

//设备在线率信息（以天为单位）
typedef struct
{
    DVR_DEV_ID llDevId;                            //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    char szDevName[128];                           //设备名称
    char szDevIP[DVR_IP_LEN];                      //设备地址
    int iDevType;                                  //设备类型
    DVR_TIME dtReportDate;                         //统计日期
    int iOnlinePercent;                            //设备在线率
    int iOnlineTime;                               //设备在线时间和(单位：秒)
} DVR_DEVICE_ONLINE_INFO, *PDVR_DEVICE_ONLINE_INFO;

//设备在线率信息数组
typedef struct
{
    unsigned int uiDeviceCount;                     //设备数量
    DVR_DEVICE_ONLINE_INFO DeviceOnlineInfos[];     //设备在线率数组
} DVR_DEVICE_ONLINE_INFOS, *PDVR_DEVICE_ONLINE_INFOS;

//云台守望信息
typedef struct
{
    DVR_DEV_ID llChannel;                           //视频通道号(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int iPresetIndex;                               //预置点序号，从1开始
    int iResetCycle;                                //复位周期，单位：秒(1-720)
    int iResetEnabled;                              //使能标志，0-不启动，1-启动
} DVR_PTZRESETINFO, *PDVR_PTZRESETINFO;

//配置输入参数（用于DVR_GetDVRConfigEx/DVR_SetDVRConfigEx）
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备Id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int iDevType;                                   //设备类型
    int iDevSubType;                                //设备子类型，选择使用
    int iReserved;                                  //保留
} DVR_CONFIG_IN_PARAM, *PDVR_CONFIG_IN_PARAM;


//////////////////////////////////////////////////////////////////////////////////////////////
//空调控制相关定义
//////////////////////////////////////////////////////////////////////////////////////////////
//空调工作模式配置
typedef struct
{
    int iWorkMode;                                  //工作模式
    int iTemperature;                               //温度
} DVR_AIR_CONDITION_WORK_MODE_CFG;

//空调参数配置
typedef struct
{
    int iPlanMode;                                 //计划模式
    DVR_AIR_CONDITION_WORK_MODE_CFG WMCfg[12];     //工作模式相关参数配置,恒定工作模式下仅数组首个元素有效。
} DVR_AIR_CONDITION_CFG;

//空调指令配置
struct DVR_AC_CMD_CFG
{
    unsigned short m_uiID;                          //指令编号
    unsigned short m_uiDataLen;                     //指令长度
    char     m_szData[60];                       	//指令数据
};

//空调指令配置数组
struct DVR_AC_CMD_CFGS
{
    struct DVR_AC_CMD_CFG cmds[64];                 //指令数组
};
//////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//门禁相关定义
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DVR_GET_DC_CAPABILITY_CFG           300    	//获取门禁能力配置（对应数据结构为门禁指令配置数组DVR_DC_CAPABILITY_CFG）
#define DVR_GET_DC_CFG                      301    	//获取门禁主机配置（对应数据结构为门禁主机配置DVR_DC_CONFIG）
#define DVR_GET_DC_DOOR_CFG                 302    	//获取门配置（对应数据结构为门配置DVR_DC_DOOR_CONFIG）
#define DVR_GET_DC_CARD_CFG                 303    	//获取门禁卡配置（对应数据结构为门禁卡配置DVR_DC_CARD_CONFIG）

#define DVR_SET_DC_CFG                      350    	//设置门禁主机配置（对应数据结构为门禁主机配置DVR_DC_CONFIG）
#define DVR_SET_DC_DOOR_CFG                 351    	//设置门配置（对应数据结构为门配置DVR_DC_DOOR_CONFIG）
#define DVR_SET_DC_CARD_CFG                 352    	//设置门禁卡配置（对应数据结构为门禁卡配置DVR_DC_CARD_CONFIG）

//门禁能力配置
struct DVR_DC_CAPABILITY_CFG
{
    unsigned int uiDoorCount;                       //门数量
    unsigned int uiReserved[10];
};

//门禁主机配置
struct DVR_DC_CONFIG
{
    unsigned int uiReserved[10];
};

//门配置
struct DVR_DC_DOOR_CONFIG
{
    unsigned char ucOpenMethod;			            //开门方式,0-未知，1-仅密码,2-仅刷卡,3-密码或刷卡,4-先密码后刷卡,5-先刷卡后密码,6-仅指纹，7-密码或刷卡或指纹,
                                                    //8-密码+刷卡+指纹，9-密码+指纹，10-刷卡+指纹，11-多人刷卡
    unsigned short usUnlockHoldTime;			    //门锁保持时间(自动关门时间)，单位：毫秒
    unsigned short usCloseTimeout;					//关门超时, 超过阈值未关会触发报警，单位：秒，0表示不检测

    unsigned int uiReserved[10];
};

//门禁卡配置
//struct DVR_DOOR_CARD_CFG
//{
//    char szCardNo[32];                              //卡号
//    unsigned char ucCardValid;                      //卡是否有效，0-无效，1-有效
//    unsigned char ucCardKind;                       //卡种类,0-普通卡,1-VIP卡,2-来宾卡,3-巡更卡,4-黑名单卡,5-胁迫卡,6-残疾人卡,7-解除卡
//    unsigned char ucLeaderCard;                     //是否为首卡，1-是，0-否
//    unsigned char ucReserved1;
//    unsigned int uiDoorRight;                       //门权限，按位表示，1为有权限，0为无权限，从低位到高位表示对门1-门N是否有权限
//    NET_DVR_VALID_PERIOD_CFG struValid;             //有效期参数
//    unsigned int uiGroups;                          //所属群组，按位表示，1-属于，0-不属于，从低位到高位表示是否从属群组1-N
//    char szCardPassword[DVR_PASS_LEN];              //卡密码
//    unsigned char ucCardRightPlan[32][4];           //卡权限计划，取值为计划模板编号，同个门不同计划模板采用权限或的方式处理
//    unsigned int uiMaxSwipeTimes;                   //最大刷卡次数，0为无次数限制
//    unsigned int uiSwipeTimes;                      //已刷卡次数
//    unsigned int uiReserved2[10];
//};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
//智能视频分析(IVS)相关结构定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//点
typedef struct
{
    int x;  									    //横坐标
    int y;  									    //纵坐标
} DVR_IVS_POINT;

//线
typedef struct
{
    DVR_IVS_POINT start;    						//起点
    DVR_IVS_POINT end;      					    //终点
} DVR_IVS_LINE;

//区域多边形最大点数
#define DVR_IVS_REGION_POINT_NUM    10

//多边形分析区域
typedef struct
{
    int           pointNum;                         //点数,大于等于3
    DVR_IVS_POINT point[DVR_IVS_REGION_POINT_NUM];  //顶点
} DVR_IVS_REGION;

//智能视频分析规则类型
typedef enum
{
    DVR_IVS_RULE_LINE   = 0,  						//警戒线               
    DVR_IVS_RULE_REGION = 0 						//警戒区域
} DVR_IVS_RULE_TYPE;

//跨线方向类型
typedef enum
{
    DVR_IVS_LINE_BOTH_DIRECTION,    				//双向
    DVR_IVS_LINE_LEFT_GO_RIGHT,     				//由左至右
    DVR_IVS_LINE_RIGHT_GO_LEFT      				//由右至左
} DVR_IVS_LINE_DIRECTION;

//警戒线规则
typedef struct
{
    DVR_IVS_LINE_DIRECTION direction;  				//警戒线跨越方向
    DVR_IVS_LINE           line;       				//警戒线坐标
} DVR_IVS_LINE_RULE;

//区域规则
typedef struct
{
    DVR_IVS_REGION region;     						//多边形
} DVR_IVS_REGION_RULE;

//智能视频分析规则
typedef struct
{
	int                 	  id;                 	//规则ID
    DVR_IVS_RULE_TYPE         ruleType;           	//规则类型
    unsigned int      		  eventTypes;          	//事件类型集合
    unsigned int              targetTypes;         	//目标类型集合
	int                 	  duration;           	//持续时间(秒)	
    union
    {
        DVR_IVS_LINE_RULE     line;    		        //线
        DVR_IVS_REGION_RULE   region;  			    //区域
    } ruleData;               					    
} DVR_IVS_RULE;

//视频处理类型
typedef enum
{
    DVR_IVS_FILTER_NONE,                            //无过滤 
    DVR_IVS_FILTER_QUIVER      					 	//防抖动处理
} DVR_IVS_FILTER_TYPE;

//规则数
#define DVR_IVS_RULE_NUM    50

//智能视频分析配置
typedef struct
{
    DVR_IVS_FILTER_TYPE filter;                    	//视频处理类型
    int                 ruleNum;                   	//设置规则数目                     
    DVR_IVS_RULE        rule[DVR_IVS_RULE_NUM];    	//规则保存数组
} DVR_IVS_CONFIG;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//人脸识别相关
//////////////////////////////////////////////////////////////////////////////////////////////////////
//人员信息
typedef struct
{
    DVR_DEV_ID 			llID;              		 	//人员ID
    int                 iType;                     	//人员类型，见“人脸数据类型”定义
    int 				iRegisterMode;				//注册模式（0: 自动采集，1-刷卡，2-读身份证，3-照片导入）
	char 				szName[64];					//姓名
    short				iSex;						//性别,0-男，1-女,255-其他
	short				iNation;					//民族
	int					iBirthDay;					//生日
	char				szAddress[96];				//住址
	char				szDepart[32];				//发证部门
	char 				szCardNum[20];				//卡号
	int					iFromValidDate;				//起始有效期
	int					iToValidDate;				//截至有效期
	int           		iRegisterTime;				//注册时间
    int           		iExpireType;				//注册有效期类型（有效期类型（0-小时，1-天，2-月，3-永久有效）
	int                 iExpireValue;				//注册有效期数值
	char 				szHostIP[20];				//注册主机IP
	int                 iHostChannelNum;			//注册主机通道号
	int                 iVerifyStatus;				//认证状态（标准版/卡口版：0-未进行人证核验，1-人证核验通过，2-人证核验未通过；
	                                                //监管场所版：0-未审核，1-审核通过，2-审核不通过，3-等待科室审核，4-等待领导审核） 
	int                 iRegisterDataCount;			//注册记录数据数量
	int                 iHasExpandInfo;				//是否带有扩展信息(0-无，1-有)
	char 				szGUID[32];					//人员全局ID,保证系统范围内记录唯一
} DVR_IVS_PERSON_INFO;

//人员注册数据信息
typedef struct
{
    DVR_DEV_ID 			llPersonID;        		 	//人员ID
    int                 iType;                      //数据类型，见“人脸数据类型”定义
	int                 iVerifyScore;				//认证分数，仅启用人证核验且iType值为0x02即注册采集人脸照片时有效
    int 				iGroupID;					//组号(组号相同说明数据之间存在关联性)
	int					iDataLen;					//数据长度
} DVR_IVS_PERSON_REGISTER_DATA_INFO;

//人员注册数据信息数组
typedef struct
{
    int                 iCount;                     //注册数据数量
    DVR_IVS_PERSON_REGISTER_DATA_INFO registerDataInfos[];	//注册数据数组指针
} DVR_IVS_PERSON_REGISTER_DATA_INFOS;

//在逃人员扩展信息
typedef struct
{
	char				szCriminalNum[24];			//在逃人员编号
	char				szLawWantedNum[16];			//通缉编号
	int 				iLawWantedDate;				//通缉日期(yyyymmdd)
	int 				iAwardMoney;				//赏金
	char				szOrgName[64];				//发布单位名称
	char				szLinkMan[32];				//联系人
	char				szLinkPhone[32];			//联系电话
	char				szLinkAddress[128];			//联系地址
	char				szRemark[256];				//说明
} DVR_IVS_ESCAPEE_EXPAND_INFO;

//重点人员扩展信息
typedef struct
{
	char				szOrgName[64];				//发布单位名称
    char				szLinkMan[32];				//联系人
	char				szLinkPhone[32];			//联系电话
	char				szLinkAddress[128];			//联系地址
	char				szRemark[256];				//说明
} DVR_IVS_IMPORTANT_EXPAND_INFO;

//涉毒人员扩展信息
typedef struct
{
	char				szOrgName[64];				//发布单位名称
	char				szLinkMan[32];				//联系人
	char				szLinkPhone[32];			//联系电话
	char				szLinkAddress[128];			//联系地址
	char				szRemark[256];				//说明
} DVR_IVS_NACOTICS_RELATED_EXPAND_INFO;

//人员扩展信息
//在人员信息结构人员类型为“在逃人员”、“重点人员”、“涉毒人员”时有效
typedef struct
{
    DVR_DEV_ID 			llPersonID;        		 	//人员ID
    int                 iPersonType;                //人员类型，见“人脸数据类型”定义
    union
	{
	DVR_IVS_ESCAPEE_EXPAND_INFO escapeeInfo;					//在逃人员信息
	DVR_IVS_IMPORTANT_EXPAND_INFO importantInfo;				//重点人员信息
    DVR_IVS_NACOTICS_RELATED_EXPAND_INFO nacoticsRelatedInfo;	//涉毒人员信息
	};
} DVR_IVS_PERSON_EXPAND_INFO;

//人员比对记录
typedef struct
{
    DVR_DEV_ID 			llID;              		 	//比对记录ID
	DVR_DEV_ID 			llTaskID;					//比对任务ID,中心比对用，前端比对始终为0
    int                 iType;                     	//记录类型
	int 				iTrackID;					//轨迹ID
	DVR_DEV_ID 			llPersonID;              	//采集人员ID，摄像机采集模式下始终为0
	int 				iPictureID;					//原始图片ID
	int 				iPhotoID;					//显示照片ID
    int 				iCardPhotoID;			    //身份证照片ID
	int           		iVerifyTime;				//认证时间
	int           		iVerifyMode;				//认证模式
	int                 iVerifyPictureType;			//认证源图像类型
	int                 iVerifyStatus;			    //认证状态
	int                 iVerifyScore;				//认证分数
	char 				szHostIP[20];				//认证主机IP
	int                 iHostChannelNum;			//认证主机通道号
	int                 iVerifyResultCount;		    //认证结果数量，最大为8人
	DVR_DEV_ID 			llVerifyPersonIDs[8];     	//认证人员ID
	int                 iVerifyScores[8];			//认证分数
	int                 iVerifyRecordDataCount;		//认证记录数据数量
} DVR_IVS_PERSON_VERIFY_RECORD;

//人员比对记录数据信息
typedef struct
{
    DVR_DEV_ID 			llRecordID;        		 	//比对记录ID
    int                 iType;                     	//数据类型，见“人脸数据类型”定义
    int 				iGroupID;					//组号(组号相同说明数据之间存在关联性)
	int					iDataLen;					//数据长度
} DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO;

//人员比对记录数据信息数组
typedef struct
{
    int                 iCount;                     		//比对记录数据数量
    DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFO verifyRecordDataInfos[];	//比对记录数据数组指针
} DVR_IVS_PERSON_VERIFY_RECORD_DATA_INFOS;

//比对区域信息
typedef struct
{
    int                 uiLibraryType;     			//人员库类型
    DVR_DEV_ID 			llRegionID;					//比对区域ID
	DVR_DEV_ID 			llRegionCode;				//比对区域编码
} DVR_IVS_REGION_INFO;

//比对区域信息数组
typedef struct
{
    int                 iCount;                		//比对区域信息数量
    DVR_IVS_REGION_INFO regionInfos[];				//比对区域信息数组指针
} DVR_IVS_REGION_INFOS;

//比对人员ID数组
typedef struct
{
    DVR_DEV_ID          llGroupID;					//比对人员组ID 
    int                 iCount;                    	//比对人员ID数量
    DVR_DEV_ID 			personIDs[];	   			//比对人员ID数组指针
} DVR_IVS_PERSON_IDS;

//终端采集配置
typedef struct
{
    int                 iChannelCount;              //通道号数量，最大为64个,数值为0表示所有通道
    DVR_DEV_ID 			channelNums[64];	  	    //通道号数组指针，从1开始
} DVR_IVS_TERMINAL_CAPTURE_CFG;
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位相关结构定义
//////////////////////////////////////////////////////////////////////////////////////////////////////
//定位数据上报
typedef struct
{
    DVR_DEV_ID llDevId;                             //设备id(实际设备：物理编号，从1开始；代理或平台：全局编号）
    int  iDevType;                                  //设备类型
    int  iDevSubType;                               //设备子类型
	DVR_DEV_ID llMapId;    			                //地图Id(全局编号)
    float fRealWorldPosX;                           //真实世界x坐标(单位:米)
    float fRealWorldPosY;                           //真实世界y坐标(单位:米)
} DVR_LOCATION_REPORT;
//////////////////////////////////////////////////////////////////////////////////////////////////////


//回调函数类型
//实时流回调函数
typedef void(*DVR_REALDATA_CALLBACK) (long lStreamHandle, unsigned long ulDataType, char *pBuffer, unsigned long ulBufSize, unsigned long ulUserData);

//语音对讲回调函数
typedef void(*DVR_VOICEDATA_CALLBACK)(long lVoiceComHandle, unsigned long ulDataType, char *pBuffer, unsigned long ulBufSize, unsigned long ulUserData);

//Draw回调函数
typedef void (*DVR_DRAW_CALLBACK)(long lStreamHandle, DVR_HDC hDc, unsigned long ulUserData);

//解码回调函数
typedef void (*DVR_DECODE_CALLBACK)(long lStreamHandle, DVR_FRAMEINFO* pFrame, unsigned long ulUserData);

//消息回调函数
typedef void (*DVR_MESSAGE_CALLBACK)(long lCommand, long lUserHandle, char *pBuf, unsigned long ulBufLen, unsigned long ulUserData);

//透明通道回调函数（网络型）
typedef void (*DVR_NETDATA_CALLBACK)(long lNetHandle, DVR_DEV_ID llDevId, char *pBuffer, unsigned long ulBufSize, unsigned long ulUserData);

//透明通道回调函数（串口型）
typedef void (*DVR_SERIALDATA_CALLBACK)(long lSerialHandle, char *pBuffer, unsigned long ulBufSize, unsigned long ulUserData);

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif // DVRWRAPPERDEF_H
