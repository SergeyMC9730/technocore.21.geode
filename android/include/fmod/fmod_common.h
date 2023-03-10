#ifndef _FMOD_COMMON_H
#define _FMOD_COMMON_H

/*
    Library import helpers
*/
#if defined(_WIN32) || defined(__CYGWIN__)
    #define F_CALL __stdcall
#else
    #define F_CALL
#endif

#if defined(_WIN32) || defined(__CYGWIN__) || defined(__ORBIS__) || defined(F_USE_DECLSPEC)
    #define F_EXPORT __declspec(dllexport)
#elif defined(__APPLE__) || defined(__ANDROID__) || defined(__linux__) || defined(F_USE_ATTRIBUTE)
    #define F_EXPORT __attribute__((visibility("default")))
#else
    #define F_EXPORT
#endif

#ifdef DLL_EXPORTS
    #define F_API F_EXPORT F_CALL
#else
    #define F_API F_CALL
#endif

#define F_CALLBACK F_CALL

/*
    FMOD core types
*/
typedef int                        FMOD_BOOL;
typedef struct FMOD_SYSTEM         FMOD_SYSTEM;
typedef struct FMOD_SOUND          FMOD_SOUND;
typedef struct FMOD_CHANNELCONTROL FMOD_CHANNELCONTROL;
typedef struct FMOD_CHANNEL        FMOD_CHANNEL;
typedef struct FMOD_CHANNELGROUP   FMOD_CHANNELGROUP;
typedef struct FMOD_SOUNDGROUP     FMOD_SOUNDGROUP;
typedef struct FMOD_REVERB3D       FMOD_REVERB3D;
typedef struct FMOD_DSP            FMOD_DSP;
typedef struct FMOD_DSPCONNECTION  FMOD_DSPCONNECTION;
typedef struct FMOD_POLYGON        FMOD_POLYGON;
typedef struct FMOD_GEOMETRY       FMOD_GEOMETRY;
typedef struct FMOD_SYNCPOINT      FMOD_SYNCPOINT;
typedef struct FMOD_ASYNCREADINFO  FMOD_ASYNCREADINFO;
typedef unsigned long long         FMOD_PORT_INDEX;

/*
    FMOD constants
*/
#define FMOD_VERSION    0x00020206                     /* 0xaaaabbcc -> aaaa = product version, bb = major version, cc = minor version.*/

typedef unsigned int FMOD_DEBUG_FLAGS;
#define FMOD_DEBUG_LEVEL_NONE                       0x00000000
#define FMOD_DEBUG_LEVEL_ERROR                      0x00000001
#define FMOD_DEBUG_LEVEL_WARNING                    0x00000002
#define FMOD_DEBUG_LEVEL_LOG                        0x00000004
#define FMOD_DEBUG_TYPE_MEMORY                      0x00000100
#define FMOD_DEBUG_TYPE_FILE                        0x00000200
#define FMOD_DEBUG_TYPE_CODEC                       0x00000400
#define FMOD_DEBUG_TYPE_TRACE                       0x00000800
#define FMOD_DEBUG_DISPLAY_TIMESTAMPS               0x00010000
#define FMOD_DEBUG_DISPLAY_LINENUMBERS              0x00020000
#define FMOD_DEBUG_DISPLAY_THREAD                   0x00040000

typedef unsigned int FMOD_MEMORY_TYPE;
#define FMOD_MEMORY_NORMAL                          0x00000000
#define FMOD_MEMORY_STREAM_FILE                     0x00000001
#define FMOD_MEMORY_STREAM_DECODE                   0x00000002
#define FMOD_MEMORY_SAMPLEDATA                      0x00000004
#define FMOD_MEMORY_DSP_BUFFER                      0x00000008
#define FMOD_MEMORY_PLUGIN                          0x00000010
#define FMOD_MEMORY_PERSISTENT                      0x00200000
#define FMOD_MEMORY_ALL                             0xFFFFFFFF

typedef unsigned int FMOD_INITFLAGS;
#define FMOD_INIT_NORMAL                            0x00000000
#define FMOD_INIT_STREAM_FROM_UPDATE                0x00000001
#define FMOD_INIT_MIX_FROM_UPDATE                   0x00000002
#define FMOD_INIT_3D_RIGHTHANDED                    0x00000004
#define FMOD_INIT_CHANNEL_LOWPASS                   0x00000100
#define FMOD_INIT_CHANNEL_DISTANCEFILTER            0x00000200
#define FMOD_INIT_PROFILE_ENABLE                    0x00010000
#define FMOD_INIT_VOL0_BECOMES_VIRTUAL              0x00020000
#define FMOD_INIT_GEOMETRY_USECLOSEST               0x00040000
#define FMOD_INIT_PREFER_DOLBY_DOWNMIX              0x00080000
#define FMOD_INIT_THREAD_UNSAFE                     0x00100000
#define FMOD_INIT_PROFILE_METER_ALL                 0x00200000
#define FMOD_INIT_MEMORY_TRACKING                   0x00400000

typedef unsigned int FMOD_DRIVER_STATE;
#define FMOD_DRIVER_STATE_CONNECTED                 0x00000001
#define FMOD_DRIVER_STATE_DEFAULT                   0x00000002

typedef unsigned int FMOD_TIMEUNIT;
#define FMOD_TIMEUNIT_MS                            0x00000001
#define FMOD_TIMEUNIT_PCM                           0x00000002
#define FMOD_TIMEUNIT_PCMBYTES                      0x00000004
#define FMOD_TIMEUNIT_RAWBYTES                      0x00000008
#define FMOD_TIMEUNIT_PCMFRACTION                   0x00000010
#define FMOD_TIMEUNIT_MODORDER                      0x00000100
#define FMOD_TIMEUNIT_MODROW                        0x00000200
#define FMOD_TIMEUNIT_MODPATTERN                    0x00000400

typedef unsigned int FMOD_SYSTEM_CALLBACK_TYPE;
#define FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED      0x00000001
#define FMOD_SYSTEM_CALLBACK_DEVICELOST             0x00000002
#define FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED 0x00000004
#define FMOD_SYSTEM_CALLBACK_THREADCREATED          0x00000008
#define FMOD_SYSTEM_CALLBACK_BADDSPCONNECTION       0x00000010
#define FMOD_SYSTEM_CALLBACK_PREMIX                 0x00000020
#define FMOD_SYSTEM_CALLBACK_POSTMIX                0x00000040
#define FMOD_SYSTEM_CALLBACK_ERROR                  0x00000080
#define FMOD_SYSTEM_CALLBACK_MIDMIX                 0x00000100
#define FMOD_SYSTEM_CALLBACK_THREADDESTROYED        0x00000200
#define FMOD_SYSTEM_CALLBACK_PREUPDATE              0x00000400
#define FMOD_SYSTEM_CALLBACK_POSTUPDATE             0x00000800
#define FMOD_SYSTEM_CALLBACK_RECORDLISTCHANGED      0x00001000
#define FMOD_SYSTEM_CALLBACK_BUFFEREDNOMIX          0x00002000
#define FMOD_SYSTEM_CALLBACK_DEVICEREINITIALIZE     0x00004000
#define FMOD_SYSTEM_CALLBACK_OUTPUTUNDERRUN         0x00008000
#define FMOD_SYSTEM_CALLBACK_ALL                    0xFFFFFFFF

typedef unsigned int FMOD_MODE;
#define FMOD_DEFAULT                                0x00000000
#define FMOD_LOOP_OFF                               0x00000001
#define FMOD_LOOP_NORMAL                            0x00000002
#define FMOD_LOOP_BIDI                              0x00000004
#define FMOD_2D                                     0x00000008
#define FMOD_3D                                     0x00000010
#define FMOD_CREATESTREAM                           0x00000080
#define FMOD_CREATESAMPLE                           0x00000100
#define FMOD_CREATECOMPRESSEDSAMPLE                 0x00000200
#define FMOD_OPENUSER                               0x00000400
#define FMOD_OPENMEMORY                             0x00000800
#define FMOD_OPENMEMORY_POINT                       0x10000000
#define FMOD_OPENRAW                                0x00001000
#define FMOD_OPENONLY                               0x00002000
#define FMOD_ACCURATETIME                           0x00004000
#define FMOD_MPEGSEARCH                             0x00008000
#define FMOD_NONBLOCKING                            0x00010000
#define FMOD_UNIQUE                                 0x00020000
#define FMOD_3D_HEADRELATIVE                        0x00040000
#define FMOD_3D_WORLDRELATIVE                       0x00080000
#define FMOD_3D_INVERSEROLLOFF                      0x00100000
#define FMOD_3D_LINEARROLLOFF                       0x00200000
#define FMOD_3D_LINEARSQUAREROLLOFF                 0x00400000
#define FMOD_3D_INVERSETAPEREDROLLOFF               0x00800000
#define FMOD_3D_CUSTOMROLLOFF                       0x04000000
#define FMOD_3D_IGNOREGEOMETRY                      0x40000000
#define FMOD_IGNORETAGS                             0x02000000
#define FMOD_LOWMEM                                 0x08000000
#define FMOD_VIRTUAL_PLAYFROMSTART                  0x80000000

typedef unsigned int FMOD_CHANNELMASK;
#define FMOD_CHANNELMASK_FRONT_LEFT                 0x00000001
#define FMOD_CHANNELMASK_FRONT_RIGHT                0x00000002
#define FMOD_CHANNELMASK_FRONT_CENTER               0x00000004
#define FMOD_CHANNELMASK_LOW_FREQUENCY              0x00000008
#define FMOD_CHANNELMASK_SURROUND_LEFT              0x00000010
#define FMOD_CHANNELMASK_SURROUND_RIGHT             0x00000020
#define FMOD_CHANNELMASK_BACK_LEFT                  0x00000040
#define FMOD_CHANNELMASK_BACK_RIGHT                 0x00000080
#define FMOD_CHANNELMASK_BACK_CENTER                0x00000100
#define FMOD_CHANNELMASK_MONO                       (FMOD_CHANNELMASK_FRONT_LEFT)
#define FMOD_CHANNELMASK_STEREO                     (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT)
#define FMOD_CHANNELMASK_LRC                        (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER)
#define FMOD_CHANNELMASK_QUAD                       (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT)
#define FMOD_CHANNELMASK_SURROUND                   (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER  | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT)
#define FMOD_CHANNELMASK_5POINT1                    (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER  | FMOD_CHANNELMASK_LOW_FREQUENCY | FMOD_CHANNELMASK_SURROUND_LEFT  | FMOD_CHANNELMASK_SURROUND_RIGHT)
#define FMOD_CHANNELMASK_5POINT1_REARS              (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER  | FMOD_CHANNELMASK_LOW_FREQUENCY | FMOD_CHANNELMASK_BACK_LEFT      | FMOD_CHANNELMASK_BACK_RIGHT)
#define FMOD_CHANNELMASK_7POINT0                    (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER  | FMOD_CHANNELMASK_SURROUND_LEFT | FMOD_CHANNELMASK_SURROUND_RIGHT | FMOD_CHANNELMASK_BACK_LEFT      | FMOD_CHANNELMASK_BACK_RIGHT)
#define FMOD_CHANNELMASK_7POINT1                    (FMOD_CHANNELMASK_FRONT_LEFT | FMOD_CHANNELMASK_FRONT_RIGHT | FMOD_CHANNELMASK_FRONT_CENTER  | FMOD_CHANNELMASK_LOW_FREQUENCY | FMOD_CHANNELMASK_SURROUND_LEFT  | FMOD_CHANNELMASK_SURROUND_RIGHT | FMOD_CHANNELMASK_BACK_LEFT | FMOD_CHANNELMASK_BACK_RIGHT)

typedef int FMOD_THREAD_PRIORITY;
/* Platform specific priority range */
#define FMOD_THREAD_PRIORITY_PLATFORM_MIN           (-32 * 1024)
#define FMOD_THREAD_PRIORITY_PLATFORM_MAX           ( 32 * 1024)
/* Platform agnostic priorities, maps internally to platform specific value */
#define FMOD_THREAD_PRIORITY_DEFAULT                (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 1)
#define FMOD_THREAD_PRIORITY_LOW                    (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 2)
#define FMOD_THREAD_PRIORITY_MEDIUM                 (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 3)
#define FMOD_THREAD_PRIORITY_HIGH                   (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 4)
#define FMOD_THREAD_PRIORITY_VERY_HIGH              (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 5)
#define FMOD_THREAD_PRIORITY_EXTREME                (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 6)
#define FMOD_THREAD_PRIORITY_CRITICAL               (FMOD_THREAD_PRIORITY_PLATFORM_MIN - 7)
/* Thread defaults */
#define FMOD_THREAD_PRIORITY_MIXER                  FMOD_THREAD_PRIORITY_EXTREME
#define FMOD_THREAD_PRIORITY_FEEDER                 FMOD_THREAD_PRIORITY_CRITICAL
#define FMOD_THREAD_PRIORITY_STREAM                 FMOD_THREAD_PRIORITY_VERY_HIGH
#define FMOD_THREAD_PRIORITY_FILE                   FMOD_THREAD_PRIORITY_HIGH
#define FMOD_THREAD_PRIORITY_NONBLOCKING            FMOD_THREAD_PRIORITY_HIGH
#define FMOD_THREAD_PRIORITY_RECORD                 FMOD_THREAD_PRIORITY_HIGH
#define FMOD_THREAD_PRIORITY_GEOMETRY               FMOD_THREAD_PRIORITY_LOW
#define FMOD_THREAD_PRIORITY_PROFILER               FMOD_THREAD_PRIORITY_MEDIUM
#define FMOD_THREAD_PRIORITY_STUDIO_UPDATE          FMOD_THREAD_PRIORITY_MEDIUM
#define FMOD_THREAD_PRIORITY_STUDIO_LOAD_BANK       FMOD_THREAD_PRIORITY_MEDIUM
#define FMOD_THREAD_PRIORITY_STUDIO_LOAD_SAMPLE     FMOD_THREAD_PRIORITY_MEDIUM
#define FMOD_THREAD_PRIORITY_CONVOLUTION1           FMOD_THREAD_PRIORITY_VERY_HIGH
#define FMOD_THREAD_PRIORITY_CONVOLUTION2           FMOD_THREAD_PRIORITY_VERY_HIGH

typedef unsigned int FMOD_THREAD_STACK_SIZE;
#define FMOD_THREAD_STACK_SIZE_DEFAULT              0
#define FMOD_THREAD_STACK_SIZE_MIXER                (80  * 1024)
#define FMOD_THREAD_STACK_SIZE_FEEDER               (16  * 1024)
#define FMOD_THREAD_STACK_SIZE_STREAM               (96  * 1024)
#define FMOD_THREAD_STACK_SIZE_FILE                 (64  * 1024)
#define FMOD_THREAD_STACK_SIZE_NONBLOCKING          (112 * 1024)
#define FMOD_THREAD_STACK_SIZE_RECORD               (16  * 1024)
#define FMOD_THREAD_STACK_SIZE_GEOMETRY             (48  * 1024)
#define FMOD_THREAD_STACK_SIZE_PROFILER             (128 * 1024)
#define FMOD_THREAD_STACK_SIZE_STUDIO_UPDATE        (96  * 1024)
#define FMOD_THREAD_STACK_SIZE_STUDIO_LOAD_BANK     (96  * 1024)
#define FMOD_THREAD_STACK_SIZE_STUDIO_LOAD_SAMPLE   (96  * 1024)
#define FMOD_THREAD_STACK_SIZE_CONVOLUTION1         (16  * 1024)
#define FMOD_THREAD_STACK_SIZE_CONVOLUTION2         (16  * 1024)

typedef long long FMOD_THREAD_AFFINITY;
/* Platform agnostic thread groupings */
#define FMOD_THREAD_AFFINITY_GROUP_DEFAULT          0x4000000000000000
#define FMOD_THREAD_AFFINITY_GROUP_A                0x4000000000000001
#define FMOD_THREAD_AFFINITY_GROUP_B                0x4000000000000002
#define FMOD_THREAD_AFFINITY_GROUP_C                0x4000000000000003
/* Thread defaults */
#define FMOD_THREAD_AFFINITY_MIXER                  FMOD_THREAD_AFFINITY_GROUP_A
#define FMOD_THREAD_AFFINITY_FEEDER                 FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_STREAM                 FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_FILE                   FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_NONBLOCKING            FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_RECORD                 FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_GEOMETRY               FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_PROFILER               FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_STUDIO_UPDATE          FMOD_THREAD_AFFINITY_GROUP_B
#define FMOD_THREAD_AFFINITY_STUDIO_LOAD_BANK       FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_STUDIO_LOAD_SAMPLE     FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_CONVOLUTION1           FMOD_THREAD_AFFINITY_GROUP_C
#define FMOD_THREAD_AFFINITY_CONVOLUTION2           FMOD_THREAD_AFFINITY_GROUP_C

/* Core mask, valid up to 1 << 62 */
#define FMOD_THREAD_AFFINITY_CORE_ALL               0
#define FMOD_THREAD_AFFINITY_CORE_0                 (1 << 0)
#define FMOD_THREAD_AFFINITY_CORE_1                 (1 << 1)
#define FMOD_THREAD_AFFINITY_CORE_2                 (1 << 2)
#define FMOD_THREAD_AFFINITY_CORE_3                 (1 << 3)
#define FMOD_THREAD_AFFINITY_CORE_4                 (1 << 4)
#define FMOD_THREAD_AFFINITY_CORE_5                 (1 << 5)
#define FMOD_THREAD_AFFINITY_CORE_6                 (1 << 6)
#define FMOD_THREAD_AFFINITY_CORE_7                 (1 << 7)
#define FMOD_THREAD_AFFINITY_CORE_8                 (1 << 8)
#define FMOD_THREAD_AFFINITY_CORE_9                 (1 << 9)
#define FMOD_THREAD_AFFINITY_CORE_10                (1 << 10)
#define FMOD_THREAD_AFFINITY_CORE_11                (1 << 11)
#define FMOD_THREAD_AFFINITY_CORE_12                (1 << 12)
#define FMOD_THREAD_AFFINITY_CORE_13                (1 << 13)
#define FMOD_THREAD_AFFINITY_CORE_14                (1 << 14)
#define FMOD_THREAD_AFFINITY_CORE_15                (1 << 15)

/* Preset for FMOD_REVERB_PROPERTIES */
#define FMOD_PRESET_OFF                             {  1000,    7,  11, 5000, 100, 100, 100, 250, 0,    20,  96, -80.0f }
#define FMOD_PRESET_GENERIC                         {  1500,    7,  11, 5000,  83, 100, 100, 250, 0, 14500,  96,  -8.0f }
#define FMOD_PRESET_PADDEDCELL                      {   170,    1,   2, 5000,  10, 100, 100, 250, 0,   160,  84,  -7.8f }
#define FMOD_PRESET_ROOM                            {   400,    2,   3, 5000,  83, 100, 100, 250, 0,  6050,  88,  -9.4f }
#define FMOD_PRESET_BATHROOM                        {  1500,    7,  11, 5000,  54, 100,  60, 250, 0,  2900,  83,   0.5f }
#define FMOD_PRESET_LIVINGROOM                      {   500,    3,   4, 5000,  10, 100, 100, 250, 0,   160,  58, -19.0f }
#define FMOD_PRESET_STONEROOM                       {  2300,   12,  17, 5000,  64, 100, 100, 250, 0,  7800,  71,  -8.5f }
#define FMOD_PRESET_AUDITORIUM                      {  4300,   20,  30, 5000,  59, 100, 100, 250, 0,  5850,  64, -11.7f }
#define FMOD_PRESET_CONCERTHALL                     {  3900,   20,  29, 5000,  70, 100, 100, 250, 0,  5650,  80,  -9.8f }
#define FMOD_PRESET_CAVE                            {  2900,   15,  22, 5000, 100, 100, 100, 250, 0, 20000,  59, -11.3f }
#define FMOD_PRESET_ARENA                           {  7200,   20,  30, 5000,  33, 100, 100, 250, 0,  4500,  80,  -9.6f }
#define FMOD_PRESET_HANGAR                          { 10000,   20,  30, 5000,  23, 100, 100, 250, 0,  3400,  72,  -7.4f }
#define FMOD_PRESET_CARPETTEDHALLWAY                {   300,    2,  30, 5000,  10, 100, 100, 250, 0,   500,  56, -24.0f }
#define FMOD_PRESET_HALLWAY                         {  1500,    7,  11, 5000,  59, 100, 100, 250, 0,  7800,  87,  -5.5f }
#define FMOD_PRESET_STONECORRIDOR                   {   270,   13,  20, 5000,  79, 100, 100, 250, 0,  9000,  86,  -6.0f }
#define FMOD_PRESET_ALLEY                           {  1500,    7,  11, 5000,  86, 100, 100, 250, 0,  8300,  80,  -9.8f }
#define FMOD_PRESET_FOREST                          {  1500,  162,  88, 5000,  54,  79, 100, 250, 0,   760,  94, -12.3f }
#define FMOD_PRESET_CITY                            {  1500,    7,  11, 5000,  67,  50, 100, 250, 0,  4050,  66, -26.0f }
#define FMOD_PRESET_MOUNTAINS                       {  1500,  300, 100, 5000,  21,  27, 100, 250, 0,  1220,  82, -24.0f }
#define FMOD_PRESET_QUARRY                          {  1500,   61,  25, 5000,  83, 100, 100, 250, 0,  3400, 100,  -5.0f }
#define FMOD_PRESET_PLAIN                           {  1500,  179, 100, 5000,  50,  21, 100, 250, 0,  1670,  65, -28.0f }
#define FMOD_PRESET_PARKINGLOT                      {  1700,    8,  12, 5000, 100, 100, 100, 250, 0, 20000,  56, -19.5f }
#define FMOD_PRESET_SEWERPIPE                       {  2800,   14,  21, 5000,  14,  80,  60, 250, 0,  3400,  66,   1.2f }
#define FMOD_PRESET_UNDERWATER                      {  1500,    7,  11, 5000,  10, 100, 100, 250, 0,   500,  92,   7.0f }

#define FMOD_MAX_CHANNEL_WIDTH                      32
#define FMOD_MAX_SYSTEMS                            8
#define FMOD_MAX_LISTENERS                          8
#define FMOD_REVERB_MAXINSTANCES                    4
#define FMOD_PORT_INDEX_NONE                        0xFFFFFFFFFFFFFFFF

typedef enum FMOD_THREAD_TYPE
{
    FMOD_THREAD_TYPE_MIXER,
    FMOD_THREAD_TYPE_FEEDER,
    FMOD_THREAD_TYPE_STREAM,
    FMOD_THREAD_TYPE_FILE,
    FMOD_THREAD_TYPE_NONBLOCKING,
    FMOD_THREAD_TYPE_RECORD,
    FMOD_THREAD_TYPE_GEOMETRY,
    FMOD_THREAD_TYPE_PROFILER,
    FMOD_THREAD_TYPE_STUDIO_UPDATE,
    FMOD_THREAD_TYPE_STUDIO_LOAD_BANK,
    FMOD_THREAD_TYPE_STUDIO_LOAD_SAMPLE,
    FMOD_THREAD_TYPE_CONVOLUTION1,
    FMOD_THREAD_TYPE_CONVOLUTION2,

    FMOD_THREAD_TYPE_MAX,
    FMOD_THREAD_TYPE_FORCEINT = 65536
} FMOD_THREAD_TYPE;

typedef enum FMOD_RESULT
{
    FMOD_OK,
    FMOD_ERR_BADCOMMAND,
    FMOD_ERR_CHANNEL_ALLOC,
    FMOD_ERR_CHANNEL_STOLEN,
    FMOD_ERR_DMA,
    FMOD_ERR_DSP_CONNECTION,
    FMOD_ERR_DSP_DONTPROCESS,
    FMOD_ERR_DSP_FORMAT,
    FMOD_ERR_DSP_INUSE,
    FMOD_ERR_DSP_NOTFOUND,
    FMOD_ERR_DSP_RESERVED,
    FMOD_ERR_DSP_SILENCE,
    FMOD_ERR_DSP_TYPE,
    FMOD_ERR_FILE_BAD,
    FMOD_ERR_FILE_COULDNOTSEEK,
    FMOD_ERR_FILE_DISKEJECTED,
    FMOD_ERR_FILE_EOF,
    FMOD_ERR_FILE_ENDOFDATA,
    FMOD_ERR_FILE_NOTFOUND,
    FMOD_ERR_FORMAT,
    FMOD_ERR_HEADER_MISMATCH,
    FMOD_ERR_HTTP,
    FMOD_ERR_HTTP_ACCESS,
    FMOD_ERR_HTTP_PROXY_AUTH,
    FMOD_ERR_HTTP_SERVER_ERROR,
    FMOD_ERR_HTTP_TIMEOUT,
    FMOD_ERR_INITIALIZATION,
    FMOD_ERR_INITIALIZED,
    FMOD_ERR_INTERNAL,
    FMOD_ERR_INVALID_FLOAT,
    FMOD_ERR_INVALID_HANDLE,
    FMOD_ERR_INVALID_PARAM,
    FMOD_ERR_INVALID_POSITION,
    FMOD_ERR_INVALID_SPEAKER,
    FMOD_ERR_INVALID_SYNCPOINT,
    FMOD_ERR_INVALID_THREAD,
    FMOD_ERR_INVALID_VECTOR,
    FMOD_ERR_MAXAUDIBLE,
    FMOD_ERR_MEMORY,
    FMOD_ERR_MEMORY_CANTPOINT,
    FMOD_ERR_NEEDS3D,
    FMOD_ERR_NEEDSHARDWARE,
    FMOD_ERR_NET_CONNECT,
    FMOD_ERR_NET_SOCKET_ERROR,
    FMOD_ERR_NET_URL,
    FMOD_ERR_NET_WOULD_BLOCK,
    FMOD_ERR_NOTREADY,
    FMOD_ERR_OUTPUT_ALLOCATED,
    FMOD_ERR_OUTPUT_CREATEBUFFER,
    FMOD_ERR_OUTPUT_DRIVERCALL,
    FMOD_ERR_OUTPUT_FORMAT,
    FMOD_ERR_OUTPUT_INIT,
    FMOD_ERR_OUTPUT_NODRIVERS,
    FMOD_ERR_PLUGIN,
    FMOD_ERR_PLUGIN_MISSING,
    FMOD_ERR_PLUGIN_RESOURCE,
    FMOD_ERR_PLUGIN_VERSION,
    FMOD_ERR_RECORD,
    FMOD_ERR_REVERB_CHANNELGROUP,
    FMOD_ERR_REVERB_INSTANCE,
    FMOD_ERR_SUBSOUNDS,
    FMOD_ERR_SUBSOUND_ALLOCATED,
    FMOD_ERR_SUBSOUND_CANTMOVE,
    FMOD_ERR_TAGNOTFOUND,
    FMOD_ERR_TOOMANYCHANNELS,
    FMOD_ERR_TRUNCATED,
    FMOD_ERR_UNIMPLEMENTED,
    FMOD_ERR_UNINITIALIZED,
    FMOD_ERR_UNSUPPORTED,
    FMOD_ERR_VERSION,
    FMOD_ERR_EVENT_ALREADY_LOADED,
    FMOD_ERR_EVENT_LIVEUPDATE_BUSY,
    FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH,
    FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT,
    FMOD_ERR_EVENT_NOTFOUND,
    FMOD_ERR_STUDIO_UNINITIALIZED,
    FMOD_ERR_STUDIO_NOT_LOADED,
    FMOD_ERR_INVALID_STRING,
    FMOD_ERR_ALREADY_LOCKED,
    FMOD_ERR_NOT_LOCKED,
    FMOD_ERR_RECORD_DISCONNECTED,
    FMOD_ERR_TOOMANYSAMPLES,

    FMOD_RESULT_FORCEINT = 65536
} FMOD_RESULT;

typedef enum FMOD_CHANNELCONTROL_TYPE
{
    FMOD_CHANNELCONTROL_CHANNEL,
    FMOD_CHANNELCONTROL_CHANNELGROUP,

    FMOD_CHANNELCONTROL_MAX,
    FMOD_CHANNELCONTROL_FORCEINT = 65536
} FMOD_CHANNELCONTROL_TYPE;

typedef enum FMOD_OUTPUTTYPE
{
    FMOD_OUTPUTTYPE_AUTODETECT,
    FMOD_OUTPUTTYPE_UNKNOWN,
    FMOD_OUTPUTTYPE_NOSOUND,
    FMOD_OUTPUTTYPE_WAVWRITER,
    FMOD_OUTPUTTYPE_NOSOUND_NRT,
    FMOD_OUTPUTTYPE_WAVWRITER_NRT,
    FMOD_OUTPUTTYPE_WASAPI,
    FMOD_OUTPUTTYPE_ASIO,
    FMOD_OUTPUTTYPE_PULSEAUDIO,
    FMOD_OUTPUTTYPE_ALSA,
    FMOD_OUTPUTTYPE_COREAUDIO,
    FMOD_OUTPUTTYPE_AUDIOTRACK,
    FMOD_OUTPUTTYPE_OPENSL,
    FMOD_OUTPUTTYPE_AUDIOOUT,
    FMOD_OUTPUTTYPE_AUDIO3D,
    FMOD_OUTPUTTYPE_WEBAUDIO,
    FMOD_OUTPUTTYPE_NNAUDIO,
    FMOD_OUTPUTTYPE_WINSONIC,
    FMOD_OUTPUTTYPE_AAUDIO,
    FMOD_OUTPUTTYPE_AUDIOWORKLET,

    FMOD_OUTPUTTYPE_MAX,
    FMOD_OUTPUTTYPE_FORCEINT = 65536
} FMOD_OUTPUTTYPE;

typedef enum FMOD_DEBUG_MODE
{
    FMOD_DEBUG_MODE_TTY,
    FMOD_DEBUG_MODE_FILE,
    FMOD_DEBUG_MODE_CALLBACK,

    FMOD_DEBUG_MODE_FORCEINT = 65536
} FMOD_DEBUG_MODE;

typedef enum FMOD_SPEAKERMODE
{
    FMOD_SPEAKERMODE_DEFAULT,
    FMOD_SPEAKERMODE_RAW,
    FMOD_SPEAKERMODE_MONO,
    FMOD_SPEAKERMODE_STEREO,
    FMOD_SPEAKERMODE_QUAD,
    FMOD_SPEAKERMODE_SURROUND,
    FMOD_SPEAKERMODE_5POINT1,
    FMOD_SPEAKERMODE_7POINT1,
    FMOD_SPEAKERMODE_7POINT1POINT4,

    FMOD_SPEAKERMODE_MAX,
    FMOD_SPEAKERMODE_FORCEINT = 65536
} FMOD_SPEAKERMODE;

typedef enum FMOD_SPEAKER
{
    FMOD_SPEAKER_NONE = -1,
    FMOD_SPEAKER_FRONT_LEFT = 0,
    FMOD_SPEAKER_FRONT_RIGHT,
    FMOD_SPEAKER_FRONT_CENTER,
    FMOD_SPEAKER_LOW_FREQUENCY,
    FMOD_SPEAKER_SURROUND_LEFT,
    FMOD_SPEAKER_SURROUND_RIGHT,
    FMOD_SPEAKER_BACK_LEFT,
    FMOD_SPEAKER_BACK_RIGHT,
    FMOD_SPEAKER_TOP_FRONT_LEFT,
    FMOD_SPEAKER_TOP_FRONT_RIGHT,
    FMOD_SPEAKER_TOP_BACK_LEFT,
    FMOD_SPEAKER_TOP_BACK_RIGHT,

    FMOD_SPEAKER_MAX,
    FMOD_SPEAKER_FORCEINT = 65536
} FMOD_SPEAKER;

typedef enum FMOD_CHANNELORDER
{
    FMOD_CHANNELORDER_DEFAULT,
    FMOD_CHANNELORDER_WAVEFORMAT,
    FMOD_CHANNELORDER_PROTOOLS,
    FMOD_CHANNELORDER_ALLMONO,
    FMOD_CHANNELORDER_ALLSTEREO,
    FMOD_CHANNELORDER_ALSA,

    FMOD_CHANNELORDER_MAX,
    FMOD_CHANNELORDER_FORCEINT = 65536
} FMOD_CHANNELORDER;

typedef enum FMOD_PLUGINTYPE
{
    FMOD_PLUGINTYPE_OUTPUT,
    FMOD_PLUGINTYPE_CODEC,
    FMOD_PLUGINTYPE_DSP,

    FMOD_PLUGINTYPE_MAX,
    FMOD_PLUGINTYPE_FORCEINT = 65536
} FMOD_PLUGINTYPE;

typedef enum FMOD_SOUND_TYPE
{
    FMOD_SOUND_TYPE_UNKNOWN,
    FMOD_SOUND_TYPE_AIFF,
    FMOD_SOUND_TYPE_ASF,
    FMOD_SOUND_TYPE_DLS,
    FMOD_SOUND_TYPE_FLAC,
    FMOD_SOUND_TYPE_FSB,
    FMOD_SOUND_TYPE_IT,
    FMOD_SOUND_TYPE_MIDI,
    FMOD_SOUND_TYPE_MOD,
    FMOD_SOUND_TYPE_MPEG,
    FMOD_SOUND_TYPE_OGGVORBIS,
    FMOD_SOUND_TYPE_PLAYLIST,
    FMOD_SOUND_TYPE_RAW,
    FMOD_SOUND_TYPE_S3M,
    FMOD_SOUND_TYPE_USER,
    FMOD_SOUND_TYPE_WAV,
    FMOD_SOUND_TYPE_XM,
    FMOD_SOUND_TYPE_XMA,
    FMOD_SOUND_TYPE_AUDIOQUEUE,
    FMOD_SOUND_TYPE_AT9,
    FMOD_SOUND_TYPE_VORBIS,
    FMOD_SOUND_TYPE_MEDIA_FOUNDATION,
    FMOD_SOUND_TYPE_MEDIACODEC,
    FMOD_SOUND_TYPE_FADPCM,
    FMOD_SOUND_TYPE_OPUS,

    FMOD_SOUND_TYPE_MAX,
    FMOD_SOUND_TYPE_FORCEINT = 65536
} FMOD_SOUND_TYPE;

typedef enum FMOD_SOUND_FORMAT
{
    FMOD_SOUND_FORMAT_NONE,
    FMOD_SOUND_FORMAT_PCM8,
    FMOD_SOUND_FORMAT_PCM16,
    FMOD_SOUND_FORMAT_PCM24,
    FMOD_SOUND_FORMAT_PCM32,
    FMOD_SOUND_FORMAT_PCMFLOAT,
    FMOD_SOUND_FORMAT_BITSTREAM,

    FMOD_SOUND_FORMAT_MAX,
    FMOD_SOUND_FORMAT_FORCEINT = 65536
} FMOD_SOUND_FORMAT;

typedef enum FMOD_OPENSTATE
{
    FMOD_OPENSTATE_READY,
    FMOD_OPENSTATE_LOADING,
    FMOD_OPENSTATE_ERROR,
    FMOD_OPENSTATE_CONNECTING,
    FMOD_OPENSTATE_BUFFERING,
    FMOD_OPENSTATE_SEEKING,
    FMOD_OPENSTATE_PLAYING,
    FMOD_OPENSTATE_SETPOSITION,

    FMOD_OPENSTATE_MAX,
    FMOD_OPENSTATE_FORCEINT = 65536
} FMOD_OPENSTATE;

typedef enum FMOD_SOUNDGROUP_BEHAVIOR
{
    FMOD_SOUNDGROUP_BEHAVIOR_FAIL,
    FMOD_SOUNDGROUP_BEHAVIOR_MUTE,
    FMOD_SOUNDGROUP_BEHAVIOR_STEALLOWEST,

    FMOD_SOUNDGROUP_BEHAVIOR_MAX,
    FMOD_SOUNDGROUP_BEHAVIOR_FORCEINT = 65536
} FMOD_SOUNDGROUP_BEHAVIOR;

typedef enum FMOD_CHANNELCONTROL_CALLBACK_TYPE
{
    FMOD_CHANNELCONTROL_CALLBACK_END,
    FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE,
    FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT,
    FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION,

    FMOD_CHANNELCONTROL_CALLBACK_MAX,
    FMOD_CHANNELCONTROL_CALLBACK_FORCEINT = 65536
} FMOD_CHANNELCONTROL_CALLBACK_TYPE;

typedef enum FMOD_CHANNELCONTROL_DSP_INDEX
{
    FMOD_CHANNELCONTROL_DSP_HEAD     = -1,
    FMOD_CHANNELCONTROL_DSP_FADER    = -2,
    FMOD_CHANNELCONTROL_DSP_TAIL     = -3,

    FMOD_CHANNELCONTROL_DSP_FORCEINT = 65536
} FMOD_CHANNELCONTROL_DSP_INDEX;

typedef enum FMOD_ERRORCALLBACK_INSTANCETYPE
{
    FMOD_ERRORCALLBACK_INSTANCETYPE_NONE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_SYSTEM,
    FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNEL,
    FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELGROUP,
    FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELCONTROL,
    FMOD_ERRORCALLBACK_INSTANCETYPE_SOUND,
    FMOD_ERRORCALLBACK_INSTANCETYPE_SOUNDGROUP,
    FMOD_ERRORCALLBACK_INSTANCETYPE_DSP,
    FMOD_ERRORCALLBACK_INSTANCETYPE_DSPCONNECTION,
    FMOD_ERRORCALLBACK_INSTANCETYPE_GEOMETRY,
    FMOD_ERRORCALLBACK_INSTANCETYPE_REVERB3D,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_SYSTEM,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTDESCRIPTION,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTINSTANCE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_PARAMETERINSTANCE,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BUS,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_VCA,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BANK,
    FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_COMMANDREPLAY,

    FMOD_ERRORCALLBACK_INSTANCETYPE_FORCEINT = 65536
} FMOD_ERRORCALLBACK_INSTANCETYPE;

typedef enum FMOD_DSP_RESAMPLER
{
    FMOD_DSP_RESAMPLER_DEFAULT,
    FMOD_DSP_RESAMPLER_NOINTERP,
    FMOD_DSP_RESAMPLER_LINEAR,
    FMOD_DSP_RESAMPLER_CUBIC,
    FMOD_DSP_RESAMPLER_SPLINE,

    FMOD_DSP_RESAMPLER_MAX,
    FMOD_DSP_RESAMPLER_FORCEINT = 65536
} FMOD_DSP_RESAMPLER;

typedef enum FMOD_DSPCONNECTION_TYPE
{
    FMOD_DSPCONNECTION_TYPE_STANDARD,
    FMOD_DSPCONNECTION_TYPE_SIDECHAIN,
    FMOD_DSPCONNECTION_TYPE_SEND,
    FMOD_DSPCONNECTION_TYPE_SEND_SIDECHAIN,

    FMOD_DSPCONNECTION_TYPE_MAX,
    FMOD_DSPCONNECTION_TYPE_FORCEINT = 65536
} FMOD_DSPCONNECTION_TYPE;

typedef enum FMOD_TAGTYPE
{
    FMOD_TAGTYPE_UNKNOWN,
    FMOD_TAGTYPE_ID3V1,
    FMOD_TAGTYPE_ID3V2,
    FMOD_TAGTYPE_VORBISCOMMENT,
    FMOD_TAGTYPE_SHOUTCAST,
    FMOD_TAGTYPE_ICECAST,
    FMOD_TAGTYPE_ASF,
    FMOD_TAGTYPE_MIDI,
    FMOD_TAGTYPE_PLAYLIST,
    FMOD_TAGTYPE_FMOD,
    FMOD_TAGTYPE_USER,

    FMOD_TAGTYPE_MAX,
    FMOD_TAGTYPE_FORCEINT = 65536
} FMOD_TAGTYPE;

typedef enum FMOD_TAGDATATYPE
{
    FMOD_TAGDATATYPE_BINARY,
    FMOD_TAGDATATYPE_INT,
    FMOD_TAGDATATYPE_FLOAT,
    FMOD_TAGDATATYPE_STRING,
    FMOD_TAGDATATYPE_STRING_UTF16,
    FMOD_TAGDATATYPE_STRING_UTF16BE,
    FMOD_TAGDATATYPE_STRING_UTF8,

    FMOD_TAGDATATYPE_MAX,
    FMOD_TAGDATATYPE_FORCEINT = 65536
} FMOD_TAGDATATYPE;

typedef enum FMOD_PORT_TYPE
{
    FMOD_PORT_TYPE_MUSIC,
    FMOD_PORT_TYPE_COPYRIGHT_MUSIC,
    FMOD_PORT_TYPE_VOICE,
    FMOD_PORT_TYPE_CONTROLLER,
    FMOD_PORT_TYPE_PERSONAL,
    FMOD_PORT_TYPE_VIBRATION,
    FMOD_PORT_TYPE_AUX,

    FMOD_PORT_TYPE_MAX,
    FMOD_PORT_TYPE_FORCEINT = 65536
} FMOD_PORT_TYPE;

/*
    FMOD callbacks
*/
typedef FMOD_RESULT (F_CALL *FMOD_DEBUG_CALLBACK)           (FMOD_DEBUG_FLAGS flags, const char *file, int line, const char* func, const char* message);
typedef FMOD_RESULT (F_CALL *FMOD_SYSTEM_CALLBACK)          (FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK_TYPE type, void *commanddata1, void* commanddata2, void *userdata);
typedef FMOD_RESULT (F_CALL *FMOD_CHANNELCONTROL_CALLBACK)  (FMOD_CHANNELCONTROL *channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2);
typedef FMOD_RESULT (F_CALL *FMOD_SOUND_NONBLOCK_CALLBACK)  (FMOD_SOUND *sound, FMOD_RESULT result);
typedef FMOD_RESULT (F_CALL *FMOD_SOUND_PCMREAD_CALLBACK)   (FMOD_SOUND *sound, void *data, unsigned int datalen);
typedef FMOD_RESULT (F_CALL *FMOD_SOUND_PCMSETPOS_CALLBACK) (FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype);
typedef FMOD_RESULT (F_CALL *FMOD_FILE_OPEN_CALLBACK)       (const char *name, unsigned int *filesize, void **handle, void *userdata);
typedef FMOD_RESULT (F_CALL *FMOD_FILE_CLOSE_CALLBACK)      (void *handle, void *userdata);
typedef FMOD_RESULT (F_CALL *FMOD_FILE_READ_CALLBACK)       (void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);
typedef FMOD_RESULT (F_CALL *FMOD_FILE_SEEK_CALLBACK)       (void *handle, unsigned int pos, void *userdata);
typedef FMOD_RESULT (F_CALL *FMOD_FILE_ASYNCREAD_CALLBACK)  (FMOD_ASYNCREADINFO *info, void *userdata);
typedef FMOD_RESULT (F_CALL *FMOD_FILE_ASYNCCANCEL_CALLBACK)(FMOD_ASYNCREADINFO *info, void *userdata);
typedef void        (F_CALL *FMOD_FILE_ASYNCDONE_FUNC)      (FMOD_ASYNCREADINFO *info, FMOD_RESULT result);
typedef void*       (F_CALL *FMOD_MEMORY_ALLOC_CALLBACK)    (unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void*       (F_CALL *FMOD_MEMORY_REALLOC_CALLBACK)  (void *ptr, unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void        (F_CALL *FMOD_MEMORY_FREE_CALLBACK)     (void *ptr, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef float       (F_CALL *FMOD_3D_ROLLOFF_CALLBACK)      (FMOD_CHANNELCONTROL *channelcontrol, float distance);

/*
    FMOD structs
*/
struct FMOD_ASYNCREADINFO
{
    void                     *handle;
    unsigned int              offset;
    unsigned int              sizebytes;
    int                       priority;
    void                     *userdata;
    void                     *buffer;
    unsigned int              bytesread;
    FMOD_FILE_ASYNCDONE_FUNC  done;
};

typedef struct FMOD_VECTOR
{
    float x;
    float y;
    float z;
} FMOD_VECTOR;

typedef struct FMOD_3D_ATTRIBUTES
{
    FMOD_VECTOR position;
    FMOD_VECTOR velocity;
    FMOD_VECTOR forward;
    FMOD_VECTOR up;
} FMOD_3D_ATTRIBUTES;

typedef struct FMOD_GUID
{
    unsigned int   Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} FMOD_GUID;

typedef struct FMOD_PLUGINLIST
{
    FMOD_PLUGINTYPE  type;
    void            *description;
} FMOD_PLUGINLIST;

typedef struct FMOD_ADVANCEDSETTINGS
{
    int                 cbSize;
    int                 maxMPEGCodecs;
    int                 maxADPCMCodecs;
    int                 maxXMACodecs;
    int                 maxVorbisCodecs;
    int                 maxAT9Codecs;
    int                 maxFADPCMCodecs;
    int                 maxPCMCodecs;
    int                 ASIONumChannels;
    char              **ASIOChannelList;
    FMOD_SPEAKER       *ASIOSpeakerList;
    float               vol0virtualvol;
    unsigned int        defaultDecodeBufferSize;
    unsigned short      profilePort;
    unsigned int        geometryMaxFadeTime;
    float               distanceFilterCenterFreq;
    int                 reverb3Dinstance;
    int                 DSPBufferPoolSize;
    FMOD_DSP_RESAMPLER  resamplerMethod;
    unsigned int        randomSeed;
    int                 maxConvolutionThreads;
    int                 maxOpusCodecs;
} FMOD_ADVANCEDSETTINGS;

typedef struct FMOD_TAG
{
    FMOD_TAGTYPE      type;
    FMOD_TAGDATATYPE  datatype;
    char             *name;
    void             *data;
    unsigned int      datalen;
    FMOD_BOOL         updated;
} FMOD_TAG;

typedef struct FMOD_CREATESOUNDEXINFO
{
    int                            cbsize;
    unsigned int                   length;
    unsigned int                   fileoffset;
    int                            numchannels;
    int                            defaultfrequency;
    FMOD_SOUND_FORMAT              format;
    unsigned int                   decodebuffersize;
    int                            initialsubsound;
    int                            numsubsounds;
    int                           *inclusionlist;
    int                            inclusionlistnum;
    FMOD_SOUND_PCMREAD_CALLBACK    pcmreadcallback;
    FMOD_SOUND_PCMSETPOS_CALLBACK  pcmsetposcallback;
    FMOD_SOUND_NONBLOCK_CALLBACK   nonblockcallback;
    const char                    *dlsname;
    const char                    *encryptionkey;
    int                            maxpolyphony;
    void                          *userdata;
    FMOD_SOUND_TYPE                suggestedsoundtype;
    FMOD_FILE_OPEN_CALLBACK        fileuseropen;
    FMOD_FILE_CLOSE_CALLBACK       fileuserclose;
    FMOD_FILE_READ_CALLBACK        fileuserread;
    FMOD_FILE_SEEK_CALLBACK        fileuserseek;
    FMOD_FILE_ASYNCREAD_CALLBACK   fileuserasyncread;
    FMOD_FILE_ASYNCCANCEL_CALLBACK fileuserasynccancel;
    void                          *fileuserdata;
    int                            filebuffersize;
    FMOD_CHANNELORDER              channelorder;
    FMOD_SOUNDGROUP               *initialsoundgroup;
    unsigned int                   initialseekposition;
    FMOD_TIMEUNIT                  initialseekpostype;
    int                            ignoresetfilesystem;
    unsigned int                   audioqueuepolicy;
    unsigned int                   minmidigranularity;
    int                            nonblockthreadid;
    FMOD_GUID                     *fsbguid;
} FMOD_CREATESOUNDEXINFO;

typedef struct FMOD_REVERB_PROPERTIES
{
    float DecayTime;
    float EarlyDelay;
    float LateDelay;
    float HFReference;
    float HFDecayRatio;
    float Diffusion;
    float Density;
    float LowShelfFrequency;
    float LowShelfGain;
    float HighCut;
    float EarlyLateMix;
    float WetLevel;
} FMOD_REVERB_PROPERTIES;

typedef struct FMOD_ERRORCALLBACK_INFO
{
    FMOD_RESULT                      result;
    FMOD_ERRORCALLBACK_INSTANCETYPE  instancetype;
    void                            *instance;
    const char                      *functionname;
    const char                      *functionparams;
} FMOD_ERRORCALLBACK_INFO;

typedef struct FMOD_CPU_USAGE
{
    float           dsp;
    float           stream;
    float           geometry;
    float           update;
    float           convolution1;
    float           convolution2;
} FMOD_CPU_USAGE;


/*
    FMOD optional headers for plugin development
*/
/*
    Codec types
*/
typedef struct FMOD_CODEC_STATE      FMOD_CODEC_STATE;
typedef struct FMOD_CODEC_WAVEFORMAT FMOD_CODEC_WAVEFORMAT;

/*
    Codec constants
*/
#define FMOD_CODEC_PLUGIN_VERSION 1

typedef int FMOD_CODEC_SEEK_METHOD;
#define FMOD_CODEC_SEEK_METHOD_SET      0
#define FMOD_CODEC_SEEK_METHOD_CURRENT  1
#define FMOD_CODEC_SEEK_METHOD_END      2

/*
    Codec callbacks
*/
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_OPEN_CALLBACK)         (FMOD_CODEC_STATE *codec_state, FMOD_MODE usermode, FMOD_CREATESOUNDEXINFO *userexinfo);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_CLOSE_CALLBACK)        (FMOD_CODEC_STATE *codec_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_READ_CALLBACK)         (FMOD_CODEC_STATE *codec_state, void *buffer, unsigned int samples_in, unsigned int *samples_out);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_GETLENGTH_CALLBACK)    (FMOD_CODEC_STATE *codec_state, unsigned int *length, FMOD_TIMEUNIT lengthtype);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_SETPOSITION_CALLBACK)  (FMOD_CODEC_STATE *codec_state, int subsound, unsigned int position, FMOD_TIMEUNIT postype);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_GETPOSITION_CALLBACK)  (FMOD_CODEC_STATE *codec_state, unsigned int *position, FMOD_TIMEUNIT postype);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_SOUNDCREATE_CALLBACK)  (FMOD_CODEC_STATE *codec_state, int subsound, FMOD_SOUND *sound);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_GETWAVEFORMAT_CALLBACK)(FMOD_CODEC_STATE *codec_state, int index, FMOD_CODEC_WAVEFORMAT *waveformat);

/*
    Codec functions
*/
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_METADATA_FUNC)         (FMOD_CODEC_STATE *codec_state, FMOD_TAGTYPE tagtype, char *name, void *data, unsigned int datalen, FMOD_TAGDATATYPE datatype, int unique);
typedef void *      (F_CALLBACK *FMOD_CODEC_ALLOC_FUNC)            (unsigned int size, unsigned int align, const char *file, int line);
typedef void        (F_CALLBACK *FMOD_CODEC_FREE_FUNC)             (void *ptr, const char *file, int line);
typedef void        (F_CALLBACK *FMOD_CODEC_LOG_FUNC)              (FMOD_DEBUG_FLAGS level, const char *file, int line, const char *function, const char *string, ...);

typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_FILE_READ_FUNC)        (FMOD_CODEC_STATE *codec_state, void *buffer, unsigned int sizebytes, unsigned int *bytesread);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_FILE_SEEK_FUNC)        (FMOD_CODEC_STATE *codec_state, unsigned int pos, FMOD_CODEC_SEEK_METHOD method);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_FILE_TELL_FUNC)        (FMOD_CODEC_STATE *codec_state, unsigned int *pos);
typedef FMOD_RESULT (F_CALLBACK *FMOD_CODEC_FILE_SIZE_FUNC)        (FMOD_CODEC_STATE *codec_state, unsigned int *size);

/*
    Codec structures
*/
typedef struct FMOD_CODEC_DESCRIPTION
{
    unsigned int                      apiversion;
    const char                       *name;
    unsigned int                      version;
    int                               defaultasstream;
    FMOD_TIMEUNIT                     timeunits;
    FMOD_CODEC_OPEN_CALLBACK          open;
    FMOD_CODEC_CLOSE_CALLBACK         close;
    FMOD_CODEC_READ_CALLBACK          read;
    FMOD_CODEC_GETLENGTH_CALLBACK     getlength;
    FMOD_CODEC_SETPOSITION_CALLBACK   setposition;
    FMOD_CODEC_GETPOSITION_CALLBACK   getposition;
    FMOD_CODEC_SOUNDCREATE_CALLBACK   soundcreate;
    FMOD_CODEC_GETWAVEFORMAT_CALLBACK getwaveformat;
} FMOD_CODEC_DESCRIPTION;

struct FMOD_CODEC_WAVEFORMAT
{
    const char*        name;
    FMOD_SOUND_FORMAT  format;
    int                channels;
    int                frequency;
    unsigned int       lengthbytes;
    unsigned int       lengthpcm;
    unsigned int       pcmblocksize;
    int                loopstart;
    int                loopend;
    FMOD_MODE          mode;
    FMOD_CHANNELMASK   channelmask;
    FMOD_CHANNELORDER  channelorder;
    float              peakvolume;
};

typedef struct FMOD_CODEC_STATE_FUNCTIONS
{
    FMOD_CODEC_METADATA_FUNC     metadata;
    FMOD_CODEC_ALLOC_FUNC        alloc;
    FMOD_CODEC_FREE_FUNC         free;
    FMOD_CODEC_LOG_FUNC          log;
    FMOD_CODEC_FILE_READ_FUNC    read;
    FMOD_CODEC_FILE_SEEK_FUNC    seek;
    FMOD_CODEC_FILE_TELL_FUNC    tell;
    FMOD_CODEC_FILE_SIZE_FUNC    size;
} FMOD_CODEC_STATE_FUNCTIONS;

struct FMOD_CODEC_STATE
{
    void                        *plugindata;
    FMOD_CODEC_WAVEFORMAT       *waveformat;
    FMOD_CODEC_STATE_FUNCTIONS  *functions;
    int                          numsubsounds;
};

/*
    Codec macros
*/
#define FMOD_CODEC_METADATA(_state, _tagtype, _name, _data, _datalen, _datatype, _unique) \
    (_state)->functions->metadata(_state, _tagtype, _name, _data, _datalen, _datatype, _unique)
#define FMOD_CODEC_ALLOC(_state, _size, _align) \
    (_state)->functions->alloc(_size, _align, __FILE__, __LINE__)
#define FMOD_CODEC_FREE(_state, _ptr) \
    (_state)->functions->free(_ptr, __FILE__, __LINE__)
#define FMOD_CODEC_LOG(_state, _level, _location, _format, ...) \
    (_state)->functions->log(_level, __FILE__, __LINE__, _location, _format, __VA_ARGS__)
#define FMOD_CODEC_FILE_READ(_state, _buffer, _sizebytes, _bytesread) \
    (_state)->functions->read(_state, _buffer, _sizebytes, _bytesread)
#define FMOD_CODEC_FILE_SEEK(_state, _pos, _method) \
    (_state)->functions->seek(_state, _pos, _method)
#define FMOD_CODEC_FILE_TELL(_state, _pos) \
    (_state)->functions->tell(_state, _pos)
#define FMOD_CODEC_FILE_SIZE(_state, _size) \
    (_state)->functions->size(_state, _size)
typedef enum
{
    FMOD_DSP_TYPE_UNKNOWN,
    FMOD_DSP_TYPE_MIXER,
    FMOD_DSP_TYPE_OSCILLATOR,
    FMOD_DSP_TYPE_LOWPASS,
    FMOD_DSP_TYPE_ITLOWPASS,
    FMOD_DSP_TYPE_HIGHPASS,
    FMOD_DSP_TYPE_ECHO,
    FMOD_DSP_TYPE_FADER,
    FMOD_DSP_TYPE_FLANGE,
    FMOD_DSP_TYPE_DISTORTION,
    FMOD_DSP_TYPE_NORMALIZE,
    FMOD_DSP_TYPE_LIMITER,
    FMOD_DSP_TYPE_PARAMEQ,
    FMOD_DSP_TYPE_PITCHSHIFT,
    FMOD_DSP_TYPE_CHORUS,
    FMOD_DSP_TYPE_VSTPLUGIN,
    FMOD_DSP_TYPE_WINAMPPLUGIN,
    FMOD_DSP_TYPE_ITECHO,
    FMOD_DSP_TYPE_COMPRESSOR,
    FMOD_DSP_TYPE_SFXREVERB,
    FMOD_DSP_TYPE_LOWPASS_SIMPLE,
    FMOD_DSP_TYPE_DELAY,
    FMOD_DSP_TYPE_TREMOLO,
    FMOD_DSP_TYPE_LADSPAPLUGIN,
    FMOD_DSP_TYPE_SEND,
    FMOD_DSP_TYPE_RETURN,
    FMOD_DSP_TYPE_HIGHPASS_SIMPLE,
    FMOD_DSP_TYPE_PAN,
    FMOD_DSP_TYPE_THREE_EQ,
    FMOD_DSP_TYPE_FFT,
    FMOD_DSP_TYPE_LOUDNESS_METER,
    FMOD_DSP_TYPE_ENVELOPEFOLLOWER,
    FMOD_DSP_TYPE_CONVOLUTIONREVERB,
    FMOD_DSP_TYPE_CHANNELMIX,
    FMOD_DSP_TYPE_TRANSCEIVER,
    FMOD_DSP_TYPE_OBJECTPAN,
    FMOD_DSP_TYPE_MULTIBAND_EQ,

    FMOD_DSP_TYPE_MAX,
    FMOD_DSP_TYPE_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_TYPE;

/*
    ===================================================================================================
    FMOD built in effect parameters.  
    Use DSP::setParameter with these enums for the 'index' parameter.
    ===================================================================================================
*/

typedef enum
{
    FMOD_DSP_OSCILLATOR_TYPE,
    FMOD_DSP_OSCILLATOR_RATE
} FMOD_DSP_OSCILLATOR;


typedef enum
{
    FMOD_DSP_LOWPASS_CUTOFF,
    FMOD_DSP_LOWPASS_RESONANCE
} FMOD_DSP_LOWPASS;


typedef enum
{
    FMOD_DSP_ITLOWPASS_CUTOFF,
    FMOD_DSP_ITLOWPASS_RESONANCE
} FMOD_DSP_ITLOWPASS;


typedef enum
{
    FMOD_DSP_HIGHPASS_CUTOFF,
    FMOD_DSP_HIGHPASS_RESONANCE
} FMOD_DSP_HIGHPASS;


typedef enum
{
    FMOD_DSP_ECHO_DELAY,
    FMOD_DSP_ECHO_FEEDBACK,
    FMOD_DSP_ECHO_DRYLEVEL,
    FMOD_DSP_ECHO_WETLEVEL
} FMOD_DSP_ECHO;


typedef enum FMOD_DSP_FADER
{
    FMOD_DSP_FADER_GAIN,
    FMOD_DSP_FADER_OVERALL_GAIN,
} FMOD_DSP_FADER;


typedef enum
{
    FMOD_DSP_FLANGE_MIX,
    FMOD_DSP_FLANGE_DEPTH,
    FMOD_DSP_FLANGE_RATE
} FMOD_DSP_FLANGE;


typedef enum
{
    FMOD_DSP_DISTORTION_LEVEL
} FMOD_DSP_DISTORTION;


typedef enum
{
    FMOD_DSP_NORMALIZE_FADETIME,
    FMOD_DSP_NORMALIZE_THRESHOLD,
    FMOD_DSP_NORMALIZE_MAXAMP
} FMOD_DSP_NORMALIZE;


typedef enum
{
    FMOD_DSP_LIMITER_RELEASETIME,
    FMOD_DSP_LIMITER_CEILING,
    FMOD_DSP_LIMITER_MAXIMIZERGAIN,
    FMOD_DSP_LIMITER_MODE,
} FMOD_DSP_LIMITER;


typedef enum
{
    FMOD_DSP_PARAMEQ_CENTER,
    FMOD_DSP_PARAMEQ_BANDWIDTH,
    FMOD_DSP_PARAMEQ_GAIN
} FMOD_DSP_PARAMEQ;


typedef enum FMOD_DSP_MULTIBAND_EQ
{
    FMOD_DSP_MULTIBAND_EQ_A_FILTER,
    FMOD_DSP_MULTIBAND_EQ_A_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_A_Q,
    FMOD_DSP_MULTIBAND_EQ_A_GAIN,
    FMOD_DSP_MULTIBAND_EQ_B_FILTER,
    FMOD_DSP_MULTIBAND_EQ_B_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_B_Q,
    FMOD_DSP_MULTIBAND_EQ_B_GAIN,
    FMOD_DSP_MULTIBAND_EQ_C_FILTER,
    FMOD_DSP_MULTIBAND_EQ_C_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_C_Q,
    FMOD_DSP_MULTIBAND_EQ_C_GAIN,
    FMOD_DSP_MULTIBAND_EQ_D_FILTER,
    FMOD_DSP_MULTIBAND_EQ_D_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_D_Q,
    FMOD_DSP_MULTIBAND_EQ_D_GAIN,
    FMOD_DSP_MULTIBAND_EQ_E_FILTER,
    FMOD_DSP_MULTIBAND_EQ_E_FREQUENCY,
    FMOD_DSP_MULTIBAND_EQ_E_Q,
    FMOD_DSP_MULTIBAND_EQ_E_GAIN,
} FMOD_DSP_MULTIBAND_EQ;


typedef enum FMOD_DSP_MULTIBAND_EQ_FILTER_TYPE
{
    FMOD_DSP_MULTIBAND_EQ_FILTER_DISABLED,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_12DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_24DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWPASS_48DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_12DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_24DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHPASS_48DB,
    FMOD_DSP_MULTIBAND_EQ_FILTER_LOWSHELF,
    FMOD_DSP_MULTIBAND_EQ_FILTER_HIGHSHELF,
    FMOD_DSP_MULTIBAND_EQ_FILTER_PEAKING,
    FMOD_DSP_MULTIBAND_EQ_FILTER_BANDPASS,
    FMOD_DSP_MULTIBAND_EQ_FILTER_NOTCH,
    FMOD_DSP_MULTIBAND_EQ_FILTER_ALLPASS,
} FMOD_DSP_MULTIBAND_EQ_FILTER_TYPE;


typedef enum
{
    FMOD_DSP_PITCHSHIFT_PITCH,
    FMOD_DSP_PITCHSHIFT_FFTSIZE,
    FMOD_DSP_PITCHSHIFT_OVERLAP,
    FMOD_DSP_PITCHSHIFT_MAXCHANNELS
} FMOD_DSP_PITCHSHIFT;


typedef enum
{
    FMOD_DSP_CHORUS_MIX,
    FMOD_DSP_CHORUS_RATE,
    FMOD_DSP_CHORUS_DEPTH,
} FMOD_DSP_CHORUS;


typedef enum
{
    FMOD_DSP_ITECHO_WETDRYMIX,
    FMOD_DSP_ITECHO_FEEDBACK,
    FMOD_DSP_ITECHO_LEFTDELAY,
    FMOD_DSP_ITECHO_RIGHTDELAY,
    FMOD_DSP_ITECHO_PANDELAY
} FMOD_DSP_ITECHO;

typedef enum
{
    FMOD_DSP_COMPRESSOR_THRESHOLD, 
    FMOD_DSP_COMPRESSOR_RATIO, 
    FMOD_DSP_COMPRESSOR_ATTACK,
    FMOD_DSP_COMPRESSOR_RELEASE,
    FMOD_DSP_COMPRESSOR_GAINMAKEUP,
    FMOD_DSP_COMPRESSOR_USESIDECHAIN,
    FMOD_DSP_COMPRESSOR_LINKED
} FMOD_DSP_COMPRESSOR;

typedef enum
{
    FMOD_DSP_SFXREVERB_DECAYTIME,
    FMOD_DSP_SFXREVERB_EARLYDELAY,
    FMOD_DSP_SFXREVERB_LATEDELAY,
    FMOD_DSP_SFXREVERB_HFREFERENCE,
    FMOD_DSP_SFXREVERB_HFDECAYRATIO,
    FMOD_DSP_SFXREVERB_DIFFUSION,
    FMOD_DSP_SFXREVERB_DENSITY,
    FMOD_DSP_SFXREVERB_LOWSHELFFREQUENCY,
    FMOD_DSP_SFXREVERB_LOWSHELFGAIN,
    FMOD_DSP_SFXREVERB_HIGHCUT,
    FMOD_DSP_SFXREVERB_EARLYLATEMIX,
    FMOD_DSP_SFXREVERB_WETLEVEL,
    FMOD_DSP_SFXREVERB_DRYLEVEL
} FMOD_DSP_SFXREVERB;

typedef enum
{
    FMOD_DSP_LOWPASS_SIMPLE_CUTOFF
} FMOD_DSP_LOWPASS_SIMPLE;


typedef enum
{
    FMOD_DSP_DELAY_CH0,
    FMOD_DSP_DELAY_CH1,
    FMOD_DSP_DELAY_CH2,
    FMOD_DSP_DELAY_CH3,
    FMOD_DSP_DELAY_CH4,
    FMOD_DSP_DELAY_CH5,
    FMOD_DSP_DELAY_CH6,
    FMOD_DSP_DELAY_CH7,
    FMOD_DSP_DELAY_CH8,
    FMOD_DSP_DELAY_CH9,
    FMOD_DSP_DELAY_CH10,
    FMOD_DSP_DELAY_CH11,
    FMOD_DSP_DELAY_CH12,
    FMOD_DSP_DELAY_CH13,
    FMOD_DSP_DELAY_CH14,
    FMOD_DSP_DELAY_CH15,
    FMOD_DSP_DELAY_MAXDELAY
} FMOD_DSP_DELAY;


typedef enum
{
    FMOD_DSP_TREMOLO_FREQUENCY,
    FMOD_DSP_TREMOLO_DEPTH,
    FMOD_DSP_TREMOLO_SHAPE,
    FMOD_DSP_TREMOLO_SKEW,
    FMOD_DSP_TREMOLO_DUTY,
    FMOD_DSP_TREMOLO_SQUARE,
    FMOD_DSP_TREMOLO_PHASE,
    FMOD_DSP_TREMOLO_SPREAD
} FMOD_DSP_TREMOLO;


typedef enum
{
    FMOD_DSP_SEND_RETURNID,
    FMOD_DSP_SEND_LEVEL,
} FMOD_DSP_SEND;


typedef enum
{
    FMOD_DSP_RETURN_ID,
    FMOD_DSP_RETURN_INPUT_SPEAKER_MODE
} FMOD_DSP_RETURN;


typedef enum
{
    FMOD_DSP_HIGHPASS_SIMPLE_CUTOFF
} FMOD_DSP_HIGHPASS_SIMPLE;


typedef enum
{
    FMOD_DSP_PAN_2D_STEREO_MODE_DISTRIBUTED,
    FMOD_DSP_PAN_2D_STEREO_MODE_DISCRETE
} FMOD_DSP_PAN_2D_STEREO_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PAN_MODE_MONO,
    FMOD_DSP_PAN_MODE_STEREO,
    FMOD_DSP_PAN_MODE_SURROUND
} FMOD_DSP_PAN_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PAN_3D_ROLLOFF_LINEARSQUARED,
    FMOD_DSP_PAN_3D_ROLLOFF_LINEAR,
    FMOD_DSP_PAN_3D_ROLLOFF_INVERSE,
    FMOD_DSP_PAN_3D_ROLLOFF_INVERSETAPERED,
    FMOD_DSP_PAN_3D_ROLLOFF_CUSTOM
} FMOD_DSP_PAN_3D_ROLLOFF_TYPE;


typedef enum
{
    FMOD_DSP_PAN_3D_EXTENT_MODE_AUTO,
    FMOD_DSP_PAN_3D_EXTENT_MODE_USER,
    FMOD_DSP_PAN_3D_EXTENT_MODE_OFF
} FMOD_DSP_PAN_3D_EXTENT_MODE_TYPE;


typedef enum
{
    FMOD_DSP_PAN_MODE,
    FMOD_DSP_PAN_2D_STEREO_POSITION,
    FMOD_DSP_PAN_2D_DIRECTION,
    FMOD_DSP_PAN_2D_EXTENT,
    FMOD_DSP_PAN_2D_ROTATION,
    FMOD_DSP_PAN_2D_LFE_LEVEL,
    FMOD_DSP_PAN_2D_STEREO_MODE,
    FMOD_DSP_PAN_2D_STEREO_SEPARATION,
    FMOD_DSP_PAN_2D_STEREO_AXIS,
    FMOD_DSP_PAN_ENABLED_SPEAKERS,
    FMOD_DSP_PAN_3D_POSITION,
    FMOD_DSP_PAN_3D_ROLLOFF,
    FMOD_DSP_PAN_3D_MIN_DISTANCE,
    FMOD_DSP_PAN_3D_MAX_DISTANCE,
    FMOD_DSP_PAN_3D_EXTENT_MODE,
    FMOD_DSP_PAN_3D_SOUND_SIZE,
    FMOD_DSP_PAN_3D_MIN_EXTENT,
    FMOD_DSP_PAN_3D_PAN_BLEND,
    FMOD_DSP_PAN_LFE_UPMIX_ENABLED,
    FMOD_DSP_PAN_OVERALL_GAIN,
    FMOD_DSP_PAN_SURROUND_SPEAKER_MODE,
    FMOD_DSP_PAN_2D_HEIGHT_BLEND,
    FMOD_DSP_PAN_ATTENUATION_RANGE,
    FMOD_DSP_PAN_OVERRIDE_RANGE
} FMOD_DSP_PAN;


typedef enum
{
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_12DB,
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_24DB,
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_48DB
} FMOD_DSP_THREE_EQ_CROSSOVERSLOPE_TYPE;


typedef enum
{
    FMOD_DSP_THREE_EQ_LOWGAIN,
    FMOD_DSP_THREE_EQ_MIDGAIN,
    FMOD_DSP_THREE_EQ_HIGHGAIN,
    FMOD_DSP_THREE_EQ_LOWCROSSOVER,
    FMOD_DSP_THREE_EQ_HIGHCROSSOVER,
    FMOD_DSP_THREE_EQ_CROSSOVERSLOPE
} FMOD_DSP_THREE_EQ;


typedef enum
{
    FMOD_DSP_FFT_WINDOW_RECT,
    FMOD_DSP_FFT_WINDOW_TRIANGLE,
    FMOD_DSP_FFT_WINDOW_HAMMING,
    FMOD_DSP_FFT_WINDOW_HANNING,
    FMOD_DSP_FFT_WINDOW_BLACKMAN,
    FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS
} FMOD_DSP_FFT_WINDOW;


typedef enum
{
    FMOD_DSP_FFT_WINDOWSIZE,
    FMOD_DSP_FFT_WINDOWTYPE,
    FMOD_DSP_FFT_SPECTRUMDATA,
    FMOD_DSP_FFT_DOMINANT_FREQ
} FMOD_DSP_FFT;

#define FMOD_DSP_LOUDNESS_METER_HISTOGRAM_SAMPLES 66

typedef enum
{
    FMOD_DSP_LOUDNESS_METER_STATE,
    FMOD_DSP_LOUDNESS_METER_WEIGHTING,
    FMOD_DSP_LOUDNESS_METER_INFO
} FMOD_DSP_LOUDNESS_METER;


typedef enum
{
    FMOD_DSP_LOUDNESS_METER_STATE_RESET_INTEGRATED = -3,
    FMOD_DSP_LOUDNESS_METER_STATE_RESET_MAXPEAK = -2,
    FMOD_DSP_LOUDNESS_METER_STATE_RESET_ALL = -1,
    FMOD_DSP_LOUDNESS_METER_STATE_PAUSED = 0,
    FMOD_DSP_LOUDNESS_METER_STATE_ANALYZING = 1
} FMOD_DSP_LOUDNESS_METER_STATE_TYPE;

typedef struct FMOD_DSP_LOUDNESS_METER_INFO_TYPE
{
    float momentaryloudness;
    float shorttermloudness;
    float integratedloudness;
    float loudness10thpercentile;
    float loudness95thpercentile;
    float loudnesshistogram[FMOD_DSP_LOUDNESS_METER_HISTOGRAM_SAMPLES];
    float maxtruepeak;
    float maxmomentaryloudness;
} FMOD_DSP_LOUDNESS_METER_INFO_TYPE;

typedef struct FMOD_DSP_LOUDNESS_METER_WEIGHTING_TYPE
{
    float channelweight[32];
} FMOD_DSP_LOUDNESS_METER_WEIGHTING_TYPE;


typedef enum
{
    FMOD_DSP_ENVELOPEFOLLOWER_ATTACK,
    FMOD_DSP_ENVELOPEFOLLOWER_RELEASE,
    FMOD_DSP_ENVELOPEFOLLOWER_ENVELOPE,
    FMOD_DSP_ENVELOPEFOLLOWER_USESIDECHAIN
} FMOD_DSP_ENVELOPEFOLLOWER;

typedef enum
{
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_IR,
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_WET,
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_DRY,
    FMOD_DSP_CONVOLUTION_REVERB_PARAM_LINKED
} FMOD_DSP_CONVOLUTION_REVERB;

typedef enum
{
    FMOD_DSP_CHANNELMIX_OUTPUT_DEFAULT,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLMONO,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLSTEREO,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLQUAD,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALL5POINT1,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALL7POINT1,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALLLFE,
    FMOD_DSP_CHANNELMIX_OUTPUT_ALL7POINT1POINT4
} FMOD_DSP_CHANNELMIX_OUTPUT;

typedef enum
{
    FMOD_DSP_CHANNELMIX_OUTPUTGROUPING,
    FMOD_DSP_CHANNELMIX_GAIN_CH0,
    FMOD_DSP_CHANNELMIX_GAIN_CH1,
    FMOD_DSP_CHANNELMIX_GAIN_CH2,
    FMOD_DSP_CHANNELMIX_GAIN_CH3,
    FMOD_DSP_CHANNELMIX_GAIN_CH4,
    FMOD_DSP_CHANNELMIX_GAIN_CH5,
    FMOD_DSP_CHANNELMIX_GAIN_CH6,
    FMOD_DSP_CHANNELMIX_GAIN_CH7,
    FMOD_DSP_CHANNELMIX_GAIN_CH8,
    FMOD_DSP_CHANNELMIX_GAIN_CH9,
    FMOD_DSP_CHANNELMIX_GAIN_CH10,
    FMOD_DSP_CHANNELMIX_GAIN_CH11,
    FMOD_DSP_CHANNELMIX_GAIN_CH12,
    FMOD_DSP_CHANNELMIX_GAIN_CH13,
    FMOD_DSP_CHANNELMIX_GAIN_CH14,
    FMOD_DSP_CHANNELMIX_GAIN_CH15,
    FMOD_DSP_CHANNELMIX_GAIN_CH16,
    FMOD_DSP_CHANNELMIX_GAIN_CH17,
    FMOD_DSP_CHANNELMIX_GAIN_CH18,
    FMOD_DSP_CHANNELMIX_GAIN_CH19,
    FMOD_DSP_CHANNELMIX_GAIN_CH20,
    FMOD_DSP_CHANNELMIX_GAIN_CH21,
    FMOD_DSP_CHANNELMIX_GAIN_CH22,
    FMOD_DSP_CHANNELMIX_GAIN_CH23,
    FMOD_DSP_CHANNELMIX_GAIN_CH24,
    FMOD_DSP_CHANNELMIX_GAIN_CH25,
    FMOD_DSP_CHANNELMIX_GAIN_CH26,
    FMOD_DSP_CHANNELMIX_GAIN_CH27,
    FMOD_DSP_CHANNELMIX_GAIN_CH28,
    FMOD_DSP_CHANNELMIX_GAIN_CH29,
    FMOD_DSP_CHANNELMIX_GAIN_CH30,
    FMOD_DSP_CHANNELMIX_GAIN_CH31,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH0,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH1,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH2,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH3,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH4,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH5,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH6,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH7,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH8,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH9,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH10,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH11,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH12,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH13,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH14,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH15,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH16,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH17,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH18,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH19,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH20,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH21,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH22,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH23,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH24,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH25,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH26,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH27,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH28,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH29,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH30,
    FMOD_DSP_CHANNELMIX_OUTPUT_CH31
} FMOD_DSP_CHANNELMIX;

typedef enum
{
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_AUTO = -1,
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_MONO = 0,
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_STEREO,
    FMOD_DSP_TRANSCEIVER_SPEAKERMODE_SURROUND,
} FMOD_DSP_TRANSCEIVER_SPEAKERMODE;


typedef enum
{
    FMOD_DSP_TRANSCEIVER_TRANSMIT,
    FMOD_DSP_TRANSCEIVER_GAIN,
    FMOD_DSP_TRANSCEIVER_CHANNEL,
    FMOD_DSP_TRANSCEIVER_TRANSMITSPEAKERMODE
} FMOD_DSP_TRANSCEIVER;


typedef enum
{
    FMOD_DSP_OBJECTPAN_3D_POSITION,
    FMOD_DSP_OBJECTPAN_3D_ROLLOFF,
    FMOD_DSP_OBJECTPAN_3D_MIN_DISTANCE,
    FMOD_DSP_OBJECTPAN_3D_MAX_DISTANCE,
    FMOD_DSP_OBJECTPAN_3D_EXTENT_MODE,
    FMOD_DSP_OBJECTPAN_3D_SOUND_SIZE,
    FMOD_DSP_OBJECTPAN_3D_MIN_EXTENT,
    FMOD_DSP_OBJECTPAN_OVERALL_GAIN,
    FMOD_DSP_OBJECTPAN_OUTPUTGAIN,
    FMOD_DSP_OBJECTPAN_ATTENUATION_RANGE,
    FMOD_DSP_OBJECTPAN_OVERRIDE_RANGE
} FMOD_DSP_OBJECTPAN;

typedef struct FMOD_DSP_STATE        FMOD_DSP_STATE;
typedef struct FMOD_DSP_BUFFER_ARRAY FMOD_DSP_BUFFER_ARRAY;
typedef struct FMOD_COMPLEX          FMOD_COMPLEX;

/*
    DSP Constants
*/
#define FMOD_PLUGIN_SDK_VERSION             110
#define FMOD_DSP_GETPARAM_VALUESTR_LENGTH   32

typedef enum
{
    FMOD_DSP_PROCESS_PERFORM,
    FMOD_DSP_PROCESS_QUERY
} FMOD_DSP_PROCESS_OPERATION;

typedef enum FMOD_DSP_PAN_SURROUND_FLAGS
{
    FMOD_DSP_PAN_SURROUND_DEFAULT = 0,
    FMOD_DSP_PAN_SURROUND_ROTATION_NOT_BIASED = 1,

    FMOD_DSP_PAN_SURROUND_FLAGS_FORCEINT = 65536
} FMOD_DSP_PAN_SURROUND_FLAGS;

typedef enum
{
    FMOD_DSP_PARAMETER_TYPE_FLOAT,
    FMOD_DSP_PARAMETER_TYPE_INT,
    FMOD_DSP_PARAMETER_TYPE_BOOL,
    FMOD_DSP_PARAMETER_TYPE_DATA,

    FMOD_DSP_PARAMETER_TYPE_MAX,
    FMOD_DSP_PARAMETER_TYPE_FORCEINT = 65536
} FMOD_DSP_PARAMETER_TYPE;

typedef enum
{
    FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE_LINEAR,
    FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE_AUTO,
    FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE_PIECEWISE_LINEAR,

    FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE_FORCEINT = 65536
} FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE;

typedef enum
{
    FMOD_DSP_PARAMETER_DATA_TYPE_USER = 0,
    FMOD_DSP_PARAMETER_DATA_TYPE_OVERALLGAIN = -1,
    FMOD_DSP_PARAMETER_DATA_TYPE_3DATTRIBUTES = -2,
    FMOD_DSP_PARAMETER_DATA_TYPE_SIDECHAIN = -3,
    FMOD_DSP_PARAMETER_DATA_TYPE_FFT = -4,
    FMOD_DSP_PARAMETER_DATA_TYPE_3DATTRIBUTES_MULTI = -5,
    FMOD_DSP_PARAMETER_DATA_TYPE_ATTENUATION_RANGE = -6,
} FMOD_DSP_PARAMETER_DATA_TYPE;

/*
    DSP Callbacks
*/
typedef FMOD_RESULT (F_CALL *FMOD_DSP_CREATE_CALLBACK)                    (FMOD_DSP_STATE *dsp_state);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_RELEASE_CALLBACK)                   (FMOD_DSP_STATE *dsp_state);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_RESET_CALLBACK)                     (FMOD_DSP_STATE *dsp_state);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_READ_CALLBACK)                      (FMOD_DSP_STATE *dsp_state, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int *outchannels);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PROCESS_CALLBACK)                   (FMOD_DSP_STATE *dsp_state, unsigned int length, const FMOD_DSP_BUFFER_ARRAY *inbufferarray, FMOD_DSP_BUFFER_ARRAY *outbufferarray, FMOD_BOOL inputsidle, FMOD_DSP_PROCESS_OPERATION op);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SETPOSITION_CALLBACK)               (FMOD_DSP_STATE *dsp_state, unsigned int pos);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SHOULDIPROCESS_CALLBACK)            (FMOD_DSP_STATE *dsp_state, FMOD_BOOL inputsidle, unsigned int length, FMOD_CHANNELMASK inmask, int inchannels, FMOD_SPEAKERMODE speakermode);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SETPARAM_FLOAT_CALLBACK)            (FMOD_DSP_STATE *dsp_state, int index, float value);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SETPARAM_INT_CALLBACK)              (FMOD_DSP_STATE *dsp_state, int index, int value);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SETPARAM_BOOL_CALLBACK)             (FMOD_DSP_STATE *dsp_state, int index, FMOD_BOOL value);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SETPARAM_DATA_CALLBACK)             (FMOD_DSP_STATE *dsp_state, int index, void *data, unsigned int length);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETPARAM_FLOAT_CALLBACK)            (FMOD_DSP_STATE *dsp_state, int index, float *value, char *valuestr);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETPARAM_INT_CALLBACK)              (FMOD_DSP_STATE *dsp_state, int index, int *value, char *valuestr);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETPARAM_BOOL_CALLBACK)             (FMOD_DSP_STATE *dsp_state, int index, FMOD_BOOL *value, char *valuestr);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETPARAM_DATA_CALLBACK)             (FMOD_DSP_STATE *dsp_state, int index, void **data, unsigned int *length, char *valuestr);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SYSTEM_REGISTER_CALLBACK)           (FMOD_DSP_STATE *dsp_state);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SYSTEM_DEREGISTER_CALLBACK)         (FMOD_DSP_STATE *dsp_state);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_SYSTEM_MIX_CALLBACK)                (FMOD_DSP_STATE *dsp_state, int stage);

/*
    DSP Functions
*/
typedef void *      (F_CALL *FMOD_DSP_ALLOC_FUNC)                         (unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void *      (F_CALL *FMOD_DSP_REALLOC_FUNC)                       (void *ptr, unsigned int size, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void        (F_CALL *FMOD_DSP_FREE_FUNC)                          (void *ptr, FMOD_MEMORY_TYPE type, const char *sourcestr);
typedef void        (F_CALL *FMOD_DSP_LOG_FUNC)                           (FMOD_DEBUG_FLAGS level, const char *file, int line, const char *function, const char *string, ...);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETSAMPLERATE_FUNC)                 (FMOD_DSP_STATE *dsp_state, int *rate);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETBLOCKSIZE_FUNC)                  (FMOD_DSP_STATE *dsp_state, unsigned int *blocksize);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETSPEAKERMODE_FUNC)                (FMOD_DSP_STATE *dsp_state, FMOD_SPEAKERMODE *speakermode_mixer, FMOD_SPEAKERMODE *speakermode_output);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETCLOCK_FUNC)                      (FMOD_DSP_STATE *dsp_state, unsigned long long *clock, unsigned int *offset, unsigned int *length);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETLISTENERATTRIBUTES_FUNC)         (FMOD_DSP_STATE *dsp_state, int *numlisteners, FMOD_3D_ATTRIBUTES *attributes);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_GETUSERDATA_FUNC)                   (FMOD_DSP_STATE *dsp_state, void **userdata);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_DFT_FFTREAL_FUNC)                   (FMOD_DSP_STATE *dsp_state, int size, const float *signal, FMOD_COMPLEX* dft, const float *window, int signalhop);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_DFT_IFFTREAL_FUNC)                  (FMOD_DSP_STATE *dsp_state, int size, const FMOD_COMPLEX *dft, float* signal, const float *window, int signalhop);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PAN_SUMMONOMATRIX_FUNC)             (FMOD_DSP_STATE *dsp_state, FMOD_SPEAKERMODE sourceSpeakerMode, float lowFrequencyGain, float overallGain, float *matrix);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PAN_SUMSTEREOMATRIX_FUNC)           (FMOD_DSP_STATE *dsp_state, FMOD_SPEAKERMODE sourceSpeakerMode, float pan, float lowFrequencyGain, float overallGain, int matrixHop, float *matrix);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PAN_SUMSURROUNDMATRIX_FUNC)         (FMOD_DSP_STATE *dsp_state, FMOD_SPEAKERMODE sourceSpeakerMode, FMOD_SPEAKERMODE targetSpeakerMode, float direction, float extent, float rotation, float lowFrequencyGain, float overallGain, int matrixHop, float *matrix, FMOD_DSP_PAN_SURROUND_FLAGS flags);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PAN_SUMMONOTOSURROUNDMATRIX_FUNC)   (FMOD_DSP_STATE *dsp_state, FMOD_SPEAKERMODE targetSpeakerMode, float direction, float extent, float lowFrequencyGain, float overallGain, int matrixHop, float *matrix);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PAN_SUMSTEREOTOSURROUNDMATRIX_FUNC) (FMOD_DSP_STATE *dsp_state, FMOD_SPEAKERMODE targetSpeakerMode, float direction, float extent, float rotation, float lowFrequencyGain, float overallGain, int matrixHop, float *matrix);
typedef FMOD_RESULT (F_CALL *FMOD_DSP_PAN_GETROLLOFFGAIN_FUNC)            (FMOD_DSP_STATE *dsp_state, FMOD_DSP_PAN_3D_ROLLOFF_TYPE rolloff, float distance, float mindistance, float maxdistance, float *gain);

/*
    DSP Structures
*/
struct FMOD_DSP_BUFFER_ARRAY
{
    int                numbuffers;
    int               *buffernumchannels;
    FMOD_CHANNELMASK  *bufferchannelmask;
    float            **buffers;
    FMOD_SPEAKERMODE   speakermode;
};

struct FMOD_COMPLEX
{
    float real;
    float imag;
};

typedef struct FMOD_DSP_PARAMETER_FLOAT_MAPPING_PIECEWISE_LINEAR
{
    int     numpoints;
    float  *pointparamvalues;
    float  *pointpositions;
} FMOD_DSP_PARAMETER_FLOAT_MAPPING_PIECEWISE_LINEAR;

typedef struct FMOD_DSP_PARAMETER_FLOAT_MAPPING
{
    FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE               type;
    FMOD_DSP_PARAMETER_FLOAT_MAPPING_PIECEWISE_LINEAR   piecewiselinearmapping;
} FMOD_DSP_PARAMETER_FLOAT_MAPPING;

typedef struct FMOD_DSP_PARAMETER_DESC_FLOAT
{
    float                               min;
    float                               max;
    float                               defaultval;
    FMOD_DSP_PARAMETER_FLOAT_MAPPING    mapping;
} FMOD_DSP_PARAMETER_DESC_FLOAT;

typedef struct FMOD_DSP_PARAMETER_DESC_INT
{
    int                 min;
    int                 max;
    int                 defaultval;
    FMOD_BOOL           goestoinf;
    const char* const*  valuenames;
} FMOD_DSP_PARAMETER_DESC_INT;

typedef struct FMOD_DSP_PARAMETER_DESC_BOOL
{
    FMOD_BOOL           defaultval;
    const char* const*  valuenames;
} FMOD_DSP_PARAMETER_DESC_BOOL;

typedef struct FMOD_DSP_PARAMETER_DESC_DATA
{
    int datatype;
} FMOD_DSP_PARAMETER_DESC_DATA;

typedef struct FMOD_DSP_PARAMETER_DESC
{
    FMOD_DSP_PARAMETER_TYPE type;
    char                    name[16];
    char                    label[16];
    const char             *description;

    union
    {
        FMOD_DSP_PARAMETER_DESC_FLOAT   floatdesc;
        FMOD_DSP_PARAMETER_DESC_INT     intdesc;
        FMOD_DSP_PARAMETER_DESC_BOOL    booldesc;
        FMOD_DSP_PARAMETER_DESC_DATA    datadesc;
    };
} FMOD_DSP_PARAMETER_DESC;

typedef struct FMOD_DSP_PARAMETER_OVERALLGAIN
{
    float linear_gain;
    float linear_gain_additive;
} FMOD_DSP_PARAMETER_OVERALLGAIN;

typedef struct FMOD_DSP_PARAMETER_3DATTRIBUTES
{
    FMOD_3D_ATTRIBUTES relative;
    FMOD_3D_ATTRIBUTES absolute;
} FMOD_DSP_PARAMETER_3DATTRIBUTES;

typedef struct FMOD_DSP_PARAMETER_3DATTRIBUTES_MULTI
{
    int                numlisteners;
    FMOD_3D_ATTRIBUTES relative[FMOD_MAX_LISTENERS];
    float              weight[FMOD_MAX_LISTENERS];
    FMOD_3D_ATTRIBUTES absolute;
} FMOD_DSP_PARAMETER_3DATTRIBUTES_MULTI;

typedef struct FMOD_DSP_PARAMETER_ATTENUATION_RANGE
{
    float min;
    float max;
} FMOD_DSP_PARAMETER_ATTENUATION_RANGE;

typedef struct FMOD_DSP_PARAMETER_SIDECHAIN
{
    FMOD_BOOL sidechainenable;
} FMOD_DSP_PARAMETER_SIDECHAIN;

typedef struct FMOD_DSP_PARAMETER_FFT
{
    int     length;
    int     numchannels;
    float  *spectrum[32];
} FMOD_DSP_PARAMETER_FFT;

typedef struct FMOD_DSP_DESCRIPTION
{
    unsigned int                        pluginsdkversion;
    char                                name[32];
    unsigned int                        version;
    int                                 numinputbuffers;
    int                                 numoutputbuffers;
    FMOD_DSP_CREATE_CALLBACK            create;
    FMOD_DSP_RELEASE_CALLBACK           release;
    FMOD_DSP_RESET_CALLBACK             reset;
    FMOD_DSP_READ_CALLBACK              read;
    FMOD_DSP_PROCESS_CALLBACK           process;
    FMOD_DSP_SETPOSITION_CALLBACK       setposition;

    int                                 numparameters;
    FMOD_DSP_PARAMETER_DESC           **paramdesc;
    FMOD_DSP_SETPARAM_FLOAT_CALLBACK    setparameterfloat;
    FMOD_DSP_SETPARAM_INT_CALLBACK      setparameterint;
    FMOD_DSP_SETPARAM_BOOL_CALLBACK     setparameterbool;
    FMOD_DSP_SETPARAM_DATA_CALLBACK     setparameterdata;
    FMOD_DSP_GETPARAM_FLOAT_CALLBACK    getparameterfloat;
    FMOD_DSP_GETPARAM_INT_CALLBACK      getparameterint;
    FMOD_DSP_GETPARAM_BOOL_CALLBACK     getparameterbool;
    FMOD_DSP_GETPARAM_DATA_CALLBACK     getparameterdata;
    FMOD_DSP_SHOULDIPROCESS_CALLBACK    shouldiprocess;
    void                               *userdata;

    FMOD_DSP_SYSTEM_REGISTER_CALLBACK   sys_register;
    FMOD_DSP_SYSTEM_DEREGISTER_CALLBACK sys_deregister;
    FMOD_DSP_SYSTEM_MIX_CALLBACK        sys_mix;

} FMOD_DSP_DESCRIPTION;

typedef struct FMOD_DSP_STATE_DFT_FUNCTIONS
{
    FMOD_DSP_DFT_FFTREAL_FUNC  fftreal;
    FMOD_DSP_DFT_IFFTREAL_FUNC inversefftreal;
} FMOD_DSP_STATE_DFT_FUNCTIONS;

typedef struct FMOD_DSP_STATE_PAN_FUNCTIONS
{
    FMOD_DSP_PAN_SUMMONOMATRIX_FUNC             summonomatrix;
    FMOD_DSP_PAN_SUMSTEREOMATRIX_FUNC           sumstereomatrix;
    FMOD_DSP_PAN_SUMSURROUNDMATRIX_FUNC         sumsurroundmatrix;
    FMOD_DSP_PAN_SUMMONOTOSURROUNDMATRIX_FUNC   summonotosurroundmatrix;
    FMOD_DSP_PAN_SUMSTEREOTOSURROUNDMATRIX_FUNC sumstereotosurroundmatrix;
    FMOD_DSP_PAN_GETROLLOFFGAIN_FUNC            getrolloffgain;
} FMOD_DSP_STATE_PAN_FUNCTIONS;

typedef struct FMOD_DSP_STATE_FUNCTIONS
{
    FMOD_DSP_ALLOC_FUNC                 alloc;
    FMOD_DSP_REALLOC_FUNC               realloc;
    FMOD_DSP_FREE_FUNC                  free;
    FMOD_DSP_GETSAMPLERATE_FUNC         getsamplerate;
    FMOD_DSP_GETBLOCKSIZE_FUNC          getblocksize;
    FMOD_DSP_STATE_DFT_FUNCTIONS       *dft;
    FMOD_DSP_STATE_PAN_FUNCTIONS       *pan;
    FMOD_DSP_GETSPEAKERMODE_FUNC        getspeakermode;
    FMOD_DSP_GETCLOCK_FUNC              getclock;
    FMOD_DSP_GETLISTENERATTRIBUTES_FUNC getlistenerattributes;
    FMOD_DSP_LOG_FUNC                   log;
    FMOD_DSP_GETUSERDATA_FUNC           getuserdata;
} FMOD_DSP_STATE_FUNCTIONS;

struct FMOD_DSP_STATE
{
    void                     *instance;
    void                     *plugindata;
    FMOD_CHANNELMASK          channelmask;
    FMOD_SPEAKERMODE          source_speakermode;
    float                    *sidechaindata;
    int                       sidechainchannels;
    FMOD_DSP_STATE_FUNCTIONS *functions;
    int                       systemobject;
};

typedef struct FMOD_DSP_METERING_INFO
{
    int   numsamples;
    float peaklevel[32];
    float rmslevel[32];
    short numchannels;
} FMOD_DSP_METERING_INFO;

/*
    DSP Macros
*/
#define FMOD_DSP_INIT_PARAMDESC_FLOAT(_paramstruct, _name, _label, _description, _min, _max, _defaultval) \
    memset(&(_paramstruct), 0, sizeof(_paramstruct)); \
    (_paramstruct).type         = FMOD_DSP_PARAMETER_TYPE_FLOAT; \
    strncpy((_paramstruct).name,  _name,  15); \
    strncpy((_paramstruct).label, _label, 15); \
    (_paramstruct).description  = _description; \
    (_paramstruct).floatdesc.min          = _min; \
    (_paramstruct).floatdesc.max          = _max; \
    (_paramstruct).floatdesc.defaultval   = _defaultval; \
    (_paramstruct).floatdesc.mapping.type = FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE_AUTO;

#define FMOD_DSP_INIT_PARAMDESC_FLOAT_WITH_MAPPING(_paramstruct, _name, _label, _description, _defaultval, _values, _positions); \
    memset(&(_paramstruct), 0, sizeof(_paramstruct)); \
    (_paramstruct).type         = FMOD_DSP_PARAMETER_TYPE_FLOAT; \
    strncpy((_paramstruct).name,  _name , 15); \
    strncpy((_paramstruct).label, _label, 15); \
    (_paramstruct).description  = _description; \
    (_paramstruct).floatdesc.min          = _values[0]; \
    (_paramstruct).floatdesc.max          = _values[sizeof(_values) / sizeof(float) - 1]; \
    (_paramstruct).floatdesc.defaultval   = _defaultval; \
    (_paramstruct).floatdesc.mapping.type = FMOD_DSP_PARAMETER_FLOAT_MAPPING_TYPE_PIECEWISE_LINEAR; \
    (_paramstruct).floatdesc.mapping.piecewiselinearmapping.numpoints = sizeof(_values) / sizeof(float); \
    (_paramstruct).floatdesc.mapping.piecewiselinearmapping.pointparamvalues = _values; \
    (_paramstruct).floatdesc.mapping.piecewiselinearmapping.pointpositions = _positions;

#define FMOD_DSP_INIT_PARAMDESC_INT(_paramstruct, _name, _label, _description, _min, _max, _defaultval, _goestoinf, _valuenames) \
    memset(&(_paramstruct), 0, sizeof(_paramstruct)); \
    (_paramstruct).type         = FMOD_DSP_PARAMETER_TYPE_INT; \
    strncpy((_paramstruct).name,  _name , 15); \
    strncpy((_paramstruct).label, _label, 15); \
    (_paramstruct).description  = _description; \
    (_paramstruct).intdesc.min          = _min; \
    (_paramstruct).intdesc.max          = _max; \
    (_paramstruct).intdesc.defaultval   = _defaultval; \
    (_paramstruct).intdesc.goestoinf    = _goestoinf; \
    (_paramstruct).intdesc.valuenames   = _valuenames;

#define FMOD_DSP_INIT_PARAMDESC_INT_ENUMERATED(_paramstruct, _name, _label, _description, _defaultval, _valuenames) \
    memset(&(_paramstruct), 0, sizeof(_paramstruct)); \
    (_paramstruct).type         = FMOD_DSP_PARAMETER_TYPE_INT; \
    strncpy((_paramstruct).name,  _name , 15); \
    strncpy((_paramstruct).label, _label, 15); \
    (_paramstruct).description  = _description; \
    (_paramstruct).intdesc.min          = 0; \
    (_paramstruct).intdesc.max          = sizeof(_valuenames) / sizeof(char*) - 1; \
    (_paramstruct).intdesc.defaultval   = _defaultval; \
    (_paramstruct).intdesc.goestoinf    = false; \
    (_paramstruct).intdesc.valuenames   = _valuenames;

#define FMOD_DSP_INIT_PARAMDESC_BOOL(_paramstruct, _name, _label, _description, _defaultval, _valuenames) \
    memset(&(_paramstruct), 0, sizeof(_paramstruct)); \
    (_paramstruct).type         = FMOD_DSP_PARAMETER_TYPE_BOOL; \
    strncpy((_paramstruct).name,  _name , 15); \
    strncpy((_paramstruct).label, _label, 15); \
    (_paramstruct).description  = _description; \
    (_paramstruct).booldesc.defaultval   = _defaultval; \
    (_paramstruct).booldesc.valuenames   = _valuenames;

#define FMOD_DSP_INIT_PARAMDESC_DATA(_paramstruct, _name, _label, _description, _datatype) \
    memset(&(_paramstruct), 0, sizeof(_paramstruct)); \
    (_paramstruct).type         = FMOD_DSP_PARAMETER_TYPE_DATA; \
    strncpy((_paramstruct).name,  _name , 15); \
    strncpy((_paramstruct).label, _label, 15); \
    (_paramstruct).description  = _description; \
    (_paramstruct).datadesc.datatype     = _datatype;

#define FMOD_DSP_ALLOC(_state, _size) \
    (_state)->functions->alloc(_size, FMOD_MEMORY_NORMAL, __FILE__)
#define FMOD_DSP_REALLOC(_state, _ptr, _size) \
    (_state)->functions->realloc(_ptr, _size, FMOD_MEMORY_NORMAL, __FILE__)
#define FMOD_DSP_FREE(_state, _ptr) \
    (_state)->functions->free(_ptr, FMOD_MEMORY_NORMAL, __FILE__)
#define FMOD_DSP_LOG(_state, _level, _location, _format, ...) \
    (_state)->functions->log(_level, __FILE__, __LINE__, _location, _format, __VA_ARGS__)
#define FMOD_DSP_GETSAMPLERATE(_state, _rate) \
    (_state)->functions->getsamplerate(_state, _rate)
#define FMOD_DSP_GETBLOCKSIZE(_state, _blocksize) \
    (_state)->functions->getblocksize(_state, _blocksize)
#define FMOD_DSP_GETSPEAKERMODE(_state, _speakermodemix, _speakermodeout) \
    (_state)->functions->getspeakermode(_state, _speakermodemix, _speakermodeout)
#define FMOD_DSP_GETCLOCK(_state, _clock, _offset, _length) \
    (_state)->functions->getclock(_state, _clock, _offset, _length)
#define FMOD_DSP_GETLISTENERATTRIBUTES(_state, _numlisteners, _attributes) \
    (_state)->functions->getlistenerattributes(_state, _numlisteners, _attributes)
#define FMOD_DSP_GETUSERDATA(_state, _userdata) \
    (_state)->functions->getuserdata(_state, _userdata)
#define FMOD_DSP_DFT_FFTREAL(_state, _size, _signal, _dft, _window, _signalhop) \
    (_state)->functions->dft->fftreal(_state, _size, _signal, _dft, _window, _signalhop)
#define FMOD_DSP_DFT_IFFTREAL(_state, _size, _dft, _signal, _window, _signalhop) \
    (_state)->functions->dft->inversefftreal(_state, _size, _dft, _signal, _window, _signalhop)
#define FMOD_DSP_PAN_SUMMONOMATRIX(_state, _sourcespeakermode, _lowfrequencygain, _overallgain, _matrix) \
    (_state)->functions->pan->summonomatrix(_state, _sourcespeakermode, _lowfrequencygain, _overallgain, _matrix)
#define FMOD_DSP_PAN_SUMSTEREOMATRIX(_state, _sourcespeakermode, _pan, _lowfrequencygain, _overallgain, _matrixhop, _matrix) \
    (_state)->functions->pan->sumstereomatrix(_state, _sourcespeakermode, _pan, _lowfrequencygain, _overallgain, _matrixhop, _matrix)
#define FMOD_DSP_PAN_SUMSURROUNDMATRIX(_state, _sourcespeakermode, _targetspeakermode, _direction, _extent, _rotation, _lowfrequencygain, _overallgain, _matrixhop, _matrix, _flags) \
    (_state)->functions->pan->sumsurroundmatrix(_state, _sourcespeakermode, _targetspeakermode, _direction, _extent, _rotation, _lowfrequencygain, _overallgain, _matrixhop, _matrix, _flags)
#define FMOD_DSP_PAN_SUMMONOTOSURROUNDMATRIX(_state, _targetspeakermode, _direction, _extent, _lowfrequencygain, _overallgain, _matrixhop, _matrix) \
    (_state)->functions->pan->summonotosurroundmatrix(_state, _targetspeakermode, _direction, _extent, _lowfrequencygain, _overallgain, _matrixhop, _matrix)
#define FMOD_DSP_PAN_SUMSTEREOTOSURROUNDMATRIX(_state, _targetspeakermode, _direction, _extent, _rotation, _lowfrequencygain, _overallgain, matrixhop, _matrix) \
    (_state)->functions->pan->sumstereotosurroundmatrix(_state, _targetspeakermode, _direction, _extent, _rotation, _lowfrequencygain, _overallgain, matrixhop, _matrix)
#define FMOD_DSP_PAN_GETROLLOFFGAIN(_state, _rolloff, _distance, _mindistance, _maxdistance, _gain) \
    (_state)->functions->pan->getrolloffgain(_state, _rolloff, _distance, _mindistance, _maxdistance, _gain)

/*
    FMOD global system functions (optional).
*/
FMOD_RESULT F_API FMOD_Memory_Initialize           (void *poolmem, int poollen, FMOD_MEMORY_ALLOC_CALLBACK useralloc, FMOD_MEMORY_REALLOC_CALLBACK userrealloc, FMOD_MEMORY_FREE_CALLBACK userfree, FMOD_MEMORY_TYPE memtypeflags);
FMOD_RESULT F_API FMOD_Memory_GetStats             (int *currentalloced, int *maxalloced, FMOD_BOOL blocking);
FMOD_RESULT F_API FMOD_Debug_Initialize            (FMOD_DEBUG_FLAGS flags, FMOD_DEBUG_MODE mode, FMOD_DEBUG_CALLBACK callback, const char *filename);
FMOD_RESULT F_API FMOD_File_SetDiskBusy            (int busy);
FMOD_RESULT F_API FMOD_File_GetDiskBusy            (int *busy);
FMOD_RESULT F_API FMOD_Thread_SetAttributes        (FMOD_THREAD_TYPE type, FMOD_THREAD_AFFINITY affinity, FMOD_THREAD_PRIORITY priority, FMOD_THREAD_STACK_SIZE stacksize);

/*
    FMOD System factory functions.  Use this to create an FMOD System Instance.  below you will see FMOD_System_Init/Close to get started.
*/
FMOD_RESULT F_API FMOD_System_Create               (FMOD_SYSTEM **system, unsigned int headerversion); 
FMOD_RESULT F_API FMOD_System_Release              (FMOD_SYSTEM *system); 

/*
    'System' API
*/

/* Setup functions. */
FMOD_RESULT F_API FMOD_System_SetOutput                 (FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output);
FMOD_RESULT F_API FMOD_System_GetOutput                 (FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output);
FMOD_RESULT F_API FMOD_System_GetNumDrivers             (FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT F_API FMOD_System_GetDriverInfo             (FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid, int *systemrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels);
FMOD_RESULT F_API FMOD_System_SetDriver                 (FMOD_SYSTEM *system, int driver);
FMOD_RESULT F_API FMOD_System_GetDriver                 (FMOD_SYSTEM *system, int *driver);
FMOD_RESULT F_API FMOD_System_SetSoftwareChannels       (FMOD_SYSTEM *system, int numsoftwarechannels);
FMOD_RESULT F_API FMOD_System_GetSoftwareChannels       (FMOD_SYSTEM *system, int *numsoftwarechannels);
FMOD_RESULT F_API FMOD_System_SetSoftwareFormat         (FMOD_SYSTEM *system, int samplerate, FMOD_SPEAKERMODE speakermode, int numrawspeakers);
FMOD_RESULT F_API FMOD_System_GetSoftwareFormat         (FMOD_SYSTEM *system, int *samplerate, FMOD_SPEAKERMODE *speakermode, int *numrawspeakers);
FMOD_RESULT F_API FMOD_System_SetDSPBufferSize          (FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers);
FMOD_RESULT F_API FMOD_System_GetDSPBufferSize          (FMOD_SYSTEM *system, unsigned int *bufferlength, int *numbuffers);
FMOD_RESULT F_API FMOD_System_SetFileSystem             (FMOD_SYSTEM *system, FMOD_FILE_OPEN_CALLBACK useropen, FMOD_FILE_CLOSE_CALLBACK userclose, FMOD_FILE_READ_CALLBACK userread, FMOD_FILE_SEEK_CALLBACK userseek, FMOD_FILE_ASYNCREAD_CALLBACK userasyncread, FMOD_FILE_ASYNCCANCEL_CALLBACK userasynccancel, int blockalign);
FMOD_RESULT F_API FMOD_System_AttachFileSystem          (FMOD_SYSTEM *system, FMOD_FILE_OPEN_CALLBACK useropen, FMOD_FILE_CLOSE_CALLBACK userclose, FMOD_FILE_READ_CALLBACK userread, FMOD_FILE_SEEK_CALLBACK userseek);
FMOD_RESULT F_API FMOD_System_SetAdvancedSettings       (FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT F_API FMOD_System_GetAdvancedSettings       (FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT F_API FMOD_System_SetCallback               (FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK callback, FMOD_SYSTEM_CALLBACK_TYPE callbackmask);

/* Plug-in support. */
FMOD_RESULT F_API FMOD_System_SetPluginPath             (FMOD_SYSTEM *system, const char *path);
FMOD_RESULT F_API FMOD_System_LoadPlugin                (FMOD_SYSTEM *system, const char *filename, unsigned int *handle, unsigned int priority);
FMOD_RESULT F_API FMOD_System_UnloadPlugin              (FMOD_SYSTEM *system, unsigned int handle);
FMOD_RESULT F_API FMOD_System_GetNumNestedPlugins       (FMOD_SYSTEM *system, unsigned int handle, int *count);
FMOD_RESULT F_API FMOD_System_GetNestedPlugin           (FMOD_SYSTEM *system, unsigned int handle, int index, unsigned int *nestedhandle);
FMOD_RESULT F_API FMOD_System_GetNumPlugins             (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int *numplugins);
FMOD_RESULT F_API FMOD_System_GetPluginHandle           (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle);
FMOD_RESULT F_API FMOD_System_GetPluginInfo             (FMOD_SYSTEM *system, unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version);
FMOD_RESULT F_API FMOD_System_SetOutputByPlugin         (FMOD_SYSTEM *system, unsigned int handle);
FMOD_RESULT F_API FMOD_System_GetOutputByPlugin         (FMOD_SYSTEM *system, unsigned int *handle);
FMOD_RESULT F_API FMOD_System_CreateDSPByPlugin         (FMOD_SYSTEM *system, unsigned int handle, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_GetDSPInfoByPlugin        (FMOD_SYSTEM *system, unsigned int handle, const FMOD_DSP_DESCRIPTION **description);
FMOD_RESULT F_API FMOD_System_RegisterCodec             (FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int *handle, unsigned int priority);
FMOD_RESULT F_API FMOD_System_RegisterDSP               (FMOD_SYSTEM *system, const FMOD_DSP_DESCRIPTION *description, unsigned int *handle);

/* Init/Close. */
FMOD_RESULT F_API FMOD_System_Init                      (FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
FMOD_RESULT F_API FMOD_System_Close                     (FMOD_SYSTEM *system);

/* General post-init system functions. */
FMOD_RESULT F_API FMOD_System_Update                    (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_SetSpeakerPosition        (FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float x, float y, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_System_GetSpeakerPosition        (FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float *x, float *y, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_System_SetStreamBufferSize       (FMOD_SYSTEM *system, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
FMOD_RESULT F_API FMOD_System_GetStreamBufferSize       (FMOD_SYSTEM *system, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);
FMOD_RESULT F_API FMOD_System_Set3DSettings             (FMOD_SYSTEM *system, float dopplerscale, float distancefactor, float rolloffscale);
FMOD_RESULT F_API FMOD_System_Get3DSettings             (FMOD_SYSTEM *system, float *dopplerscale, float *distancefactor, float *rolloffscale);
FMOD_RESULT F_API FMOD_System_Set3DNumListeners         (FMOD_SYSTEM *system, int numlisteners);
FMOD_RESULT F_API FMOD_System_Get3DNumListeners         (FMOD_SYSTEM *system, int *numlisteners);
FMOD_RESULT F_API FMOD_System_Set3DListenerAttributes   (FMOD_SYSTEM *system, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_System_Get3DListenerAttributes   (FMOD_SYSTEM *system, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_System_Set3DRolloffCallback      (FMOD_SYSTEM *system, FMOD_3D_ROLLOFF_CALLBACK callback);
FMOD_RESULT F_API FMOD_System_MixerSuspend              (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_MixerResume               (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_GetDefaultMixMatrix       (FMOD_SYSTEM *system, FMOD_SPEAKERMODE sourcespeakermode, FMOD_SPEAKERMODE targetspeakermode, float *matrix, int matrixhop);
FMOD_RESULT F_API FMOD_System_GetSpeakerModeChannels    (FMOD_SYSTEM *system, FMOD_SPEAKERMODE mode, int *channels);

/* System information functions. */
FMOD_RESULT F_API FMOD_System_GetVersion                (FMOD_SYSTEM *system, unsigned int *version);
FMOD_RESULT F_API FMOD_System_GetOutputHandle           (FMOD_SYSTEM *system, void **handle);
FMOD_RESULT F_API FMOD_System_GetChannelsPlaying        (FMOD_SYSTEM *system, int *channels, int *realchannels);
FMOD_RESULT F_API FMOD_System_GetCPUUsage               (FMOD_SYSTEM *system, FMOD_CPU_USAGE *usage);
FMOD_RESULT F_API FMOD_System_GetFileUsage              (FMOD_SYSTEM *system, long long *sampleBytesRead, long long *streamBytesRead, long long *otherBytesRead);

/* Sound/DSP/Channel/FX creation and retrieval. */
FMOD_RESULT F_API FMOD_System_CreateSound               (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_System_CreateStream              (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_System_CreateDSP                 (FMOD_SYSTEM *system, const FMOD_DSP_DESCRIPTION *description, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateDSPByType           (FMOD_SYSTEM *system, FMOD_DSP_TYPE type, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateChannelGroup        (FMOD_SYSTEM *system, const char *name, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_System_CreateSoundGroup          (FMOD_SYSTEM *system, const char *name, FMOD_SOUNDGROUP **soundgroup);
FMOD_RESULT F_API FMOD_System_CreateReverb3D            (FMOD_SYSTEM *system, FMOD_REVERB3D **reverb);
FMOD_RESULT F_API FMOD_System_PlaySound                 (FMOD_SYSTEM *system, FMOD_SOUND *sound, FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_PlayDSP                   (FMOD_SYSTEM *system, FMOD_DSP *dsp, FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_GetChannel                (FMOD_SYSTEM *system, int channelid, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_GetDSPInfoByType          (FMOD_SYSTEM *system, FMOD_DSP_TYPE type, const FMOD_DSP_DESCRIPTION **description);
FMOD_RESULT F_API FMOD_System_GetMasterChannelGroup     (FMOD_SYSTEM *system, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_System_GetMasterSoundGroup       (FMOD_SYSTEM *system, FMOD_SOUNDGROUP **soundgroup);

/* Routing to ports. */
FMOD_RESULT F_API FMOD_System_AttachChannelGroupToPort  (FMOD_SYSTEM *system, FMOD_PORT_TYPE portType, FMOD_PORT_INDEX portIndex, FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL passThru);
FMOD_RESULT F_API FMOD_System_DetachChannelGroupFromPort(FMOD_SYSTEM *system, FMOD_CHANNELGROUP *channelgroup);

/* Reverb API. */
FMOD_RESULT F_API FMOD_System_SetReverbProperties       (FMOD_SYSTEM *system, int instance, const FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT F_API FMOD_System_GetReverbProperties       (FMOD_SYSTEM *system, int instance, FMOD_REVERB_PROPERTIES *prop);

/* System level DSP functionality. */
FMOD_RESULT F_API FMOD_System_LockDSP                   (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_UnlockDSP                 (FMOD_SYSTEM *system);

/* Recording API. */
FMOD_RESULT F_API FMOD_System_GetRecordNumDrivers       (FMOD_SYSTEM *system, int *numdrivers, int *numconnected);
FMOD_RESULT F_API FMOD_System_GetRecordDriverInfo       (FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid, int *systemrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels, FMOD_DRIVER_STATE *state);
FMOD_RESULT F_API FMOD_System_GetRecordPosition         (FMOD_SYSTEM *system, int id, unsigned int *position);
FMOD_RESULT F_API FMOD_System_RecordStart               (FMOD_SYSTEM *system, int id, FMOD_SOUND *sound, FMOD_BOOL loop);
FMOD_RESULT F_API FMOD_System_RecordStop                (FMOD_SYSTEM *system, int id);
FMOD_RESULT F_API FMOD_System_IsRecording               (FMOD_SYSTEM *system, int id, FMOD_BOOL *recording);

/* Geometry API. */
FMOD_RESULT F_API FMOD_System_CreateGeometry            (FMOD_SYSTEM *system, int maxpolygons, int maxvertices, FMOD_GEOMETRY **geometry);
FMOD_RESULT F_API FMOD_System_SetGeometrySettings       (FMOD_SYSTEM *system, float maxworldsize);
FMOD_RESULT F_API FMOD_System_GetGeometrySettings       (FMOD_SYSTEM *system, float *maxworldsize);
FMOD_RESULT F_API FMOD_System_LoadGeometry              (FMOD_SYSTEM *system, const void *data, int datasize, FMOD_GEOMETRY **geometry);
FMOD_RESULT F_API FMOD_System_GetGeometryOcclusion      (FMOD_SYSTEM *system, const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb);

/* Network functions. */
FMOD_RESULT F_API FMOD_System_SetNetworkProxy           (FMOD_SYSTEM *system, const char *proxy);
FMOD_RESULT F_API FMOD_System_GetNetworkProxy           (FMOD_SYSTEM *system, char *proxy, int proxylen);
FMOD_RESULT F_API FMOD_System_SetNetworkTimeout         (FMOD_SYSTEM *system, int timeout);
FMOD_RESULT F_API FMOD_System_GetNetworkTimeout         (FMOD_SYSTEM *system, int *timeout);

/* Userdata set/get. */
FMOD_RESULT F_API FMOD_System_SetUserData               (FMOD_SYSTEM *system, void *userdata);
FMOD_RESULT F_API FMOD_System_GetUserData               (FMOD_SYSTEM *system, void **userdata);

/* Sound API
*/

FMOD_RESULT F_API FMOD_Sound_Release                    (FMOD_SOUND *sound);
FMOD_RESULT F_API FMOD_Sound_GetSystemObject            (FMOD_SOUND *sound, FMOD_SYSTEM **system);

/*
     Standard sound manipulation functions.
*/

FMOD_RESULT F_API FMOD_Sound_Lock                       (FMOD_SOUND *sound, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
FMOD_RESULT F_API FMOD_Sound_Unlock                     (FMOD_SOUND *sound, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
FMOD_RESULT F_API FMOD_Sound_SetDefaults                (FMOD_SOUND *sound, float frequency, int priority);
FMOD_RESULT F_API FMOD_Sound_GetDefaults                (FMOD_SOUND *sound, float *frequency, int *priority);
FMOD_RESULT F_API FMOD_Sound_Set3DMinMaxDistance        (FMOD_SOUND *sound, float min, float max);
FMOD_RESULT F_API FMOD_Sound_Get3DMinMaxDistance        (FMOD_SOUND *sound, float *min, float *max);
FMOD_RESULT F_API FMOD_Sound_Set3DConeSettings          (FMOD_SOUND *sound, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_Sound_Get3DConeSettings          (FMOD_SOUND *sound, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_Sound_Set3DCustomRolloff         (FMOD_SOUND *sound, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_Sound_Get3DCustomRolloff         (FMOD_SOUND *sound, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_Sound_GetSubSound                (FMOD_SOUND *sound, int index, FMOD_SOUND **subsound);
FMOD_RESULT F_API FMOD_Sound_GetSubSoundParent          (FMOD_SOUND *sound, FMOD_SOUND **parentsound);
FMOD_RESULT F_API FMOD_Sound_GetName                    (FMOD_SOUND *sound, char *name, int namelen);
FMOD_RESULT F_API FMOD_Sound_GetLength                  (FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);
FMOD_RESULT F_API FMOD_Sound_GetFormat                  (FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
FMOD_RESULT F_API FMOD_Sound_GetNumSubSounds            (FMOD_SOUND *sound, int *numsubsounds);
FMOD_RESULT F_API FMOD_Sound_GetNumTags                 (FMOD_SOUND *sound, int *numtags, int *numtagsupdated);
FMOD_RESULT F_API FMOD_Sound_GetTag                     (FMOD_SOUND *sound, const char *name, int index, FMOD_TAG *tag);
FMOD_RESULT F_API FMOD_Sound_GetOpenState               (FMOD_SOUND *sound, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, FMOD_BOOL *starving, FMOD_BOOL *diskbusy);
FMOD_RESULT F_API FMOD_Sound_ReadData                   (FMOD_SOUND *sound, void *buffer, unsigned int length, unsigned int *read);
FMOD_RESULT F_API FMOD_Sound_SeekData                   (FMOD_SOUND *sound, unsigned int pcm);

FMOD_RESULT F_API FMOD_Sound_SetSoundGroup              (FMOD_SOUND *sound, FMOD_SOUNDGROUP *soundgroup);
FMOD_RESULT F_API FMOD_Sound_GetSoundGroup              (FMOD_SOUND *sound, FMOD_SOUNDGROUP **soundgroup);

/*
     Synchronization point API.  These points can come from markers embedded in wav files, and can also generate channel callbacks.
*/

FMOD_RESULT F_API FMOD_Sound_GetNumSyncPoints           (FMOD_SOUND *sound, int *numsyncpoints);
FMOD_RESULT F_API FMOD_Sound_GetSyncPoint               (FMOD_SOUND *sound, int index, FMOD_SYNCPOINT **point);
FMOD_RESULT F_API FMOD_Sound_GetSyncPointInfo           (FMOD_SOUND *sound, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
FMOD_RESULT F_API FMOD_Sound_AddSyncPoint               (FMOD_SOUND *sound, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
FMOD_RESULT F_API FMOD_Sound_DeleteSyncPoint            (FMOD_SOUND *sound, FMOD_SYNCPOINT *point);

/*
     Functions also in Channel class but here they are the 'default' to save having to change it in Channel all the time.
*/

FMOD_RESULT F_API FMOD_Sound_SetMode                    (FMOD_SOUND *sound, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_Sound_GetMode                    (FMOD_SOUND *sound, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_Sound_SetLoopCount               (FMOD_SOUND *sound, int loopcount);
FMOD_RESULT F_API FMOD_Sound_GetLoopCount               (FMOD_SOUND *sound, int *loopcount);
FMOD_RESULT F_API FMOD_Sound_SetLoopPoints              (FMOD_SOUND *sound, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT F_API FMOD_Sound_GetLoopPoints              (FMOD_SOUND *sound, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

/*
     For MOD/S3M/XM/IT/MID sequenced formats only.
*/

FMOD_RESULT F_API FMOD_Sound_GetMusicNumChannels        (FMOD_SOUND *sound, int *numchannels);
FMOD_RESULT F_API FMOD_Sound_SetMusicChannelVolume      (FMOD_SOUND *sound, int channel, float volume);
FMOD_RESULT F_API FMOD_Sound_GetMusicChannelVolume      (FMOD_SOUND *sound, int channel, float *volume);
FMOD_RESULT F_API FMOD_Sound_SetMusicSpeed              (FMOD_SOUND *sound, float speed);
FMOD_RESULT F_API FMOD_Sound_GetMusicSpeed              (FMOD_SOUND *sound, float *speed);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Sound_SetUserData                (FMOD_SOUND *sound, void *userdata);
FMOD_RESULT F_API FMOD_Sound_GetUserData                (FMOD_SOUND *sound, void **userdata);

/*
    'Channel' API
*/

FMOD_RESULT F_API FMOD_Channel_GetSystemObject          (FMOD_CHANNEL *channel, FMOD_SYSTEM **system);

/*
     General control functionality for Channels and ChannelGroups.
*/

FMOD_RESULT F_API FMOD_Channel_Stop                     (FMOD_CHANNEL *channel);
FMOD_RESULT F_API FMOD_Channel_SetPaused                (FMOD_CHANNEL *channel, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_Channel_GetPaused                (FMOD_CHANNEL *channel, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_Channel_SetVolume                (FMOD_CHANNEL *channel, float volume);
FMOD_RESULT F_API FMOD_Channel_GetVolume                (FMOD_CHANNEL *channel, float *volume);
FMOD_RESULT F_API FMOD_Channel_SetVolumeRamp            (FMOD_CHANNEL *channel, FMOD_BOOL ramp);
FMOD_RESULT F_API FMOD_Channel_GetVolumeRamp            (FMOD_CHANNEL *channel, FMOD_BOOL *ramp);
FMOD_RESULT F_API FMOD_Channel_GetAudibility            (FMOD_CHANNEL *channel, float *audibility);
FMOD_RESULT F_API FMOD_Channel_SetPitch                 (FMOD_CHANNEL *channel, float pitch);
FMOD_RESULT F_API FMOD_Channel_GetPitch                 (FMOD_CHANNEL *channel, float *pitch);
FMOD_RESULT F_API FMOD_Channel_SetMute                  (FMOD_CHANNEL *channel, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_Channel_GetMute                  (FMOD_CHANNEL *channel, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_Channel_SetReverbProperties      (FMOD_CHANNEL *channel, int instance, float wet);
FMOD_RESULT F_API FMOD_Channel_GetReverbProperties      (FMOD_CHANNEL *channel, int instance, float *wet);
FMOD_RESULT F_API FMOD_Channel_SetLowPassGain           (FMOD_CHANNEL *channel, float gain);
FMOD_RESULT F_API FMOD_Channel_GetLowPassGain           (FMOD_CHANNEL *channel, float *gain);
FMOD_RESULT F_API FMOD_Channel_SetMode                  (FMOD_CHANNEL *channel, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_Channel_GetMode                  (FMOD_CHANNEL *channel, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_Channel_SetCallback              (FMOD_CHANNEL *channel, FMOD_CHANNELCONTROL_CALLBACK callback);
FMOD_RESULT F_API FMOD_Channel_IsPlaying                (FMOD_CHANNEL *channel, FMOD_BOOL *isplaying);

/*
     Note all 'set' functions alter a final matrix, this is why the only get function is getMixMatrix, to avoid other get functions returning incorrect/obsolete values.
*/

FMOD_RESULT F_API FMOD_Channel_SetPan                   (FMOD_CHANNEL *channel, float pan);
FMOD_RESULT F_API FMOD_Channel_SetMixLevelsOutput       (FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright);
FMOD_RESULT F_API FMOD_Channel_SetMixLevelsInput        (FMOD_CHANNEL *channel, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_SetMixMatrix             (FMOD_CHANNEL *channel, float *matrix, int outchannels, int inchannels, int inchannel_hop);
FMOD_RESULT F_API FMOD_Channel_GetMixMatrix             (FMOD_CHANNEL *channel, float *matrix, int *outchannels, int *inchannels, int inchannel_hop);

/*
     Clock based functionality.
*/

FMOD_RESULT F_API FMOD_Channel_GetDSPClock              (FMOD_CHANNEL *channel, unsigned long long *dspclock, unsigned long long *parentclock);
FMOD_RESULT F_API FMOD_Channel_SetDelay                 (FMOD_CHANNEL *channel, unsigned long long dspclock_start, unsigned long long dspclock_end, FMOD_BOOL stopchannels);
FMOD_RESULT F_API FMOD_Channel_GetDelay                 (FMOD_CHANNEL *channel, unsigned long long *dspclock_start, unsigned long long *dspclock_end, FMOD_BOOL *stopchannels);
FMOD_RESULT F_API FMOD_Channel_AddFadePoint             (FMOD_CHANNEL *channel, unsigned long long dspclock, float volume);
FMOD_RESULT F_API FMOD_Channel_SetFadePointRamp         (FMOD_CHANNEL *channel, unsigned long long dspclock, float volume);
FMOD_RESULT F_API FMOD_Channel_RemoveFadePoints         (FMOD_CHANNEL *channel, unsigned long long dspclock_start, unsigned long long dspclock_end);
FMOD_RESULT F_API FMOD_Channel_GetFadePoints            (FMOD_CHANNEL *channel, unsigned int *numpoints, unsigned long long *point_dspclock, float *point_volume);

/*
     DSP effects.
*/

FMOD_RESULT F_API FMOD_Channel_GetDSP                   (FMOD_CHANNEL *channel, int index, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_Channel_AddDSP                   (FMOD_CHANNEL *channel, int index, FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_Channel_RemoveDSP                (FMOD_CHANNEL *channel, FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_Channel_GetNumDSPs               (FMOD_CHANNEL *channel, int *numdsps);
FMOD_RESULT F_API FMOD_Channel_SetDSPIndex              (FMOD_CHANNEL *channel, FMOD_DSP *dsp, int index);
FMOD_RESULT F_API FMOD_Channel_GetDSPIndex              (FMOD_CHANNEL *channel, FMOD_DSP *dsp, int *index);

/*
     3D functionality.
*/

FMOD_RESULT F_API FMOD_Channel_Set3DAttributes          (FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_Channel_Get3DAttributes          (FMOD_CHANNEL *channel, FMOD_VECTOR *pos, FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_Channel_Set3DMinMaxDistance      (FMOD_CHANNEL *channel, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_Channel_Get3DMinMaxDistance      (FMOD_CHANNEL *channel, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_Channel_Set3DConeSettings        (FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_Channel_Get3DConeSettings        (FMOD_CHANNEL *channel, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_Channel_Set3DConeOrientation     (FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Channel_Get3DConeOrientation     (FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Channel_Set3DCustomRolloff       (FMOD_CHANNEL *channel, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_Channel_Get3DCustomRolloff       (FMOD_CHANNEL *channel, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_Channel_Set3DOcclusion           (FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion);
FMOD_RESULT F_API FMOD_Channel_Get3DOcclusion           (FMOD_CHANNEL *channel, float *directocclusion, float *reverbocclusion);
FMOD_RESULT F_API FMOD_Channel_Set3DSpread              (FMOD_CHANNEL *channel, float angle);
FMOD_RESULT F_API FMOD_Channel_Get3DSpread              (FMOD_CHANNEL *channel, float *angle);
FMOD_RESULT F_API FMOD_Channel_Set3DLevel               (FMOD_CHANNEL *channel, float level);
FMOD_RESULT F_API FMOD_Channel_Get3DLevel               (FMOD_CHANNEL *channel, float *level);
FMOD_RESULT F_API FMOD_Channel_Set3DDopplerLevel        (FMOD_CHANNEL *channel, float level);
FMOD_RESULT F_API FMOD_Channel_Get3DDopplerLevel        (FMOD_CHANNEL *channel, float *level);
FMOD_RESULT F_API FMOD_Channel_Set3DDistanceFilter      (FMOD_CHANNEL *channel, FMOD_BOOL custom, float customLevel, float centerFreq);
FMOD_RESULT F_API FMOD_Channel_Get3DDistanceFilter      (FMOD_CHANNEL *channel, FMOD_BOOL *custom, float *customLevel, float *centerFreq);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Channel_SetUserData              (FMOD_CHANNEL *channel, void *userdata);
FMOD_RESULT F_API FMOD_Channel_GetUserData              (FMOD_CHANNEL *channel, void **userdata);

/*
     Channel specific control functionality.
*/

FMOD_RESULT F_API FMOD_Channel_SetFrequency             (FMOD_CHANNEL *channel, float frequency);
FMOD_RESULT F_API FMOD_Channel_GetFrequency             (FMOD_CHANNEL *channel, float *frequency);
FMOD_RESULT F_API FMOD_Channel_SetPriority              (FMOD_CHANNEL *channel, int priority);
FMOD_RESULT F_API FMOD_Channel_GetPriority              (FMOD_CHANNEL *channel, int *priority);
FMOD_RESULT F_API FMOD_Channel_SetPosition              (FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype);
FMOD_RESULT F_API FMOD_Channel_GetPosition              (FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype);
FMOD_RESULT F_API FMOD_Channel_SetChannelGroup          (FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_Channel_GetChannelGroup          (FMOD_CHANNEL *channel, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_Channel_SetLoopCount             (FMOD_CHANNEL *channel, int loopcount);
FMOD_RESULT F_API FMOD_Channel_GetLoopCount             (FMOD_CHANNEL *channel, int *loopcount);
FMOD_RESULT F_API FMOD_Channel_SetLoopPoints            (FMOD_CHANNEL *channel, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT F_API FMOD_Channel_GetLoopPoints            (FMOD_CHANNEL *channel, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_Channel_IsVirtual                (FMOD_CHANNEL *channel, FMOD_BOOL *isvirtual);
FMOD_RESULT F_API FMOD_Channel_GetCurrentSound          (FMOD_CHANNEL *channel, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_Channel_GetIndex                 (FMOD_CHANNEL *channel, int *index);

/*
    'ChannelGroup' API
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetSystemObject     (FMOD_CHANNELGROUP *channelgroup, FMOD_SYSTEM **system);

/*
     General control functionality for Channels and ChannelGroups.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_Stop                (FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_ChannelGroup_SetPaused           (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_ChannelGroup_GetPaused           (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_ChannelGroup_SetVolume           (FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_GetVolume           (FMOD_CHANNELGROUP *channelgroup, float *volume);
FMOD_RESULT F_API FMOD_ChannelGroup_SetVolumeRamp       (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL ramp);
FMOD_RESULT F_API FMOD_ChannelGroup_GetVolumeRamp       (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *ramp);
FMOD_RESULT F_API FMOD_ChannelGroup_GetAudibility       (FMOD_CHANNELGROUP *channelgroup, float *audibility);
FMOD_RESULT F_API FMOD_ChannelGroup_SetPitch            (FMOD_CHANNELGROUP *channelgroup, float pitch);
FMOD_RESULT F_API FMOD_ChannelGroup_GetPitch            (FMOD_CHANNELGROUP *channelgroup, float *pitch);
FMOD_RESULT F_API FMOD_ChannelGroup_SetMute             (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_ChannelGroup_GetMute             (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_ChannelGroup_SetReverbProperties (FMOD_CHANNELGROUP *channelgroup, int instance, float wet);
FMOD_RESULT F_API FMOD_ChannelGroup_GetReverbProperties (FMOD_CHANNELGROUP *channelgroup, int instance, float *wet);
FMOD_RESULT F_API FMOD_ChannelGroup_SetLowPassGain      (FMOD_CHANNELGROUP *channelgroup, float gain);
FMOD_RESULT F_API FMOD_ChannelGroup_GetLowPassGain      (FMOD_CHANNELGROUP *channelgroup, float *gain);
FMOD_RESULT F_API FMOD_ChannelGroup_SetMode             (FMOD_CHANNELGROUP *channelgroup, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_ChannelGroup_GetMode             (FMOD_CHANNELGROUP *channelgroup, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_ChannelGroup_SetCallback         (FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELCONTROL_CALLBACK callback);
FMOD_RESULT F_API FMOD_ChannelGroup_IsPlaying           (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *isplaying);

/*
     Note all 'set' functions alter a final matrix, this is why the only get function is getMixMatrix, to avoid other get functions returning incorrect/obsolete values.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_SetPan              (FMOD_CHANNELGROUP *channelgroup, float pan);
FMOD_RESULT F_API FMOD_ChannelGroup_SetMixLevelsOutput  (FMOD_CHANNELGROUP *channelgroup, float frontleft, float frontright, float center, float lfe, float surroundleft, float surroundright, float backleft, float backright);
FMOD_RESULT F_API FMOD_ChannelGroup_SetMixLevelsInput   (FMOD_CHANNELGROUP *channelgroup, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_ChannelGroup_SetMixMatrix        (FMOD_CHANNELGROUP *channelgroup, float *matrix, int outchannels, int inchannels, int inchannel_hop);
FMOD_RESULT F_API FMOD_ChannelGroup_GetMixMatrix        (FMOD_CHANNELGROUP *channelgroup, float *matrix, int *outchannels, int *inchannels, int inchannel_hop);

/*
     Clock based functionality.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetDSPClock         (FMOD_CHANNELGROUP *channelgroup, unsigned long long *dspclock, unsigned long long *parentclock);
FMOD_RESULT F_API FMOD_ChannelGroup_SetDelay            (FMOD_CHANNELGROUP *channelgroup, unsigned long long dspclock_start, unsigned long long dspclock_end, FMOD_BOOL stopchannels);
FMOD_RESULT F_API FMOD_ChannelGroup_GetDelay            (FMOD_CHANNELGROUP *channelgroup, unsigned long long *dspclock_start, unsigned long long *dspclock_end, FMOD_BOOL *stopchannels);
FMOD_RESULT F_API FMOD_ChannelGroup_AddFadePoint        (FMOD_CHANNELGROUP *channelgroup, unsigned long long dspclock, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_SetFadePointRamp    (FMOD_CHANNELGROUP *channelgroup, unsigned long long dspclock, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_RemoveFadePoints    (FMOD_CHANNELGROUP *channelgroup, unsigned long long dspclock_start, unsigned long long dspclock_end);
FMOD_RESULT F_API FMOD_ChannelGroup_GetFadePoints       (FMOD_CHANNELGROUP *channelgroup, unsigned int *numpoints, unsigned long long *point_dspclock, float *point_volume);

/*
     DSP effects.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetDSP              (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_ChannelGroup_AddDSP              (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_ChannelGroup_RemoveDSP           (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumDSPs          (FMOD_CHANNELGROUP *channelgroup, int *numdsps);
FMOD_RESULT F_API FMOD_ChannelGroup_SetDSPIndex         (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp, int index);
FMOD_RESULT F_API FMOD_ChannelGroup_GetDSPIndex         (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp, int *index);

/*
     3D functionality.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_Set3DAttributes     (FMOD_CHANNELGROUP *channelgroup, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DAttributes     (FMOD_CHANNELGROUP *channelgroup, FMOD_VECTOR *pos, FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DMinMaxDistance (FMOD_CHANNELGROUP *channelgroup, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DMinMaxDistance (FMOD_CHANNELGROUP *channelgroup, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DConeSettings   (FMOD_CHANNELGROUP *channelgroup, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DConeSettings   (FMOD_CHANNELGROUP *channelgroup, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DConeOrientation(FMOD_CHANNELGROUP *channelgroup, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DConeOrientation(FMOD_CHANNELGROUP *channelgroup, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DCustomRolloff  (FMOD_CHANNELGROUP *channelgroup, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DCustomRolloff  (FMOD_CHANNELGROUP *channelgroup, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DOcclusion      (FMOD_CHANNELGROUP *channelgroup, float directocclusion, float reverbocclusion);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DOcclusion      (FMOD_CHANNELGROUP *channelgroup, float *directocclusion, float *reverbocclusion);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DSpread         (FMOD_CHANNELGROUP *channelgroup, float angle);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DSpread         (FMOD_CHANNELGROUP *channelgroup, float *angle);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DLevel          (FMOD_CHANNELGROUP *channelgroup, float level);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DLevel          (FMOD_CHANNELGROUP *channelgroup, float *level);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DDopplerLevel   (FMOD_CHANNELGROUP *channelgroup, float level);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DDopplerLevel   (FMOD_CHANNELGROUP *channelgroup, float *level);
FMOD_RESULT F_API FMOD_ChannelGroup_Set3DDistanceFilter (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL custom, float customLevel, float centerFreq);
FMOD_RESULT F_API FMOD_ChannelGroup_Get3DDistanceFilter (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *custom, float *customLevel, float *centerFreq);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_SetUserData         (FMOD_CHANNELGROUP *channelgroup, void *userdata);
FMOD_RESULT F_API FMOD_ChannelGroup_GetUserData         (FMOD_CHANNELGROUP *channelgroup, void **userdata);

FMOD_RESULT F_API FMOD_ChannelGroup_Release             (FMOD_CHANNELGROUP *channelgroup);

/*
     Nested channel groups.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_AddGroup            (FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP *group, FMOD_BOOL propagatedspclock, FMOD_DSPCONNECTION **connection);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumGroups        (FMOD_CHANNELGROUP *channelgroup, int *numgroups);
FMOD_RESULT F_API FMOD_ChannelGroup_GetGroup            (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNELGROUP **group);
FMOD_RESULT F_API FMOD_ChannelGroup_GetParentGroup      (FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP **group);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetName             (FMOD_CHANNELGROUP *channelgroup, char *name, int namelen);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumChannels      (FMOD_CHANNELGROUP *channelgroup, int *numchannels);
FMOD_RESULT F_API FMOD_ChannelGroup_GetChannel          (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNEL **channel);

/*
    'SoundGroup' API
*/

FMOD_RESULT F_API FMOD_SoundGroup_Release               (FMOD_SOUNDGROUP *soundgroup);
FMOD_RESULT F_API FMOD_SoundGroup_GetSystemObject       (FMOD_SOUNDGROUP *soundgroup, FMOD_SYSTEM **system);

/*
     SoundGroup control functions.
*/

FMOD_RESULT F_API FMOD_SoundGroup_SetMaxAudible         (FMOD_SOUNDGROUP *soundgroup, int maxaudible);
FMOD_RESULT F_API FMOD_SoundGroup_GetMaxAudible         (FMOD_SOUNDGROUP *soundgroup, int *maxaudible);
FMOD_RESULT F_API FMOD_SoundGroup_SetMaxAudibleBehavior (FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR behavior);
FMOD_RESULT F_API FMOD_SoundGroup_GetMaxAudibleBehavior (FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR *behavior);
FMOD_RESULT F_API FMOD_SoundGroup_SetMuteFadeSpeed      (FMOD_SOUNDGROUP *soundgroup, float speed);
FMOD_RESULT F_API FMOD_SoundGroup_GetMuteFadeSpeed      (FMOD_SOUNDGROUP *soundgroup, float *speed);
FMOD_RESULT F_API FMOD_SoundGroup_SetVolume             (FMOD_SOUNDGROUP *soundgroup, float volume);
FMOD_RESULT F_API FMOD_SoundGroup_GetVolume             (FMOD_SOUNDGROUP *soundgroup, float *volume);
FMOD_RESULT F_API FMOD_SoundGroup_Stop                  (FMOD_SOUNDGROUP *soundgroup);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_SoundGroup_GetName               (FMOD_SOUNDGROUP *soundgroup, char *name, int namelen);
FMOD_RESULT F_API FMOD_SoundGroup_GetNumSounds          (FMOD_SOUNDGROUP *soundgroup, int *numsounds);
FMOD_RESULT F_API FMOD_SoundGroup_GetSound              (FMOD_SOUNDGROUP *soundgroup, int index, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_SoundGroup_GetNumPlaying         (FMOD_SOUNDGROUP *soundgroup, int *numplaying);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_SoundGroup_SetUserData           (FMOD_SOUNDGROUP *soundgroup, void *userdata);
FMOD_RESULT F_API FMOD_SoundGroup_GetUserData           (FMOD_SOUNDGROUP *soundgroup, void **userdata);

/*
    'DSP' API
*/

FMOD_RESULT F_API FMOD_DSP_Release                      (FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_DSP_GetSystemObject              (FMOD_DSP *dsp, FMOD_SYSTEM **system);

/*
     Connection / disconnection / input and output enumeration.
*/

FMOD_RESULT F_API FMOD_DSP_AddInput                     (FMOD_DSP *dsp, FMOD_DSP *input, FMOD_DSPCONNECTION **connection, FMOD_DSPCONNECTION_TYPE type);
FMOD_RESULT F_API FMOD_DSP_DisconnectFrom               (FMOD_DSP *dsp, FMOD_DSP *target, FMOD_DSPCONNECTION *connection);
FMOD_RESULT F_API FMOD_DSP_DisconnectAll                (FMOD_DSP *dsp, FMOD_BOOL inputs, FMOD_BOOL outputs);
FMOD_RESULT F_API FMOD_DSP_GetNumInputs                 (FMOD_DSP *dsp, int *numinputs);
FMOD_RESULT F_API FMOD_DSP_GetNumOutputs                (FMOD_DSP *dsp, int *numoutputs);
FMOD_RESULT F_API FMOD_DSP_GetInput                     (FMOD_DSP *dsp, int index, FMOD_DSP **input, FMOD_DSPCONNECTION **inputconnection);
FMOD_RESULT F_API FMOD_DSP_GetOutput                    (FMOD_DSP *dsp, int index, FMOD_DSP **output, FMOD_DSPCONNECTION **outputconnection);

/*
     DSP unit control.
*/

FMOD_RESULT F_API FMOD_DSP_SetActive                    (FMOD_DSP *dsp, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_DSP_GetActive                    (FMOD_DSP *dsp, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_DSP_SetBypass                    (FMOD_DSP *dsp, FMOD_BOOL bypass);
FMOD_RESULT F_API FMOD_DSP_GetBypass                    (FMOD_DSP *dsp, FMOD_BOOL *bypass);
FMOD_RESULT F_API FMOD_DSP_SetWetDryMix                 (FMOD_DSP *dsp, float prewet, float postwet, float dry);
FMOD_RESULT F_API FMOD_DSP_GetWetDryMix                 (FMOD_DSP *dsp, float *prewet, float *postwet, float *dry);
FMOD_RESULT F_API FMOD_DSP_SetChannelFormat             (FMOD_DSP *dsp, FMOD_CHANNELMASK channelmask, int numchannels, FMOD_SPEAKERMODE source_speakermode);
FMOD_RESULT F_API FMOD_DSP_GetChannelFormat             (FMOD_DSP *dsp, FMOD_CHANNELMASK *channelmask, int *numchannels, FMOD_SPEAKERMODE *source_speakermode);
FMOD_RESULT F_API FMOD_DSP_GetOutputChannelFormat       (FMOD_DSP *dsp, FMOD_CHANNELMASK inmask, int inchannels, FMOD_SPEAKERMODE inspeakermode, FMOD_CHANNELMASK *outmask, int *outchannels, FMOD_SPEAKERMODE *outspeakermode);
FMOD_RESULT F_API FMOD_DSP_Reset                        (FMOD_DSP *dsp);

/*
     DSP parameter control.
*/

FMOD_RESULT F_API FMOD_DSP_SetParameterFloat            (FMOD_DSP *dsp, int index, float value);
FMOD_RESULT F_API FMOD_DSP_SetParameterInt              (FMOD_DSP *dsp, int index, int value);
FMOD_RESULT F_API FMOD_DSP_SetParameterBool             (FMOD_DSP *dsp, int index, FMOD_BOOL value);
FMOD_RESULT F_API FMOD_DSP_SetParameterData             (FMOD_DSP *dsp, int index, void *data, unsigned int length);
FMOD_RESULT F_API FMOD_DSP_GetParameterFloat            (FMOD_DSP *dsp, int index, float *value, char *valuestr, int valuestrlen);
FMOD_RESULT F_API FMOD_DSP_GetParameterInt              (FMOD_DSP *dsp, int index, int *value, char *valuestr, int valuestrlen);
FMOD_RESULT F_API FMOD_DSP_GetParameterBool             (FMOD_DSP *dsp, int index, FMOD_BOOL *value, char *valuestr, int valuestrlen);
FMOD_RESULT F_API FMOD_DSP_GetParameterData             (FMOD_DSP *dsp, int index, void **data, unsigned int *length, char *valuestr, int valuestrlen);
FMOD_RESULT F_API FMOD_DSP_GetNumParameters             (FMOD_DSP *dsp, int *numparams);
FMOD_RESULT F_API FMOD_DSP_GetParameterInfo             (FMOD_DSP *dsp, int index, FMOD_DSP_PARAMETER_DESC **desc);
FMOD_RESULT F_API FMOD_DSP_GetDataParameterIndex        (FMOD_DSP *dsp, int datatype, int *index);
FMOD_RESULT F_API FMOD_DSP_ShowConfigDialog             (FMOD_DSP *dsp, void *hwnd, FMOD_BOOL show);

/*
     DSP attributes.
*/

FMOD_RESULT F_API FMOD_DSP_GetInfo                      (FMOD_DSP *dsp, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
FMOD_RESULT F_API FMOD_DSP_GetType                      (FMOD_DSP *dsp, FMOD_DSP_TYPE *type);
FMOD_RESULT F_API FMOD_DSP_GetIdle                      (FMOD_DSP *dsp, FMOD_BOOL *idle);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_DSP_SetUserData                  (FMOD_DSP *dsp, void *userdata);
FMOD_RESULT F_API FMOD_DSP_GetUserData                  (FMOD_DSP *dsp, void **userdata);

/*
     Metering.
*/

FMOD_RESULT F_API FMOD_DSP_SetMeteringEnabled           (FMOD_DSP *dsp, FMOD_BOOL inputEnabled, FMOD_BOOL outputEnabled);
FMOD_RESULT F_API FMOD_DSP_GetMeteringEnabled           (FMOD_DSP *dsp, FMOD_BOOL *inputEnabled, FMOD_BOOL *outputEnabled);
FMOD_RESULT F_API FMOD_DSP_GetMeteringInfo              (FMOD_DSP *dsp, FMOD_DSP_METERING_INFO *inputInfo, FMOD_DSP_METERING_INFO *outputInfo);
FMOD_RESULT F_API FMOD_DSP_GetCPUUsage                  (FMOD_DSP *dsp, unsigned int *exclusive, unsigned int *inclusive);

/*
    'DSPConnection' API
*/

FMOD_RESULT F_API FMOD_DSPConnection_GetInput           (FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **input);
FMOD_RESULT F_API FMOD_DSPConnection_GetOutput          (FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **output);
FMOD_RESULT F_API FMOD_DSPConnection_SetMix             (FMOD_DSPCONNECTION *dspconnection, float volume);
FMOD_RESULT F_API FMOD_DSPConnection_GetMix             (FMOD_DSPCONNECTION *dspconnection, float *volume);
FMOD_RESULT F_API FMOD_DSPConnection_SetMixMatrix       (FMOD_DSPCONNECTION *dspconnection, float *matrix, int outchannels, int inchannels, int inchannel_hop);
FMOD_RESULT F_API FMOD_DSPConnection_GetMixMatrix       (FMOD_DSPCONNECTION *dspconnection, float *matrix, int *outchannels, int *inchannels, int inchannel_hop);
FMOD_RESULT F_API FMOD_DSPConnection_GetType            (FMOD_DSPCONNECTION *dspconnection, FMOD_DSPCONNECTION_TYPE *type);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_DSPConnection_SetUserData        (FMOD_DSPCONNECTION *dspconnection, void *userdata);
FMOD_RESULT F_API FMOD_DSPConnection_GetUserData        (FMOD_DSPCONNECTION *dspconnection, void **userdata);

/*
    'Geometry' API
*/

FMOD_RESULT F_API FMOD_Geometry_Release                 (FMOD_GEOMETRY *geometry);

/*
     Polygon manipulation.
*/

FMOD_RESULT F_API FMOD_Geometry_AddPolygon              (FMOD_GEOMETRY *geometry, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex);
FMOD_RESULT F_API FMOD_Geometry_GetNumPolygons          (FMOD_GEOMETRY *geometry, int *numpolygons);
FMOD_RESULT F_API FMOD_Geometry_GetMaxPolygons          (FMOD_GEOMETRY *geometry, int *maxpolygons, int *maxvertices);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonNumVertices   (FMOD_GEOMETRY *geometry, int index, int *numvertices);
FMOD_RESULT F_API FMOD_Geometry_SetPolygonVertex        (FMOD_GEOMETRY *geometry, int index, int vertexindex, const FMOD_VECTOR *vertex);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonVertex        (FMOD_GEOMETRY *geometry, int index, int vertexindex, FMOD_VECTOR *vertex);
FMOD_RESULT F_API FMOD_Geometry_SetPolygonAttributes    (FMOD_GEOMETRY *geometry, int index, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonAttributes    (FMOD_GEOMETRY *geometry, int index, float *directocclusion, float *reverbocclusion, FMOD_BOOL *doublesided);

/*
     Object manipulation.
*/

FMOD_RESULT F_API FMOD_Geometry_SetActive               (FMOD_GEOMETRY *geometry, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_Geometry_GetActive               (FMOD_GEOMETRY *geometry, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_Geometry_SetRotation             (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_Geometry_GetRotation             (FMOD_GEOMETRY *geometry, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_Geometry_SetPosition             (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *position);
FMOD_RESULT F_API FMOD_Geometry_GetPosition             (FMOD_GEOMETRY *geometry, FMOD_VECTOR *position);
FMOD_RESULT F_API FMOD_Geometry_SetScale                (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *scale);
FMOD_RESULT F_API FMOD_Geometry_GetScale                (FMOD_GEOMETRY *geometry, FMOD_VECTOR *scale);
FMOD_RESULT F_API FMOD_Geometry_Save                    (FMOD_GEOMETRY *geometry, void *data, int *datasize);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Geometry_SetUserData             (FMOD_GEOMETRY *geometry, void *userdata);
FMOD_RESULT F_API FMOD_Geometry_GetUserData             (FMOD_GEOMETRY *geometry, void **userdata);

/*
    'Reverb3D' API
*/

FMOD_RESULT F_API FMOD_Reverb3D_Release                 (FMOD_REVERB3D *reverb3d);

/*
     Reverb manipulation.
*/

FMOD_RESULT F_API FMOD_Reverb3D_Set3DAttributes         (FMOD_REVERB3D *reverb3d, const FMOD_VECTOR *position, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_Reverb3D_Get3DAttributes         (FMOD_REVERB3D *reverb3d, FMOD_VECTOR *position, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_Reverb3D_SetProperties           (FMOD_REVERB3D *reverb3d, const FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT F_API FMOD_Reverb3D_GetProperties           (FMOD_REVERB3D *reverb3d, FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT F_API FMOD_Reverb3D_SetActive               (FMOD_REVERB3D *reverb3d, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_Reverb3D_GetActive               (FMOD_REVERB3D *reverb3d, FMOD_BOOL *active);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Reverb3D_SetUserData             (FMOD_REVERB3D *reverb3d, void *userdata);
FMOD_RESULT F_API FMOD_Reverb3D_GetUserData             (FMOD_REVERB3D *reverb3d, void **userdata);

typedef struct FMOD_OUTPUT_STATE FMOD_OUTPUT_STATE;

/*
    Output callbacks
*/ 
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETNUMDRIVERSCALLBACK)  (FMOD_OUTPUT_STATE *output_state, int *numdrivers);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETDRIVERINFOCALLBACK)  (FMOD_OUTPUT_STATE *output, int id, char *name, short *nameW, int namelen, FMOD_GUID *guid, int *systemrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_INITCALLBACK)           (FMOD_OUTPUT_STATE *output_state, int selecteddriver, FMOD_INITFLAGS flags, int *outputrate, FMOD_SPEAKERMODE *speakermode, int *speakermodechannels, FMOD_SOUND_FORMAT *outputformat, int dspbufferlength, int dspnumbuffers, void *extradriverdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_STARTCALLBACK)          (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_STOPCALLBACK)           (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_CLOSECALLBACK)          (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_UPDATECALLBACK)         (FMOD_OUTPUT_STATE *output_state);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETHANDLECALLBACK)      (FMOD_OUTPUT_STATE *output_state, void **handle);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_GETPOSITIONCALLBACK)    (FMOD_OUTPUT_STATE *output_state, unsigned int *pcm);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_LOCKCALLBACK)           (FMOD_OUTPUT_STATE *output_state, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_UNLOCKCALLBACK)         (FMOD_OUTPUT_STATE *output_state, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);

typedef FMOD_RESULT (F_CALLBACK *FMOD_OUTPUT_READFROMMIXER)          (FMOD_OUTPUT_STATE *output_state, void *buffer, unsigned int length);  /* This one is called by plugin through FMOD_OUTPUT_STATE, not set by user as a callback. */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    When creating an output, declare one of these and provide the relevant callbacks and name for FMOD to use when it opens and reads a file of this type.
    [REMARKS]
    Members marked with [in] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [out] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    [SEE_ALSO]
    FMOD_OUTPUT_STATE
]
*/
typedef struct FMOD_OUTPUT_DESCRIPTION
{
    const char                        *name;                  /* [in] Name of the output. */
    unsigned int                       version;               /* [in] Plugin writer's version number. */
    int                                polling;               /* [in] If TRUE (non zero), this tells FMOD to start a thread and call getposition / lock / unlock for feeding data.  If 0, the output is probably callback based, so all the plugin needs to do is call readfrommixer to the appropriate pointer. */ 
    FMOD_OUTPUT_GETNUMDRIVERSCALLBACK  getnumdrivers;         /* [in] For sound device enumeration.  This callback is to give System::getNumDrivers somthing to return. */
    FMOD_OUTPUT_GETDRIVERINFOCALLBACK  getdriverinfo;         /* [in] For sound device enumeration.  This callback is to give System::getDriverName somthing to return. */
    FMOD_OUTPUT_INITCALLBACK           init;                  /* [in] Initialization function for the output device.  This is called from System::init. */
    FMOD_OUTPUT_STARTCALLBACK          start;                 /* [in] Initialization function for the output device to start accepting audio data from the FMOD software mixer.  This is called from System::init. */
    FMOD_OUTPUT_STOPCALLBACK           stop;                  /* [in] Initialization function for the output device to stop accepting audio data from FMOD the software mixer.  This is called from System::close. */
    FMOD_OUTPUT_CLOSECALLBACK          close;                 /* [in] Cleanup / close down function for the output device.  This is called from System::close. */
    FMOD_OUTPUT_UPDATECALLBACK         update;                /* [in] Update function that is called once a frame by the user.  This is called from System::update. */
    FMOD_OUTPUT_GETHANDLECALLBACK      gethandle;             /* [in] This is called from System::getOutputHandle.  This is just to return a pointer to the internal system device object that the system may be using.*/
    FMOD_OUTPUT_GETPOSITIONCALLBACK    getposition;           /* [in] This is called from the FMOD software mixer thread if 'polling' = true.  This returns a position value in samples so that FMOD knows where and when to fill its buffer. */
    FMOD_OUTPUT_LOCKCALLBACK           lock;                  /* [in] This is called from the FMOD software mixer thread if 'polling' = true.  This function provides a pointer to data that FMOD can write to when software mixing. */
    FMOD_OUTPUT_UNLOCKCALLBACK         unlock;                /* [in] This is called from the FMOD software mixer thread if 'polling' = true.  This optional function accepts the data that has been mixed and copies it or does whatever it needs to before sending it to the hardware. */
} FMOD_OUTPUT_DESCRIPTION;

FMOD_RESULT F_API FMOD_System_RegisterOutput            (FMOD_SYSTEM *system, const FMOD_OUTPUT_DESCRIPTION *description, unsigned int *handle);

/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Output plugin structure that is passed into each callback.
    [REMARKS]
    Members marked with [in] mean the variable can be written to.  The user can set the value.<br>
    Members marked with [out] mean the variable is modified by FMOD and is for reading purposes only.  Do not change this value.<br>
    [SEE_ALSO]
    FMOD_OUTPUT_DESCRIPTION
]
*/
struct FMOD_OUTPUT_STATE
{
    void                      *plugindata;      /* [in] Plugin writer created data the output author wants to attach to this object. */
    FMOD_OUTPUT_READFROMMIXER  readfrommixer;   /* [out] Function to update mixer and write the result to the provided pointer.  Used from callback based output only.  Polling based output uses lock/unlock/getposition. */
};

#endif