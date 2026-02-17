// TODO: Save script button
// TODO: Script source viewer and changer (create separate window to edit and shit)

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <CommCtrl.h>
#include <commdlg.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdarg>
#include <wininet.h>
#include <unordered_map>
#pragma comment(lib, "wininet.lib")

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "comdlg32.lib")

// ==================== IL2CPP Types ====================
typedef void* Il2CppString;
typedef void* Il2CppArray;
typedef void* Il2CppDomain;
typedef void* Il2CppThread;
typedef void* Il2CppClass;
typedef void* Il2CppImage;
typedef void* Il2CppAssembly;

// ==================== IL2CPP API ====================
typedef Il2CppString* (__cdecl* il2cpp_string_new_t)(const char* str);
typedef Il2CppDomain* (__cdecl* il2cpp_domain_get_t)();
typedef Il2CppThread* (__cdecl* il2cpp_thread_attach_t)(Il2CppDomain* domain);
typedef void(__cdecl* il2cpp_thread_detach_t)(Il2CppThread* thread);
typedef Il2CppAssembly** (__cdecl* il2cpp_domain_get_assemblies_t)(Il2CppDomain* domain, size_t* count);
typedef Il2CppImage* (__cdecl* il2cpp_assembly_get_image_t)(Il2CppAssembly* assembly);
typedef Il2CppClass* (__cdecl* il2cpp_class_from_name_t)(Il2CppImage* image, const char* namespaze, const char* name);
typedef void* (__cdecl* il2cpp_class_get_static_field_data_t)(Il2CppClass* klass);

typedef Il2CppArray* (__fastcall* Instance_GetChildren_t)(void* instance);
typedef Il2CppString* (__fastcall* Instance_get_Name_t)(void* instance);
typedef void(__fastcall* Instance_set_Name_t)(void* instance, Il2CppString* value);
typedef Il2CppString* (__fastcall* Instance_get_ClassName_t)(void* instance);
typedef void(__fastcall* Instance_Destroy_t)(void* instance, float time);
typedef void* (__fastcall* Instance_Clone_t)(void* instance);
typedef void* (__fastcall* Instance_New_t)(Il2CppString* className, void* parent);

typedef void(__fastcall* BaseScript_set_Source_t)(void* script, Il2CppString* source);
typedef void(__fastcall* BaseScript_Run_t)(void* script);
typedef void* (__cdecl* ScriptService_get_Instance_t)();
typedef void(__fastcall* ScriptService_RunScript_t)(void* scriptService, void* script);
typedef Il2CppString* (__fastcall* BaseScript_get_Source_t)(void* script);

typedef void(__fastcall* NetworkEvent_InvokeServer_t)(void* networkEvent, void* msg);

typedef void(__fastcall* Plr_CmdSetHealth_t)(void* player, float health);

typedef void(__fastcall* NW_ctor_t)(void* self);
typedef void(__fastcall* NW_WriteByte_t)(void* self, uint8_t value);
typedef void(__fastcall* NW_WriteBlittableFloat_t)(void* self, float value);
typedef void(__fastcall* NW_WriteBlittableUInt_t)(void* self, uint32_t value);
typedef void(__fastcall* NW_WriteBlittableUShort_t)(void* self, uint16_t value);
typedef void(__fastcall* NW_WriteBool_t)(void* self, bool value);
typedef void(__fastcall* NW_WriteVector3_t)(void* self, void* vec3ptr);
typedef void(__fastcall* NW_WriteString_t)(void* self, void* str);
typedef void* (__cdecl* il2cpp_object_new_t)(void* klass);
typedef void(__fastcall* SendCommandInternal_t)(void* self, Il2CppString* funcName, int functionHash, void* writer, int channelId, bool requireAuthority);
typedef uint32_t(__fastcall* NB_get_netId_t)(void* self);

// ==================== Globals ====================
HMODULE g_GameAssembly = nullptr;
HMODULE g_Module = nullptr;

il2cpp_string_new_t il2cpp_string_new = nullptr;
il2cpp_domain_get_t il2cpp_domain_get = nullptr;
il2cpp_thread_attach_t il2cpp_thread_attach = nullptr;
il2cpp_thread_detach_t il2cpp_thread_detach = nullptr;
il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies = nullptr;
il2cpp_assembly_get_image_t il2cpp_assembly_get_image = nullptr;
il2cpp_class_from_name_t il2cpp_class_from_name = nullptr;
il2cpp_class_get_static_field_data_t il2cpp_class_get_static_field_data = nullptr;

Instance_GetChildren_t Instance_GetChildren = nullptr;
Instance_get_Name_t Instance_get_Name = nullptr;
Instance_set_Name_t Instance_set_Name = nullptr;
Instance_get_ClassName_t Instance_get_ClassName = nullptr;
Instance_Destroy_t Instance_Destroy = nullptr;
Instance_Clone_t Instance_Clone = nullptr;
Instance_New_t Instance_New = nullptr;

BaseScript_set_Source_t BaseScript_set_Source = nullptr;
BaseScript_get_Source_t BaseScript_get_Source = nullptr;
BaseScript_Run_t BaseScript_Run = nullptr;
ScriptService_get_Instance_t ScriptService_get_Instance = nullptr;
ScriptService_RunScript_t ScriptService_RunScript = nullptr;

Plr_CmdSetHealth_t Plr_CmdSetHealth = nullptr;
void* g_PlayersInstance = nullptr;


il2cpp_object_new_t il2cpp_object_new = nullptr;
NW_ctor_t NW_ctor = nullptr;
NW_WriteByte_t NW_WriteByte = nullptr;
NW_WriteBlittableFloat_t NW_WriteFloat = nullptr;
NW_WriteBlittableUInt_t NW_WriteUInt = nullptr;
NW_WriteBlittableUShort_t NW_WriteUShort = nullptr;
NW_WriteBool_t NW_WriteBool = nullptr;
NW_WriteVector3_t NW_WriteVector3 = nullptr;
NW_WriteString_t NW_WriteString = nullptr;
SendCommandInternal_t SendCmdInternal = nullptr;
NB_get_netId_t NB_get_netId = nullptr;

void* g_NetworkWriterClass = nullptr;
void* g_SendCmdAddr = nullptr;
BYTE g_SendCmdOrig[14];
bool g_AuthBypassEnabled = false;
bool g_CmdSnifferEnabled = false;

uintptr_t g_NB_netIdentity_offset = 0;
uintptr_t g_NI_netId_offset = 0;
int g_CmdSetHealth_Hash = 0;

struct CapturedCmd {
    int hash;
    char funcName[128];
    int payloadSize;
    uint8_t payload[256];
    uint32_t fromNetId;
};
CapturedCmd g_CapturedCmds[256];
int g_CapturedCmdCount = 0;

struct PlayerInfo {
    void* ptr;
    uint32_t netId;
    char name[128];
};
PlayerInfo g_ScannedPlayers[64];
int g_ScannedPlayerCount = 0;



Il2CppDomain* g_Domain = nullptr;
Il2CppThread* g_Thread = nullptr;
void* g_GameSingleton = nullptr;
void* g_ScriptService = nullptr;
void* g_CurrentScript = nullptr;

bool g_EventLoggerEnabled = false;
bool g_HooksInstalled = false;
void* g_InvokeServerAddr = nullptr;
BYTE g_InvokeServerOrig[14];

void* g_CreatedScripts[128];
int g_CreatedScriptCount = 0;
bool g_AutoCleanup = true;

// ---- State ----
bool g_PCEnabled = false;          // packet canceller active
bool g_PCLogging = false;          // logging RPCs
bool g_PCAutoBlock = false;        // auto-block mode
bool g_AntiKickEnabled = false;
bool g_HealthFreezeEnabled = false;
bool g_FullDesyncEnabled = false;

// ---- Blocked hashes ----
struct BlockedEntry {
    uint16_t hash;
    char label[64];        // user label or auto-detected name
    int blockCount;        // how many times blocked
    bool enabled;
};
BlockedEntry g_Blocked[256];
int g_BlockedCount = 0;

// ---- RPC Log (ring buffer) ----
struct RpcLogEntry {
    uint16_t hash;
    uint8_t componentIndex;
    uint8_t callType;      // 0=Cmd, 1=ClientRpc, 2=TargetRpc
    uint32_t netId;
    DWORD timestamp;
    bool wasBlocked;
};
RpcLogEntry g_RpcLog[512];
int g_RpcLogHead = 0;
int g_RpcLogCount = 0;

// ---- Hook addresses ----
void* g_HandleRCAddr = nullptr;
BYTE g_HandleRCOrig[14];
bool g_HandleRCHooked = false;

void* g_DelayedDiscAddr = nullptr;
BYTE g_DelayedDiscOrig[14];
bool g_DelayedDiscHooked = false;

void* g_DeserializeAddr = nullptr;
BYTE g_DeserializeOrig[14];
bool g_DeserializeHooked = false;

constexpr uintptr_t HANDLE_REMOTE_CALL_OFFSET = 0x132FFF0;
constexpr uintptr_t CONN_DISCONNECT_OFFSET = 0x132E7A0;   // NetworkConnectionToServer::Disconnect
constexpr uintptr_t CONN_ISALIVE_OFFSET = 0x132EB70;
constexpr uintptr_t DELAYED_DISCONNECT_OFFSET = 0x431CB0;    // PTAuthenticator::DelayedDisconnect
constexpr uintptr_t DESERIALIZE_CLIENT_OFFSET = 0x132FCB0;   // NetworkIdentity::DeserializeClient

std::string g_LoadedLuaFile;

// ==================== Offsets ====================
constexpr uintptr_t INSTANCE_GETCHILDREN_OFFSET = 0x44AEF0;    // TODO: обновить
constexpr uintptr_t INSTANCE_GET_NAME_OFFSET = 0x417800;       // TODO: обновить
constexpr uintptr_t INSTANCE_SET_NAME_OFFSET = 0x44F800;       // TODO: обновить
constexpr uintptr_t INSTANCE_GET_CLASSNAME_OFFSET = 0x2FDB30;  // TODO: обновить
constexpr uintptr_t INSTANCE_DESTROY_OFFSET = 0x44A620;        // TODO: обновить
constexpr uintptr_t INSTANCE_CLONE_OFFSET = 0x44A350;          // TODO: обновить
constexpr uintptr_t INSTANCE_NEW_OFFSET = 0x44BE30;


constexpr uintptr_t BASESCRIPT_SET_SOURCE_OFFSET = 0x4238B0;
constexpr uintptr_t BASESCRIPT_RUN_OFFSET = 0x422EF0;
constexpr uintptr_t BASESCRIPT_GET_SOURCE_OFFSET = 0x417820;  // get_Networksource
constexpr uintptr_t SCRIPTSERVICE_GET_INSTANCE_OFFSET = 0x4B3B70;
constexpr uintptr_t SCRIPTSERVICE_RUNSCRIPT_OFFSET = 0x4B30B0;

constexpr uintptr_t PLR_CMDSETHEALTH_OFFSET = 0x470310;
constexpr uintptr_t PLAYERS_LOCALPLAYER_OFFSET = 0x108;
constexpr uintptr_t BASESCRIPT_SOURCE_FIELD_OFFSET = 0x108;

constexpr uintptr_t NETEVENT_INVOKESERVER_OFFSET = 0x45D800;
constexpr uintptr_t NETMSG_STRINGS_OFFSET = 0x10, NETMSG_INTS_OFFSET = 0x18, NETMSG_NUMBERS_OFFSET = 0x20;
constexpr uintptr_t NETMSG_BOOLS_OFFSET = 0x28, NETMSG_VEC2S_OFFSET = 0x30, NETMSG_VEC3S_OFFSET = 0x38;

constexpr uintptr_t NW_CTOR_OFFSET = 0x136B920;
constexpr uintptr_t NW_WRITEBYTE_OFFSET = 0x136B7E0;
constexpr uintptr_t NW_WRITE_FLOAT_OFFSET = 0x757A30;
constexpr uintptr_t NW_WRITE_INT_OFFSET = 0x755CD0;
constexpr uintptr_t NW_WRITE_UINT_OFFSET = 0x7578B0;
constexpr uintptr_t NW_WRITE_USHORT_OFFSET = 0x757860;
constexpr uintptr_t NW_WRITE_BOOL_OFFSET = 0x7557A0;
constexpr uintptr_t NW_WRITE_VEC3_OFFSET = 0x758150;
constexpr uintptr_t NW_WRITE_STRING_OFFSET = 0x757D20;
constexpr uintptr_t SEND_CMD_INTERNAL_OFFSET = 0x13200C0;
constexpr uintptr_t NB_GET_NETID_OFFSET = 0x1321FB0;

constexpr uintptr_t PLAYER_KICK_OFFSET = 0x476040;
constexpr uintptr_t PLAYERPROXY_KICK_OFFSET = 0x4CBDE0;

constexpr uintptr_t KCP_CLIENT_RAWINPUT_OFFSET = 0x1164330;  // KcpClient::RawInput
constexpr uintptr_t KCP_CLIENT_RAWSEND_OFFSET = 0x11648A0;  // KcpClient::Send  
constexpr uintptr_t KCP_CLIENT_RAWRECV_OFFSET = 0x1164730;  // KcpClient::RawReceive
constexpr uintptr_t KCP_PEER_SENDDATA_OFFSET = 0x1166160;  // KcpPeer::SendData
constexpr uintptr_t KCP_PEER_TICKINCOMING_OFFSET = 0x1167040;  // KcpPeer::TickIncoming
constexpr uintptr_t KCP_PEER_DISCONNECT_OFFSET = 0x1164DA0;  // KcpPeer::Disconnect
constexpr uintptr_t KCP_PEER_HANDLEPING_OFFSET = 0x11653E0;
constexpr uintptr_t KCP_PEER_SENDPING_OFFSET = 0x11666B0;
constexpr uintptr_t KCP_PEER_HANDLETIMEOUT_OFFSET = 0x1165430;
constexpr uintptr_t KCP_PEER_TICKOUTGOING_OFFSET = 0x1167140;
constexpr uintptr_t KCP_TRANSPORT_CLIENT_EARLYUPDATE_OFFSET = 0x1342950;
constexpr uintptr_t KCP_TRANSPORT_CLIENT_LATEUPDATE_OFFSET = 0x13429A0;

// ==================== HOOKFUNCTION FULL IMPLEMENTATION ====================
// MoonSharp VM globals
void* g_MsScript = nullptr;
void* g_MsGlobals = nullptr;
bool g_MsReady = false;
// Offsets
constexpr uintptr_t MS_CALLBACK_INVOKE_OFFSET = 0x317AF0;
constexpr uintptr_t MS_CBARGS_GETITEM_OFFSET = 0x317680;
constexpr uintptr_t MS_CALL_DV_OFFSET = 0x32D3C0;
constexpr uintptr_t MS_DYNVALUE_NEWNIL_OFFSET = 0x31A480;
constexpr uintptr_t MS_DYNVALUE_NEWCB_OFFSET = 0x31A000; // NewCallback(CallbackFunction*)
constexpr uintptr_t MS_TABLE_SET_STR_OFFSET = 0x332FE0;
constexpr uintptr_t MS_TABLE_GET_STR_OFFSET = 0x331940;

// Struct Offsets
constexpr uintptr_t DYNVALUE_OBJECT_OFFSET = 0x28;  // DynValue.m_Object
constexpr uintptr_t CBFUNC_DELEGATE_OFFSET = 0x18;  // CallbackFunction.m_CallBack
constexpr uintptr_t DELEGATE_METHOD_CODE_OFFSET = 0x40;  // Delegate.method_code

// Types
typedef void* MsDynValue;
typedef void* MsScript;
typedef void* MsTable;

typedef MsDynValue(__fastcall* MS_CallbackInvoke_t)(void*, void*, void*, bool, void*);
typedef MsDynValue(__fastcall* MS_CBArgs_GetItem_t)(void*, int, void*);
typedef MsDynValue(__fastcall* MS_Call_DV_t)(MsScript, MsDynValue, void*);
typedef MsDynValue(__fastcall* MS_DynValue_NewNil_t)(void*);
typedef MsDynValue(__fastcall* MS_DynValue_NewCB_t)(void* cbFunc, void*);
typedef void(__fastcall* MS_Table_Set_Str_t)(void*, Il2CppString*, MsDynValue, void*);
typedef MsDynValue(__fastcall* MS_Table_Get_Str_t)(void*, Il2CppString*, void*);

// Globals
MS_CallbackInvoke_t   MS_CallbackInvoke = nullptr;
MS_CBArgs_GetItem_t   MS_CBArgs_GetItem = nullptr;
MS_Call_DV_t          MS_Call_DV = nullptr;
MS_DynValue_NewNil_t  MS_DynValue_NewNil = nullptr;
MS_DynValue_NewCB_t   MS_DynValue_NewCB = nullptr;
MS_Table_Set_Str_t    MS_Table_Set_Str = nullptr;
MS_Table_Get_Str_t    MS_Table_Get_Str = nullptr;

void* g_InvokeAddr = nullptr;
BYTE g_InvokeOrig[14];
bool g_InvokeHooked = false;
CRITICAL_SECTION g_HooksCS;

// Hook storage
struct HookInfo {
    MsDynValue hookClosure;
    void* originalMethodCode;
    bool enabled;
};
std::unordered_map<void*, HookInfo> g_Hooks;

constexpr uintptr_t NW_BUFFER_OFFSET = 0x10;
constexpr uintptr_t NW_POSITION_OFFSET = 0x18;

constexpr uintptr_t ARRAY_LENGTH_OFFSET = 0x18;
constexpr uintptr_t ARRAY_FIRST_ELEMENT_OFFSET = 0x20;
constexpr uintptr_t STRING_LENGTH_OFFSET = 0x10;
constexpr uintptr_t STRING_CHARS_OFFSET = 0x14;

// ==================== GUI ====================
HWND g_Window = nullptr;
HWND g_TabControl = nullptr;
HWND g_TreeView = nullptr;
HWND g_PropertyList = nullptr;
HWND g_NameEdit = nullptr;
HWND g_ScriptEdit = nullptr;
HWND g_ExecuteBtn = nullptr;
HWND g_ClearBtn = nullptr;
HWND g_LoadFileBtn = nullptr;
HWND g_ScriptStatus = nullptr;
HWND g_LogBox = nullptr;
HWND g_CmdOutput = nullptr;
HWND g_CmdInput = nullptr;
HWND g_CmdSendBtn = nullptr;
HWND g_ScriptTabControl = nullptr;
HWND g_AddTabBtn = nullptr;
HWND g_CloseTabBtn = nullptr;

#define ID_TABCONTROL 100
#define ID_TREEVIEW 101
#define ID_PROPERTYLIST 102
#define ID_REFRESH 103
#define ID_DELETE 104
#define ID_CLONE 105
#define ID_NAMEEDIT 107
#define ID_SETNAME 108
#define ID_SCRIPTEDIT 120
#define ID_EXECUTE 121
#define ID_CLEAR 122
#define ID_LOADFILE 124
#define ID_SCRIPTSTATUS 123
#define ID_LOGBOX 106
#define ID_CMD_OUTPUT 140
#define ID_CMD_INPUT 141
#define ID_CMD_SEND 142
#define ID_COPYPATH 111

// ==================== SCRIPT TABS ====================
#define MAX_SCRIPT_TABS 16
#define ID_SCRIPTTAB    300
#define ID_ADDTAB       301
#define ID_CLOSETAB     302


char g_ElytraDir[MAX_PATH] = {};
char g_ScriptsDir[MAX_PATH] = {};
char g_TabsDir[MAX_PATH] = {};

void InitDirectories() {
    char appdata[MAX_PATH] = {};
    if (!GetEnvironmentVariableA("APPDATA", appdata, MAX_PATH)) {
        strcpy_s(appdata, "C:\\");
    }

    snprintf(g_ElytraDir, MAX_PATH, "%s\\Elytra", appdata);
    snprintf(g_ScriptsDir, MAX_PATH, "%s\\scripts", g_ElytraDir);
    snprintf(g_TabsDir, MAX_PATH, "%s\\tabs", g_ElytraDir);

    CreateDirectoryA(g_ElytraDir, nullptr);
    CreateDirectoryA(g_ScriptsDir, nullptr);
    CreateDirectoryA(g_TabsDir, nullptr);
}

#define ID_SCRIPTLIST    320
#define ID_SCRIPTLIST_LOAD 321
#define ID_SCRIPTLIST_REFRESH 322
#define ID_SCRIPTLIST_OPENFOLDER 323

HWND g_ScriptListBox = nullptr;
HWND g_ScriptListLoadBtn = nullptr;
HWND g_ScriptListRefreshBtn = nullptr;
HWND g_ScriptListOpenBtn = nullptr;

#define ID_PREVTAB 303
#define ID_NEXTTAB 304

HWND g_PrevTabBtn = nullptr;
HWND g_NextTabBtn = nullptr;

struct ScriptFile {
    char filename[MAX_PATH];
    char fullpath[MAX_PATH];
};

ScriptFile g_ScriptFiles[256];
int g_ScriptFileCount = 0;

void RefreshScriptList() {
    if (!g_ScriptListBox) return;
    SendMessage(g_ScriptListBox, LB_RESETCONTENT, 0, 0);
    g_ScriptFileCount = 0;

    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\*.lua", g_ScriptsDir);

    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        if (g_ScriptFileCount >= 256) break;

        auto& sf = g_ScriptFiles[g_ScriptFileCount];
        strcpy_s(sf.filename, fd.cFileName);
        snprintf(sf.fullpath, MAX_PATH, "%s\\%s", g_ScriptsDir, fd.cFileName);

        // Показываем размер файла рядом с именем
        char display[MAX_PATH + 32];
        if (fd.nFileSizeLow > 1024)
            snprintf(display, sizeof(display), "%s  (%d KB)", fd.cFileName, fd.nFileSizeLow / 1024);
        else
            snprintf(display, sizeof(display), "%s  (%d B)", fd.cFileName, fd.nFileSizeLow);

        SendMessageA(g_ScriptListBox, LB_ADDSTRING, 0, (LPARAM)display);
        g_ScriptFileCount++;
    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
}


struct ScriptTab {
    char title[64];
    char* buffer;
    int bufferSize;
    bool fromFile;
    char filePath[MAX_PATH];
};

ScriptTab g_ScriptTabs[MAX_SCRIPT_TABS];
int g_ScriptTabCount = 0;
int g_CurrentScriptTab = 0;

// ==================== TELEPATHY OFFSETS ====================
constexpr uintptr_t TELE_RECV_ENQUEUE_OFFSET = 0x18D4070;  // MagnificentReceivePipe::Enqueue
constexpr uintptr_t TELE_SEND_ENQUEUE_OFFSET = 0x18D4FF0;  // MagnificentSendPipe::Enqueue
constexpr uintptr_t TELE_CLIENT_DISCONNECT_OFFSET = 0x18D2E90;  // Client::Disconnect
constexpr uintptr_t TELE_CLIENT_SEND_OFFSET = 0x18D3430;  // Client::Send
constexpr uintptr_t TELE_CLIENT_TICK_OFFSET = 0x18D3740;  // Client::Tick
constexpr uintptr_t TELE_CLIENT_CONNECTED_OFFSET = 0x18D38F0;  // Client::get_Connected

// ==================== TELEPATHY STATE ====================
bool g_TcpSnifferEnabled = false;
bool g_TcpDropDisconnect = false;
bool g_TcpDropAllIncoming = false;
bool g_TcpDropOutgoing = false;

uint64_t g_TcpBytesSent = 0;
uint64_t g_TcpBytesRecv = 0;
uint32_t g_TcpPktSentPerSec = 0;
uint32_t g_TcpPktRecvPerSec = 0;
uint32_t g_TcpSentCounter = 0;
uint32_t g_TcpRecvCounter = 0;
DWORD g_TcpLastStatsTick = 0;

void* g_TeleClientInstance = nullptr;

// Blocked Mirror message IDs
uint16_t g_BlockedMsgIds[32];
int g_BlockedMsgIdCount = 0;

bool IsMsgIdBlocked(uint16_t msgId) {
    for (int i = 0; i < g_BlockedMsgIdCount; i++)
        if (g_BlockedMsgIds[i] == msgId) return true;
    return false;
}

void UpdateTcpStats() {
    DWORD now = GetTickCount();
    if (now - g_TcpLastStatsTick >= 1000) {
        g_TcpPktSentPerSec = g_TcpSentCounter;
        g_TcpPktRecvPerSec = g_TcpRecvCounter;
        g_TcpSentCounter = 0;
        g_TcpRecvCounter = 0;
        g_TcpLastStatsTick = now;
    }
}

// ==================== MIRROR MSG LOOKUP ====================
struct MirrorMsgInfo { uint16_t id; const char* name; };

MirrorMsgInfo g_KnownMsgs[] = {
    {0x0001, "ReadyMessage"},
    {0x0002, "NotReadyMessage"},
    {0x0003, "AddPlayerMessage"},
    {0x0004, "SceneMessage"},
    {0x0005, "CommandMessage"},
    {0x0006, "RpcMessage"},
    {0x0007, "SpawnMessage"},
    {0x0008, "ObjectSpawnStarted"},
    {0x0009, "ObjectSpawnFinished"},
    {0x000A, "ObjectDestroy"},
    {0x000B, "ObjectHide"},
    {0x000C, "EntityState"},
    {0x000D, "ChangeOwner"},
    {0x000E, "NetworkPingMessage"},
    {0x000F, "NetworkPongMessage"},
    {0x0010, "TimeSnapshotMessage"},
    {0, nullptr}
};

const char* LookupMirrorMsg(uint16_t id) {
    for (int i = 0; g_KnownMsgs[i].name; i++)
        if (g_KnownMsgs[i].id == id) return g_KnownMsgs[i].name;
    return nullptr;
}

// ==================== HOOK: MagnificentReceivePipe::Enqueue ====================
// void Enqueue(int connectionId, int eventType, ArraySegment<byte> data)
// EventType: 0=Connected, 1=Data, 2=Disconnected

typedef void(__fastcall* RecvPipe_Enqueue_t)(
    void* self, int connectionId, int eventType, void* segmentPtr);

void* g_RecvEnqueueAddr = nullptr;
BYTE g_RecvEnqueueOrig[14];
bool g_RecvEnqueueHooked = false;


struct InstanceInfo { void* ptr; char name[128]; char className[64]; HTREEITEM treeItem; };
std::map<HTREEITEM, InstanceInfo> g_Instances;
void* g_SelectedInstance = nullptr;

typedef void(__fastcall* HandleRemoteCall_t)(
    void* self, uint8_t componentIndex, uint16_t functionHash,
    int remoteCallType, void* reader, void* conn);

typedef void(__fastcall* ConnDisconnect_t)(void* self);
typedef bool(__fastcall* ConnIsAlive_t)(void* self, float timeout);
typedef void(__fastcall* DelayedDisconnect_t)(void* self, void* conn, float delay);
typedef void(__fastcall* DeserializeClient_t)(void* self, void* reader, bool initialState);

constexpr uintptr_t USERCODE_DISCONNECT_RPC_OFFSET = 0x480EA0;
constexpr uintptr_t PLAYER_DELAYED_DISCONNECT_OFFSET = 0x4708D0;
constexpr uintptr_t PTNETMGR_CLIENT_DISCONNECT_OFFSET = 0x432920;
constexpr uintptr_t SHOW_DISCONNECT_MSG_OFFSET = 0x50FE40;
constexpr uintptr_t PT_AUTH_DELAYED_DISC_OFFSET = 0x431CB0;

typedef void(__fastcall* GenericVoid_t)(void* self);
typedef void(__fastcall* GenericVoidStr_t)(void* self, void* str);

void* g_KickRpcAddr = nullptr;
BYTE g_KickRpcOrig[14];
bool g_KickRpcHooked = false;

// ArraySegment<byte> layout in il2cpp:
// +0x00: void* _array (System.Byte[])
// +0x08: int32 _offset
// +0x0C: int32 _count

struct ArraySegment {
    void* array;    // managed byte[]
    int offset;
    int count;
};

// Ring buffer для захвата пакетов
struct RawPacket {
    DWORD timestamp;
    bool isOutgoing;        // true = send, false = receive
    int channel;            // 0 = Reliable, 1 = Unreliable
    int dataSize;
    uint8_t data[1400];     // KCP MTU default = 1200
};

RawPacket g_PacketLog[2048];
int g_PacketLogHead = 0;
int g_PacketLogCount = 0;
bool g_RawSnifferEnabled = false;
bool g_RawLogToConsole = false;

int g_SpeedMultiplier = 1;  // 1 = normal, 2-10 = faster


// Hook: KcpPeer::SendData — КАЖДЫЙ исходящий пакет
typedef void(__fastcall* KcpPeer_SendData_t)(void* self, void* segment, int channel);
void* g_KcpSendDataAddr = nullptr;
BYTE g_KcpSendDataOrig[14];
bool g_KcpSendDataHooked = false;

// Packet filter
bool g_DropOutgoing = false;        // Drop ALL outgoing
bool g_DropOutgoingUnreliable = false;  // Drop only unreliable (movement)

typedef void(__fastcall* KcpClient_RawInput_t)(void* self, void* segment);
void* g_KcpRawInputAddr = nullptr;
BYTE g_KcpRawInputOrig[14];
bool g_KcpRawInputHooked = false;

bool g_DropIncoming = false;
bool g_DropIncomingUnreliable = false;

struct InjectPacket {
    uint8_t data[1400];
    int size;
    int channel;
    bool pending;
};
InjectPacket g_InjectQueue[32];
int g_InjectCount = 0;

// Hook: KcpPeer::Disconnect — prevent transport-level disconnect
typedef void(__fastcall* KcpPeer_Disconnect_t)(void* self);
void* g_KcpDisconnectAddr = nullptr;
BYTE g_KcpDisconnectOrig[14];
bool g_KcpDisconnectHooked = false;

// Hook: KcpPeer::SendDisconnect — prevent client from sending disconnect
constexpr uintptr_t KCP_PEER_SENDDISCONNECT_OFFSET = 0x1166290;
typedef void(__fastcall* KcpPeer_SendDisconnect_t)(void* self);
void* g_KcpSendDiscAddr = nullptr;
BYTE g_KcpSendDiscOrig[14];
bool g_KcpSendDiscHooked = false;

// Stats
uint64_t g_TotalBytesSent = 0;
uint64_t g_TotalBytesRecv = 0;
uint32_t g_PacketsSentPerSec = 0;
uint32_t g_PacketsRecvPerSec = 0;
uint32_t g_PacketsSentCounter = 0;
uint32_t g_PacketsRecvCounter = 0;
DWORD g_LastStatsTick = 0;

void UpdatePacketStats() {
    DWORD now = GetTickCount();
    if (now - g_LastStatsTick >= 1000) {
        g_PacketsSentPerSec = g_PacketsSentCounter;
        g_PacketsRecvPerSec = g_PacketsRecvCounter;
        g_PacketsSentCounter = 0;
        g_PacketsRecvCounter = 0;
        g_LastStatsTick = now;
    }
}

// ---- check if hash is blocked ----
int FindBlockedIndex(uint16_t hash) {
    for (int i = 0; i < g_BlockedCount; i++) {
        if (g_Blocked[i].hash == hash && g_Blocked[i].enabled)
            return i;
    }
    return -1;
}

// ==================== Logging ====================
void Log(const char* fmt, ...) {
    char buf[1024];
    va_list a;
    va_start(a, fmt);
    vsnprintf(buf, sizeof(buf), fmt, a);
    va_end(a);
    if (g_LogBox) {
        int l = GetWindowTextLengthA(g_LogBox);
        SendMessageA(g_LogBox, EM_SETSEL, l, l);
        SendMessageA(g_LogBox, EM_REPLACESEL, 0, (LPARAM)buf);
        SendMessageA(g_LogBox, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        SendMessageA(g_LogBox, EM_SCROLLCARET, 0, 0);
    }
}

void UpdateScriptStatus(const char* s) {
    if (g_ScriptStatus) SetWindowTextA(g_ScriptStatus, s);
}

int AddScriptTab(const char* title, const char* content) {
    if (g_ScriptTabCount >= MAX_SCRIPT_TABS) return -1;

    auto& tab = g_ScriptTabs[g_ScriptTabCount];
    memset(&tab, 0, sizeof(ScriptTab));
    strncpy_s(tab.title, title, 63);

    int contentLen = content ? (int)strlen(content) : 0;
    tab.bufferSize = contentLen + 4096;
    tab.buffer = (char*)calloc(tab.bufferSize, 1);
    if (content && contentLen > 0) {
        strcpy_s(tab.buffer, tab.bufferSize, content);
    }
    tab.fromFile = false;
    tab.filePath[0] = 0;

    TCITEMA tie = {};
    tie.mask = TCIF_TEXT;
    tie.pszText = (LPSTR)title;
    TabCtrl_InsertItem(g_ScriptTabControl, g_ScriptTabCount, &tie);

    return g_ScriptTabCount++;
}

void LoadTabContent(int idx) {
    if (idx < 0 || idx >= g_ScriptTabCount) return;
    SetWindowTextA(g_ScriptEdit, g_ScriptTabs[idx].buffer ? g_ScriptTabs[idx].buffer : "");
    UpdateScriptStatus(g_ScriptTabs[idx].title);
}

void SaveCurrentTabContent() {
    if (g_CurrentScriptTab < 0 || g_CurrentScriptTab >= g_ScriptTabCount) return;
    auto& tab = g_ScriptTabs[g_CurrentScriptTab];

    int len = GetWindowTextLengthA(g_ScriptEdit);
    if (len + 1 > tab.bufferSize) {
        tab.bufferSize = len + 4096;
        tab.buffer = (char*)realloc(tab.buffer, tab.bufferSize);
    }
    if (tab.buffer) {
        GetWindowTextA(g_ScriptEdit, tab.buffer, tab.bufferSize);
    }
}

void RemoveScriptTab(int idx) {
    if (idx < 0 || idx >= g_ScriptTabCount || g_ScriptTabCount <= 1) return;

    // Сначала сохраняем текущий таб если это он
    if (idx == g_CurrentScriptTab) {
        SaveCurrentTabContent();
    }

    // Освобождаем память закрываемого таба
    if (g_ScriptTabs[idx].buffer) {
        free(g_ScriptTabs[idx].buffer);
        g_ScriptTabs[idx].buffer = nullptr;
    }

    // Сдвигаем остальные
    for (int i = idx; i < g_ScriptTabCount - 1; i++) {
        g_ScriptTabs[i] = g_ScriptTabs[i + 1];
    }

    // Обнуляем последний (чтобы не было мусора)
    memset(&g_ScriptTabs[g_ScriptTabCount - 1], 0, sizeof(ScriptTab));

    g_ScriptTabCount--;
    TabCtrl_DeleteItem(g_ScriptTabControl, idx);

    // Корректируем текущий индекс
    if (g_CurrentScriptTab >= g_ScriptTabCount) {
        g_CurrentScriptTab = g_ScriptTabCount - 1;
    }
    else if (g_CurrentScriptTab > idx) {
        g_CurrentScriptTab--;
    }

    TabCtrl_SetCurSel(g_ScriptTabControl, g_CurrentScriptTab);
    LoadTabContent(g_CurrentScriptTab);
}


void SwitchScriptTab(int newIdx) {
    if (newIdx == g_CurrentScriptTab || newIdx < 0 || newIdx >= g_ScriptTabCount) return;
    SaveCurrentTabContent();
    g_CurrentScriptTab = newIdx;
    LoadTabContent(newIdx);
}

void CmdLog(const char* fmt, ...) {
    char buf[1024];
    va_list a;
    va_start(a, fmt);
    vsnprintf(buf, sizeof(buf), fmt, a);
    va_end(a);
    if (g_CmdOutput) {
        int l = GetWindowTextLengthA(g_CmdOutput);
        SendMessageA(g_CmdOutput, EM_SETSEL, l, l);
        SendMessageA(g_CmdOutput, EM_REPLACESEL, 0, (LPARAM)buf);
        SendMessageA(g_CmdOutput, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        SendMessageA(g_CmdOutput, EM_SCROLLCARET, 0, 0);
    }
}

void LogRawPacket(bool outgoing, int channel, const uint8_t* data, int size) {
    if (!g_RawSnifferEnabled) return;

    UpdatePacketStats();

    auto& pkt = g_PacketLog[g_PacketLogHead];
    pkt.timestamp = GetTickCount();
    pkt.isOutgoing = outgoing;
    pkt.channel = channel;
    pkt.dataSize = size > 1400 ? 1400 : size;
    if (data && size > 0)
        memcpy(pkt.data, data, pkt.dataSize);

    g_PacketLogHead = (g_PacketLogHead + 1) % 2048;
    if (g_PacketLogCount < 2048) g_PacketLogCount++;

    if (outgoing) {
        g_TotalBytesSent += size;
        g_PacketsSentCounter++;
    }
    else {
        g_TotalBytesRecv += size;
        g_PacketsRecvCounter++;
    }

    if (g_RawLogToConsole) {
        char hex[128] = {};
        int p = 0;
        int n = size > 32 ? 32 : size;
        for (int i = 0; i < n; i++)
            p += snprintf(hex + p, sizeof(hex) - p, "%02X ", data[i]);
        CmdLog("[%s] ch=%d %d bytes: %s%s",
            outgoing ? "OUT" : " IN", channel, size, hex,
            size > 32 ? "..." : "");
    }
}


// ==================== Safe Functions ====================
static bool SafeReadString(Il2CppString* str, char* out, int size) {
    if (!str || !out) return false;
    __try {
        int len = *(int*)((uintptr_t)str + STRING_LENGTH_OFFSET);
        if (len <= 0 || len >= size) return false;
        wchar_t* chars = (wchar_t*)((uintptr_t)str + STRING_CHARS_OFFSET);
        for (int i = 0; i < len; i++) out[i] = (char)chars[i];
        out[len] = 0;
        return true;
    }
    __except (1) { return false; }
}

static bool SafeGetName(void* inst, char* out, int size) {
    if (!inst || !Instance_get_Name) return false;
    __try { return SafeReadString(Instance_get_Name(inst), out, size); }
    __except (1) { return false; }
}

static bool SafeGetClassName(void* inst, char* out, int size) {
    if (!inst || !Instance_get_ClassName) return false;
    __try { return SafeReadString(Instance_get_ClassName(inst), out, size); }
    __except (1) { return false; }
}

static int SafeGetChildren(void* inst, void** out, int max) {
    if (!inst || !Instance_GetChildren) return 0;
    __try {
        Il2CppArray* arr = Instance_GetChildren(inst);
        if (!arr) return 0;
        int cnt = *(int*)((uintptr_t)arr + ARRAY_LENGTH_OFFSET);
        if (cnt <= 0) return 0;
        void** elems = (void**)((uintptr_t)arr + ARRAY_FIRST_ELEMENT_OFFSET);
        int n = 0;
        for (int i = 0; i < cnt && n < max; i++) {
            if (elems[i]) out[n++] = elems[i];
        }
        return n;
    }
    __except (1) { return 0; }
}

static void* SafeGetLocalPlayer() {
    if (!g_PlayersInstance) return nullptr;
    __try {
        void* lp = *(void**)((uintptr_t)g_PlayersInstance + PLAYERS_LOCALPLAYER_OFFSET);
        return lp;
    }
    __except (1) { return nullptr; }
}

static void* SafeFindGame(Il2CppDomain* dom) {
    if (!il2cpp_domain_get_assemblies || !il2cpp_assembly_get_image ||
        !il2cpp_class_from_name || !il2cpp_class_get_static_field_data)
        return nullptr;
    __try {
        size_t cnt = 0;
        Il2CppAssembly** asms = il2cpp_domain_get_assemblies(dom, &cnt);
        for (size_t i = 0; i < cnt; i++) {
            Il2CppImage* img = il2cpp_assembly_get_image(asms[i]);
            if (!img) continue;
            Il2CppClass* cls = il2cpp_class_from_name(img, "Polytoria.Datamodel", "Game");
            if (!cls) continue;
            void* data = il2cpp_class_get_static_field_data(cls);
            if (!data) continue;
            void* s = *(void**)data;
            if (s) return s;
        }
    }
    __except (1) {}
    return nullptr;
}

static void* SafeGetScriptService() {
    if (ScriptService_get_Instance) {
        __try {
            void* inst = ScriptService_get_Instance();
            if (inst) return inst;
        }
        __except (1) {}
    }
    return nullptr;
}

// ==================== File Loading ====================
std::string OpenFileDialog(HWND parent) {
    char filename[MAX_PATH] = { 0 };
    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = parent;
    ofn.lpstrFilter = "Lua Files (*.lua)\0*.lua\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
    ofn.lpstrTitle = "Load Lua File";
    if (GetOpenFileNameA(&ofn)) return std::string(filename);
    return "";
}

std::string SaveFileDialog(HWND parent) {
    char filename[MAX_PATH] = "script.lua";
    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = parent;
    ofn.lpstrFilter = "Lua Files (*.lua)\0*.lua\0Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    ofn.lpstrTitle = "Save Script Source";
    if (GetSaveFileNameA(&ofn)) return std::string(filename);
    return "";
}

std::string ReadFileContents(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return "";
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string contents((size_t)size, '\0');
    file.read(&contents[0], size);
    return contents;
}

// ==================== Script Execution ====================
void EnsureScriptService() {
    if (g_ScriptService) return;

    // Пробуем получить ScriptService
    g_ScriptService = SafeGetScriptService();
    if (g_ScriptService) {
        Log("[+] Parent @ 0x%p", g_ScriptService);
        return;
    }

    // Fallback на Game
    if (!g_GameSingleton) {
        g_GameSingleton = SafeFindGame(g_Domain);
    }
    if (g_GameSingleton) {
        g_ScriptService = g_GameSingleton;
        Log("[!] Using Environment as fallback @ 0x%p", g_ScriptService);
    }
}

// ==================== NetMessage Dict Dump ====================
static void DumpDict_StringString(void* dict, const char* label) {
    if (!dict) return;
    __try {
        void* ea = *(void**)((uintptr_t)dict + 0x18);
        int count = *(int*)((uintptr_t)dict + 0x20);
        if (!ea || count <= 0) return;
        int al = *(int*)((uintptr_t)ea + 0x18);
        uintptr_t data = (uintptr_t)ea + 0x20;
        int logged = 0;
        for (int i = 0; i < al && logged < count; i++) {
            uintptr_t e = data + (uintptr_t)i * 0x18;
            if (*(int*)(e) < 0) continue;
            void* k = *(void**)(e + 0x08);
            void* v = *(void**)(e + 0x10);
            char kb[128] = {}, vb[256] = {};
            SafeReadString((Il2CppString*)k, kb, 128);
            SafeReadString((Il2CppString*)v, vb, 256);
            CmdLog("    [%s] \"%s\" = \"%s\"", label, kb, vb);
            logged++;
        }
    }
    __except (1) {}
}

static void DumpDict_StringInt(void* dict, const char* label) {
    if (!dict) return;
    __try {
        void* ea = *(void**)((uintptr_t)dict + 0x18);
        int count = *(int*)((uintptr_t)dict + 0x20);
        if (!ea || count <= 0) return;
        int al = *(int*)((uintptr_t)ea + 0x18);
        uintptr_t data = (uintptr_t)ea + 0x20;
        int logged = 0;
        for (int i = 0; i < al && logged < count; i++) {
            uintptr_t e = data + (uintptr_t)i * 0x18;
            if (*(int*)(e) < 0) continue;
            void* k = *(void**)(e + 0x08);
            int v = *(int*)(e + 0x10);
            char kb[128] = {};
            SafeReadString((Il2CppString*)k, kb, 128);
            CmdLog("    [%s] \"%s\" = %d", label, kb, v);
            logged++;
        }
    }
    __except (1) {}
}

static void DumpDict_StringFloat(void* dict, const char* label) {
    if (!dict) return;
    __try {
        void* ea = *(void**)((uintptr_t)dict + 0x18);
        int count = *(int*)((uintptr_t)dict + 0x20);
        if (!ea || count <= 0) return;
        int al = *(int*)((uintptr_t)ea + 0x18);
        uintptr_t data = (uintptr_t)ea + 0x20;
        int logged = 0;
        for (int i = 0; i < al && logged < count; i++) {
            uintptr_t e = data + (uintptr_t)i * 0x18;
            if (*(int*)(e) < 0) continue;
            void* k = *(void**)(e + 0x08);
            float v = *(float*)(e + 0x10);
            char kb[128] = {};
            SafeReadString((Il2CppString*)k, kb, 128);
            CmdLog("    [%s] \"%s\" = %.4f", label, kb, v);
            logged++;
        }
    }
    __except (1) {}
}

static void DumpDict_StringBool(void* dict, const char* label) {
    if (!dict) return;
    __try {
        void* ea = *(void**)((uintptr_t)dict + 0x18);
        int count = *(int*)((uintptr_t)dict + 0x20);
        if (!ea || count <= 0) return;
        int al = *(int*)((uintptr_t)ea + 0x18);
        uintptr_t data = (uintptr_t)ea + 0x20;
        int logged = 0;
        for (int i = 0; i < al && logged < count; i++) {
            uintptr_t e = data + (uintptr_t)i * 0x18;
            if (*(int*)(e) < 0) continue;
            void* k = *(void**)(e + 0x08);
            bool v = *(bool*)(e + 0x10);
            char kb[128] = {};
            SafeReadString((Il2CppString*)k, kb, 128);
            CmdLog("    [%s] \"%s\" = %s", label, kb, v ? "true" : "false");
            logged++;
        }
    }
    __except (1) {}
}

static void DumpDict_StringVec2(void* dict, const char* label) {
    if (!dict) return;
    __try {
        void* ea = *(void**)((uintptr_t)dict + 0x18);
        int count = *(int*)((uintptr_t)dict + 0x20);
        if (!ea || count <= 0) return;
        int al = *(int*)((uintptr_t)ea + 0x18);
        uintptr_t data = (uintptr_t)ea + 0x20;
        int logged = 0;
        for (int i = 0; i < al && logged < count; i++) {
            uintptr_t e = data + (uintptr_t)i * 0x18;
            if (*(int*)(e) < 0) continue;
            void* k = *(void**)(e + 0x08);
            float x = *(float*)(e + 0x10), y = *(float*)(e + 0x14);
            char kb[128] = {};
            SafeReadString((Il2CppString*)k, kb, 128);
            CmdLog("    [%s] \"%s\" = (%.2f, %.2f)", label, kb, x, y);
            logged++;
        }
    }
    __except (1) {}
}

static void DumpDict_StringVec3(void* dict, const char* label) {
    if (!dict) return;
    __try {
        void* ea = *(void**)((uintptr_t)dict + 0x18);
        int count = *(int*)((uintptr_t)dict + 0x20);
        if (!ea || count <= 0) return;
        int al = *(int*)((uintptr_t)ea + 0x18);
        uintptr_t data = (uintptr_t)ea + 0x20;
        int logged = 0;
        for (int i = 0; i < al && logged < count; i++) {
            uintptr_t e = data + (uintptr_t)i * 0x20;
            if (*(int*)(e) < 0) continue;
            void* k = *(void**)(e + 0x08);
            float x = *(float*)(e + 0x10), y = *(float*)(e + 0x14), z = *(float*)(e + 0x18);
            char kb[128] = {};
            SafeReadString((Il2CppString*)k, kb, 128);
            CmdLog("    [%s] \"%s\" = (%.2f, %.2f, %.2f)", label, kb, x, y, z);
            logged++;
        }
    }
    __except (1) {}
}

static void LogNetMessage(void* msg, const char* eventName, const char* method) {
    if (!msg) {
        CmdLog("[ELOGGER] %s.%s() - msg=NULL", eventName, method);
        return;
    }
    CmdLog("[ELOGGER] === %s.%s() === NetMessage @ 0x%p", eventName, method, msg);
    __try {
        DumpDict_StringString(*(void**)((uintptr_t)msg + NETMSG_STRINGS_OFFSET), "string");
        DumpDict_StringInt(*(void**)((uintptr_t)msg + NETMSG_INTS_OFFSET), "int");
        DumpDict_StringFloat(*(void**)((uintptr_t)msg + NETMSG_NUMBERS_OFFSET), "number");
        DumpDict_StringBool(*(void**)((uintptr_t)msg + NETMSG_BOOLS_OFFSET), "bool");
        DumpDict_StringVec2(*(void**)((uintptr_t)msg + NETMSG_VEC2S_OFFSET), "vec2");
        DumpDict_StringVec3(*(void**)((uintptr_t)msg + NETMSG_VEC3S_OFFSET), "vec3");
    }
    __except (1) {
        CmdLog("[ELOGGER] Failed to read NetMessage");
    }
    CmdLog("[ELOGGER] === END ===");
}

// ==================== Hooks ====================
static void PatchBytes(void* addr, const BYTE* patch, size_t len) {
    DWORD old;
    VirtualProtect(addr, len, PAGE_EXECUTE_READWRITE, &old);
    memcpy(addr, patch, len);
    VirtualProtect(addr, len, old, &old);
    FlushInstructionCache(GetCurrentProcess(), addr, len);
}

static void InstallHook(void* target, void* hook, BYTE* orig) {
    DWORD old;
    VirtualProtect(target, 14, PAGE_EXECUTE_READWRITE, &old);
    memcpy(orig, target, 14);
    BYTE jmp[14] = { 0xFF, 0x25, 0, 0, 0, 0 };
    *(void**)(jmp + 6) = hook;
    memcpy(target, jmp, 14);
    VirtualProtect(target, 14, old, &old);
    FlushInstructionCache(GetCurrentProcess(), target, 14);
}

static void RemoveHook(void* target, BYTE* orig) {
    PatchBytes(target, orig, 14);
}


// ==================== GLOBAL INVOKE HOOK ====================
MsDynValue __fastcall Hook_CallbackInvoke(
    void* cbFunc, void* execCtx, void* args, bool isMethodCall, void* method)
{
    EnterCriticalSection(&g_HooksCS);
    auto it = g_Hooks.find(cbFunc);
    HookInfo* hook = (it != g_Hooks.end() && it->second.enabled) ? &it->second : nullptr;
    MsDynValue hookClosure = hook ? hook->hookClosure : nullptr;
    LeaveCriticalSection(&g_HooksCS);

    // Not hooked - call original
    if (!hookClosure) {
        RemoveHook(g_InvokeAddr, g_InvokeOrig);
        MsDynValue result = nullptr;
        __try { result = MS_CallbackInvoke(cbFunc, execCtx, args, isMethodCall, method); }
        __except (1) {}
        InstallHook(g_InvokeAddr, &Hook_CallbackInvoke, g_InvokeOrig);
        return result;
    }

    // === HOOKED ===
    RemoveHook(g_InvokeAddr, g_InvokeOrig);
    MsDynValue result = nullptr;

    __try {
        MsScript script = nullptr;
        __try {
            void* processor = *(void**)((uintptr_t)execCtx + 0x10);
            if (processor) script = *(void**)((uintptr_t)processor + 0x20);
        }
        __except (1) {}

        if (script && hookClosure) {
            result = MS_Call_DV(script, hookClosure, nullptr);
        }
    }
    __except (1) {}

    InstallHook(g_InvokeAddr, &Hook_CallbackInvoke, g_InvokeOrig);
    return result;
}

// ==================== NATIVE IMPL ====================
MsDynValue __fastcall Native_HookFunction_Impl(
    void* execCtx, void* cbArgs, void* method)
{
    MsDynValue arg0 = MS_CBArgs_GetItem(cbArgs, 0, nullptr);
    MsDynValue arg1 = MS_CBArgs_GetItem(cbArgs, 1, nullptr);

    if (!arg0 || !arg1) return MS_DynValue_NewNil(nullptr);

    void* originalCbFunc = nullptr;
    __try {
        originalCbFunc = *(void**)((uintptr_t)arg0 + DYNVALUE_OBJECT_OFFSET);
    }
    __except (1) { return MS_DynValue_NewNil(nullptr); }

    if (!originalCbFunc) return MS_DynValue_NewNil(nullptr);

    EnterCriticalSection(&g_HooksCS);

    auto it = g_Hooks.find(originalCbFunc);
    if (it != g_Hooks.end()) {
        it->second.hookClosure = arg1;
        LeaveCriticalSection(&g_HooksCS);
        return arg0;
    }

    HookInfo hi;
    hi.hookClosure = arg1;
    hi.enabled = true;
    hi.originalMethodCode = nullptr;

    __try {
        void* delegate = *(void**)((uintptr_t)originalCbFunc + CBFUNC_DELEGATE_OFFSET);
        if (delegate) {
            hi.originalMethodCode = *(void**)((uintptr_t)delegate + DELEGATE_METHOD_CODE_OFFSET);
        }
    }
    __except (1) {}

    g_Hooks[originalCbFunc] = hi;

    if (!g_InvokeHooked) {
        g_InvokeAddr = (void*)((uintptr_t)g_GameAssembly + MS_CALLBACK_INVOKE_OFFSET);
        MS_CallbackInvoke = (MS_CallbackInvoke_t)g_InvokeAddr;
        InstallHook(g_InvokeAddr, &Hook_CallbackInvoke, g_InvokeOrig);
        g_InvokeHooked = true;
    }

    LeaveCriticalSection(&g_HooksCS);
    return arg0;
}

MsDynValue __fastcall Native_UnhookFunction_Impl(
    void* execCtx, void* cbArgs, void* method)
{
    MsDynValue arg0 = MS_CBArgs_GetItem(cbArgs, 0, nullptr);
    if (!arg0) return MS_DynValue_NewNil(nullptr);

    void* cbFunc = nullptr;
    __try { cbFunc = *(void**)((uintptr_t)arg0 + DYNVALUE_OBJECT_OFFSET); }
    __except (1) { return MS_DynValue_NewNil(nullptr); }

    EnterCriticalSection(&g_HooksCS);
    g_Hooks.erase(cbFunc);
    LeaveCriticalSection(&g_HooksCS);

    return MS_DynValue_NewNil(nullptr);
}

// ==================== DELEGATE CLONE ====================
void* CloneDelegateWithFunc(void* originalDelegate, void* newFuncPtr) {
    if (!originalDelegate || !newFuncPtr) return nullptr;
    __try {
        void* klass = *(void**)((uintptr_t)originalDelegate);
        void* newDelegate = il2cpp_object_new(klass);
        if (!newDelegate) return nullptr;
        memcpy((void*)((uintptr_t)newDelegate + 0x08), (void*)((uintptr_t)originalDelegate + 0x08), 0x40);
        *(void**)((uintptr_t)newDelegate + 0x10) = newFuncPtr;
        *(void**)((uintptr_t)newDelegate + 0x18) = newFuncPtr;
        *(void**)((uintptr_t)newDelegate + 0x20) = nullptr;
        return newDelegate;
    }
    __except (1) { return nullptr; }
}

MsDynValue CreateNativeCallback(void* nativeFuncPtr, const char* name) {
    if (!g_MsGlobals || !nativeFuncPtr) return nullptr;

    MsDynValue printDV = MS_Table_Get_Str(g_MsGlobals, il2cpp_string_new("print"), nullptr);
    if (!printDV) return nullptr;

    void* printCBFunc = *(void**)((uintptr_t)printDV + DYNVALUE_OBJECT_OFFSET);
    if (!printCBFunc) return nullptr;

    void* printDelegate = *(void**)((uintptr_t)printCBFunc + CBFUNC_DELEGATE_OFFSET);
    if (!printDelegate) return nullptr;

    void* newDelegate = CloneDelegateWithFunc(printDelegate, nativeFuncPtr);
    if (!newDelegate) return nullptr;

    void* cbKlass = *(void**)((uintptr_t)printCBFunc);
    void* newCBFunc = il2cpp_object_new(cbKlass);
    if (!newCBFunc) return nullptr;

    memcpy((void*)((uintptr_t)newCBFunc + 0x08), (void*)((uintptr_t)printCBFunc + 0x08), 0x20);
    *(void**)((uintptr_t)newCBFunc + 0x10) = (void*)il2cpp_string_new(name);
    *(void**)((uintptr_t)newCBFunc + 0x18) = newDelegate;

    return MS_DynValue_NewCB(newCBFunc, nullptr);
}

// ==================== INJECT ====================
bool g_NativesInjected = false;

void InjectNativeGlobals() {
    if (!g_MsReady || !g_MsGlobals) return;
    if (g_NativesInjected) return;

    // Init offsets
    uintptr_t b = (uintptr_t)g_GameAssembly;
    MS_CallbackInvoke = (MS_CallbackInvoke_t)(b + MS_CALLBACK_INVOKE_OFFSET);
    MS_CBArgs_GetItem = (MS_CBArgs_GetItem_t)(b + MS_CBARGS_GETITEM_OFFSET);
    MS_Call_DV = (MS_Call_DV_t)(b + MS_CALL_DV_OFFSET);
    MS_DynValue_NewNil = (MS_DynValue_NewNil_t)(b + MS_DYNVALUE_NEWNIL_OFFSET);
    MS_DynValue_NewCB = (MS_DynValue_NewCB_t)(b + MS_DYNVALUE_NEWCB_OFFSET);
    MS_Table_Set_Str = (MS_Table_Set_Str_t)(b + MS_TABLE_SET_STR_OFFSET);
    MS_Table_Get_Str = (MS_Table_Get_Str_t)(b + MS_TABLE_GET_STR_OFFSET);

    InitializeCriticalSection(&g_HooksCS);

    // Inject hookfunction
    MsDynValue hookCB = CreateNativeCallback((void*)&Native_HookFunction_Impl, "hookfunction");
    if (hookCB) {
        MS_Table_Set_Str(g_MsGlobals, il2cpp_string_new("hookfunction"), hookCB, nullptr);
        Log("[+] hookfunction injected");
    }

    MsDynValue unhookCB = CreateNativeCallback((void*)&Native_UnhookFunction_Impl, "unhookfunction");
    if (unhookCB) {
        MS_Table_Set_Str(g_MsGlobals, il2cpp_string_new("unhookfunction"), unhookCB, nullptr);
        Log("[+] unhookfunction injected");
    }

    g_NativesInjected = true;
}

bool g_HookFuncsInjected = false;

void InitHookFunctionPointers() {
    uintptr_t b = (uintptr_t)g_GameAssembly;
    MS_CallbackInvoke = (MS_CallbackInvoke_t)(b + MS_CALLBACK_INVOKE_OFFSET);
    MS_CBArgs_GetItem = (MS_CBArgs_GetItem_t)(b + MS_CBARGS_GETITEM_OFFSET);
    MS_Call_DV = (MS_Call_DV_t)(b + MS_CALL_DV_OFFSET);
    MS_DynValue_NewNil = (MS_DynValue_NewNil_t)(b + MS_DYNVALUE_NEWNIL_OFFSET);
    MS_DynValue_NewCB = (MS_DynValue_NewCB_t)(b + MS_DYNVALUE_NEWCB_OFFSET);
    MS_Table_Set_Str = (MS_Table_Set_Str_t)(b + MS_TABLE_SET_STR_OFFSET);
    MS_Table_Get_Str = (MS_Table_Get_Str_t)(b + MS_TABLE_GET_STR_OFFSET);
}

void EnsureHookFunctionsInjected() {
    if (g_HookFuncsInjected) return;
    if (!g_MsReady || !g_MsGlobals) return; // VM еще не захвачена

    InitHookFunctionPointers();
    InitializeCriticalSection(&g_HooksCS);

    MsDynValue hookCB = CreateNativeCallback((void*)&Native_HookFunction_Impl, "hookfunction");
    if (hookCB) {
        MS_Table_Set_Str(g_MsGlobals, il2cpp_string_new("hookfunction"), hookCB, nullptr);
        Log("[+] hookfunction injected into Lua!");
    }
    else {
        Log("[-] hookfunction injection failed");
    }

    MsDynValue unhookCB = CreateNativeCallback((void*)&Native_UnhookFunction_Impl, "unhookfunction");
    if (unhookCB) {
        MS_Table_Set_Str(g_MsGlobals, il2cpp_string_new("unhookfunction"), unhookCB, nullptr);
    }

    g_HookFuncsInjected = true;
}

void ShutdownHookFunction() {
    if (g_InvokeHooked) {
        RemoveHook(g_InvokeAddr, g_InvokeOrig);
        g_InvokeHooked = false;
    }
    EnterCriticalSection(&g_HooksCS);
    g_Hooks.clear();
    LeaveCriticalSection(&g_HooksCS);
    DeleteCriticalSection(&g_HooksCS);
}

// ==================== NETWORK MONITOR WINDOW ====================
// Отдельное окно с табами для Mirror/KCP трафика, 
// собственным ring buffer и автоскроллом

HWND g_NetMonWindow = nullptr;
HWND g_NetMonListView = nullptr;     // ListView вместо Edit — не лагает на 10000+ строк
HWND g_NetMonStatusBar = nullptr;
HWND g_NetMonFilterEdit = nullptr;
HWND g_NetMonTabControl = nullptr;

// Кнопки
HWND g_NetMonBtnPause = nullptr;
HWND g_NetMonBtnClear = nullptr;
HWND g_NetMonBtnExport = nullptr;
HWND g_NetMonBtnAutoScroll = nullptr;

#define ID_NETMON_LISTVIEW   200
#define ID_NETMON_STATUS     201
#define ID_NETMON_FILTER     202
#define ID_NETMON_TAB        203
#define ID_NETMON_PAUSE      204
#define ID_NETMON_CLEAR      205
#define ID_NETMON_EXPORT     206
#define ID_NETMON_AUTOSCROLL 207
#define ID_NETMON_COPYROW    208

bool g_NetMonPaused = false;
bool g_NetMonAutoScroll = true;
int g_NetMonCurrentTab = 0;  // 0=All, 1=Mirror RPC, 2=KCP Raw, 3=Blocked

// Фильтр
char g_NetMonFilter[128] = {};

// ==================== UNIFIED NET LOG ====================
// Единый лог для всего сетевого — и Mirror, и KCP

enum NetLogType {
    NLOG_MIRROR_RPC_IN = 0,
    NLOG_MIRROR_RPC_OUT,
    NLOG_MIRROR_CMD_OUT,
    NLOG_MIRROR_SYNCVAR,
    NLOG_KCP_RAW_IN,
    NLOG_KCP_RAW_OUT,
    NLOG_KCP_CONTROL,
    NLOG_TCP_IN,          // <-- NEW
    NLOG_TCP_OUT,         // <-- NEW
    NLOG_BLOCKED,
    NLOG_FORGE,
    NLOG_INFO
};

struct NetLogEntry {
    DWORD timestamp;
    NetLogType type;
    uint16_t rpcHash;
    uint32_t netId;
    int dataSize;
    char summary[256];      // готовая строка для отображения
    char rpcName[64];       // resolved name
    char detail[512];       // hex dump или доп. инфо
    bool wasBlocked;
};

// Ring buffer — 8192 записей, не тормозит
constexpr int NETLOG_SIZE = 8192;
NetLogEntry g_NetLog[NETLOG_SIZE];
int g_NetLogHead = 0;
int g_NetLogCount = 0;
CRITICAL_SECTION g_NetLogCS;  // thread safety

void NetLogHex(const uint8_t* data, int size) {
    if (!data || size <= 0) return;
    EnterCriticalSection(&g_NetLogCS);

    int idx = (g_NetLogHead - 1 + NETLOG_SIZE) % NETLOG_SIZE;
    auto& e = g_NetLog[idx];

    int p = 0;
    int n = size > 64 ? 64 : size;
    for (int i = 0; i < n && p < 500; i++)
        p += snprintf(e.detail + p, sizeof(e.detail) - p, "%02X ", data[i]);
    if (size > 64)
        snprintf(e.detail + p, sizeof(e.detail) - p, "... (%d more)", size - 64);

    LeaveCriticalSection(&g_NetLogCS);
}

// ==================== LISTVIEW HELPERS ====================

void NetMonAddColumns() {
    LVCOLUMNA col = {};
    col.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
    col.fmt = LVCFMT_LEFT;

    struct { const char* name; int width; } cols[] = {
        {"#",       45},
        {"Time",    70},
        {"Type",    75},
        {"Dir",     35},
        {"Hash",    55},
        {"Name",   180},
        {"NetID",   50},
        {"Size",    45},
        {"Status",  60},
        {"Summary",350}
    };

    for (int i = 0; i < 10; i++) {
        col.pszText = (LPSTR)cols[i].name;
        col.cx = cols[i].width;
        col.iSubItem = i;
        ListView_InsertColumn(g_NetMonListView, i, &col);
    }
}

const char* NetLogTypeStr(NetLogType t) {
    switch (t) {
    case NLOG_MIRROR_RPC_IN:  return "RPC";
    case NLOG_MIRROR_RPC_OUT: return "RPC";
    case NLOG_MIRROR_CMD_OUT: return "CMD";
    case NLOG_MIRROR_SYNCVAR: return "SyncVar";
    case NLOG_KCP_RAW_IN:    return "KCP";
    case NLOG_KCP_RAW_OUT:   return "KCP";
    case NLOG_KCP_CONTROL:   return "KCP-CTL";
    case NLOG_TCP_IN:        return "TCP";     // <-- NEW
    case NLOG_TCP_OUT:       return "TCP";     // <-- NEW
    case NLOG_BLOCKED:       return "BLOCKED";
    case NLOG_FORGE:         return "FORGE";
    case NLOG_INFO:          return "INFO";
    default:                 return "???";
    }
}

const char* NetLogDirStr(NetLogType t) {
    switch (t) {
    case NLOG_MIRROR_RPC_IN:  return "IN";
    case NLOG_MIRROR_RPC_OUT: return "OUT";
    case NLOG_MIRROR_CMD_OUT: return "OUT";
    case NLOG_KCP_RAW_IN:    return "IN";
    case NLOG_KCP_RAW_OUT:   return "OUT";
    case NLOG_TCP_IN:        return "IN";      // <-- NEW
    case NLOG_TCP_OUT:       return "OUT";     // <-- NEW
    default:                 return "-";
    }
}

bool NetLogMatchesTab(const NetLogEntry& e, int tab) {
    switch (tab) {
    case 0: return true;                                                    // All
    case 1: return e.type <= NLOG_MIRROR_SYNCVAR;                          // Mirror
    case 2: return e.type >= NLOG_KCP_RAW_IN && e.type <= NLOG_KCP_CONTROL; // KCP
    case 3: return e.type == NLOG_TCP_IN || e.type == NLOG_TCP_OUT;        // TCP  <-- NEW
    case 4: return e.wasBlocked;                                            // Blocked
    default: return true;
    }
}

bool NetLogMatchesFilter(const NetLogEntry& e, const char* filter) {
    if (!filter[0]) return true;
    if (strstr(e.summary, filter)) return true;
    if (strstr(e.rpcName, filter)) return true;
    if (strstr(e.detail, filter)) return true;

    // Match hash as hex
    char hashStr[16];
    snprintf(hashStr, sizeof(hashStr), "%04X", e.rpcHash);
    if (strstr(hashStr, filter)) return true;

    return false;
}

// ==================== REFRESH LISTVIEW ====================

int g_NetMonLastCount = 0;  // last synced count

void NetMonRefresh(bool full = false) {
    if (g_NetMonPaused) return;

    EnterCriticalSection(&g_NetLogCS);

    if (full) {
        ListView_DeleteAllItems(g_NetMonListView);
        g_NetMonLastCount = 0;
    }

    // Get filter
    GetWindowTextA(g_NetMonFilterEdit, g_NetMonFilter, 128);

    // Add only new entries
    int startIdx = g_NetMonLastCount;
    int endIdx = g_NetLogCount;

    // Virtual index for ListView
    int lvCount = ListView_GetItemCount(g_NetMonListView);

    for (int i = startIdx; i < endIdx; i++) {
        int realIdx = (g_NetLogHead - g_NetLogCount + i + NETLOG_SIZE) % NETLOG_SIZE;
        auto& e = g_NetLog[realIdx];

        if (!NetLogMatchesTab(e, g_NetMonCurrentTab)) continue;
        if (!NetLogMatchesFilter(e, g_NetMonFilter)) continue;

        char buf[32];

        LVITEMA lvi = {};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = lvCount;

        // #
        snprintf(buf, sizeof(buf), "%d", i);
        lvi.pszText = buf;
        lvi.iSubItem = 0;
        ListView_InsertItem(g_NetMonListView, &lvi);

        // Time (relative seconds)
        static DWORD s_StartTime = 0;
        if (!s_StartTime) s_StartTime = e.timestamp;
        snprintf(buf, sizeof(buf), "%.2f", (e.timestamp - s_StartTime) / 1000.0);
        ListView_SetItemText(g_NetMonListView, lvCount, 1, buf);

        // Type
        ListView_SetItemText(g_NetMonListView, lvCount, 2, (LPSTR)NetLogTypeStr(e.type));

        // Direction
        ListView_SetItemText(g_NetMonListView, lvCount, 3, (LPSTR)NetLogDirStr(e.type));

        // Hash
        if (e.rpcHash) {
            snprintf(buf, sizeof(buf), "0x%04X", e.rpcHash);
            ListView_SetItemText(g_NetMonListView, lvCount, 4, buf);
        }

        // Name
        if (e.rpcName[0])
            ListView_SetItemText(g_NetMonListView, lvCount, 5, (LPSTR)e.rpcName);

        // NetID
        if (e.netId) {
            snprintf(buf, sizeof(buf), "%u", e.netId);
            ListView_SetItemText(g_NetMonListView, lvCount, 6, buf);
        }

        // Size
        if (e.dataSize > 0) {
            snprintf(buf, sizeof(buf), "%d", e.dataSize);
            ListView_SetItemText(g_NetMonListView, lvCount, 7, buf);
        }

        // Status
        ListView_SetItemText(g_NetMonListView, lvCount, 8,
            (LPSTR)(e.wasBlocked ? "BLOCKED" : "PASS"));

        // Summary
        ListView_SetItemText(g_NetMonListView, lvCount, 9, (LPSTR)e.summary);

        lvCount++;
    }

    g_NetMonLastCount = endIdx;

    // Auto-scroll
    if (g_NetMonAutoScroll && lvCount > 0) {
        ListView_EnsureVisible(g_NetMonListView, lvCount - 1, FALSE);
    }

    // Status bar
    char status[256];
    snprintf(status, sizeof(status),
        " Packets: %d | Showing: %d | %s | %s",
        g_NetLogCount, lvCount,
        g_NetMonPaused ? "PAUSED" : "LIVE",
        g_NetMonAutoScroll ? "AutoScroll" : "Manual");
    SetWindowTextA(g_NetMonStatusBar, status);

    LeaveCriticalSection(&g_NetLogCS);
}

// ==================== EXPORT ====================

void NetMonExport() {
    char filename[MAX_PATH] = "elytra_netlog.csv";
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_NetMonWindow;
    ofn.lpstrFilter = "CSV Files (*.csv)\0*.csv\0Text Files (*.txt)\0*.txt\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    ofn.lpstrTitle = "Export Network Log";

    if (!GetSaveFileNameA(&ofn)) return;

    FILE* f = nullptr;
    fopen_s(&f, filename, "w");
    if (!f) { CmdLog("[-] Can't create file"); return; }

    fprintf(f, "Index,Timestamp,Type,Direction,Hash,Name,NetID,Size,Status,Summary,HexDump\n");

    EnterCriticalSection(&g_NetLogCS);
    for (int i = 0; i < g_NetLogCount; i++) {
        int idx = (g_NetLogHead - g_NetLogCount + i + NETLOG_SIZE) % NETLOG_SIZE;
        auto& e = g_NetLog[idx];

        fprintf(f, "%d,%u,%s,%s,0x%04X,\"%s\",%u,%d,%s,\"%s\",\"%s\"\n",
            i, e.timestamp,
            NetLogTypeStr(e.type), NetLogDirStr(e.type),
            e.rpcHash, e.rpcName, e.netId, e.dataSize,
            e.wasBlocked ? "BLOCKED" : "PASS",
            e.summary, e.detail);
    }
    LeaveCriticalSection(&g_NetLogCS);

    fclose(f);
    CmdLog("[+] Exported %d entries to %s", g_NetLogCount, filename);
}

// ==================== DETAIL POPUP ====================

void ShowPacketDetail(int listIndex) {
    // Получаем реальный индекс из первой колонки
    char buf[32] = {};
    ListView_GetItemText(g_NetMonListView, listIndex, 0, buf, 32);
    int logIdx = atoi(buf);

    if (logIdx < 0 || logIdx >= g_NetLogCount) return;

    int realIdx = (g_NetLogHead - g_NetLogCount + logIdx + NETLOG_SIZE) % NETLOG_SIZE;
    auto& e = g_NetLog[realIdx];

    char detail[2048];
    snprintf(detail, sizeof(detail),
        "=== PACKET #%d ===\n"
        "Timestamp: %u (%.2fs)\n"
        "Type: %s\n"
        "Direction: %s\n"
        "RPC Hash: 0x%04X\n"
        "RPC Name: %s\n"
        "NetID: %u\n"
        "Data Size: %d bytes\n"
        "Status: %s\n"
        "\n--- Summary ---\n%s\n"
        "\n--- Hex Dump ---\n%s\n"
        "\n--- Quick Actions ---\n"
        "block 0x%04X %s\n"
        "unblock 0x%04X",
        logIdx, e.timestamp, e.timestamp / 1000.0,
        NetLogTypeStr(e.type), NetLogDirStr(e.type),
        e.rpcHash,
        e.rpcName[0] ? e.rpcName : "(unknown)",
        e.netId, e.dataSize,
        e.wasBlocked ? "BLOCKED" : "PASSED",
        e.summary,
        e.detail[0] ? e.detail : "(no data captured)",
        e.rpcHash, e.rpcName[0] ? e.rpcName : "rpc",
        e.rpcHash);

    MessageBoxA(g_NetMonWindow, detail, "Packet Detail", MB_OK | MB_ICONINFORMATION);
}


// ==================== CREATE WINDOW ====================
LRESULT CALLBACK NetMonWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void CreateNetMonWindow() {
    if (g_NetMonWindow) {
        ShowWindow(g_NetMonWindow, SW_SHOW);
        SetForegroundWindow(g_NetMonWindow);
        return;
    }

    InitializeCriticalSection(&g_NetLogCS);

    // Register class
    WNDCLASSEXA wc = { sizeof(wc) };
    wc.lpfnWndProc = NetMonWndProc;
    wc.hInstance = g_Module;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "ELYTRA_NETMON";
    RegisterClassExA(&wc);

    g_NetMonWindow = CreateWindowExA(
        WS_EX_TOPMOST,
        "ELYTRA_NETMON",
        "Elytra - Network Monitor",
        WS_OVERLAPPEDWINDOW,
        100, 100, 1100, 600,
        nullptr, nullptr, g_Module, nullptr);

    HFONT font = CreateFontA(13, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, "Consolas");
    HFONT fontBold = CreateFontA(13, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, "Segoe UI");

    // Tab control
    g_NetMonTabControl = CreateWindowExA(0, WC_TABCONTROLA, "",
        WS_CHILD | WS_VISIBLE,
        0, 0, 340, 28,
        g_NetMonWindow, (HMENU)ID_NETMON_TAB, g_Module, nullptr);
    SendMessage(g_NetMonTabControl, WM_SETFONT, (WPARAM)fontBold, TRUE);

    TCITEMA tie = {}; tie.mask = TCIF_TEXT;
    tie.pszText = (LPSTR)"All";       TabCtrl_InsertItem(g_NetMonTabControl, 0, &tie);
    tie.pszText = (LPSTR)"Mirror";    TabCtrl_InsertItem(g_NetMonTabControl, 1, &tie);
    tie.pszText = (LPSTR)"KCP";       TabCtrl_InsertItem(g_NetMonTabControl, 2, &tie);
    tie.pszText = (LPSTR)"TCP";       TabCtrl_InsertItem(g_NetMonTabControl, 3, &tie);  // <-- NEW
    tie.pszText = (LPSTR)"Blocked";   TabCtrl_InsertItem(g_NetMonTabControl, 4, &tie);  // <-- WAS 3

    // Filter
    g_NetMonFilterEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
        340, 3, 700, 22,
        g_NetMonWindow, (HMENU)ID_NETMON_FILTER, g_Module, nullptr);
    SendMessage(g_NetMonFilterEdit, WM_SETFONT, (WPARAM)font, TRUE);
    SendMessageA(g_NetMonFilterEdit, EM_SETCUEBANNER, TRUE,
        (LPARAM)L"Filter (hash, name, text...)");

    // ListView
    g_NetMonListView = CreateWindowExA(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEWA, "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
        LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS,
        0, 30, 1080, 500,
        g_NetMonWindow, (HMENU)ID_NETMON_LISTVIEW, g_Module, nullptr);

    SendMessage(g_NetMonListView, WM_SETFONT, (WPARAM)font, TRUE);
    ListView_SetExtendedListViewStyle(g_NetMonListView,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);

    NetMonAddColumns();

    // Bottom buttons
    int y = 570;
    g_NetMonBtnPause = CreateWindowExA(0, "BUTTON", "Pause",
        WS_CHILD | WS_VISIBLE, 5, y, 60, 24,
        g_NetMonWindow, (HMENU)ID_NETMON_PAUSE, g_Module, nullptr);

    g_NetMonBtnClear = CreateWindowExA(0, "BUTTON", "Clear",
        WS_CHILD | WS_VISIBLE, 70, y, 55, 24,
        g_NetMonWindow, (HMENU)ID_NETMON_CLEAR, g_Module, nullptr);

    g_NetMonBtnExport = CreateWindowExA(0, "BUTTON", "Export",
        WS_CHILD | WS_VISIBLE, 130, y, 60, 24,
        g_NetMonWindow, (HMENU)ID_NETMON_EXPORT, g_Module, nullptr);

    g_NetMonBtnAutoScroll = CreateWindowExA(0, "BUTTON", "Scroll:ON",
        WS_CHILD | WS_VISIBLE, 195, y, 80, 24,
        g_NetMonWindow, (HMENU)ID_NETMON_AUTOSCROLL, g_Module, nullptr);

    g_NetMonStatusBar = CreateWindowExA(0, "STATIC", " Ready",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        290, y + 2, 700, 20,
        g_NetMonWindow, (HMENU)ID_NETMON_STATUS, g_Module, nullptr);
    SendMessage(g_NetMonStatusBar, WM_SETFONT, (WPARAM)font, TRUE);

    ShowWindow(g_NetMonWindow, SW_SHOW);
}


void __fastcall Hook_InvokeServer(void* self, void* msg) {
    if (g_EventLoggerEnabled) {
        char n[128] = "?";
        SafeGetName(self, n, 128);
        LogNetMessage(msg, n, "InvokeServer");
    }
    RemoveHook(g_InvokeServerAddr, g_InvokeServerOrig);
    __try {
        ((NetworkEvent_InvokeServer_t)g_InvokeServerAddr)(self, msg);
    }
    __except (1) {}
    InstallHook(g_InvokeServerAddr, &Hook_InvokeServer, g_InvokeServerOrig);
}



typedef void(__fastcall* KcpPeer_HandleTimeout_t)(void* self, uint32_t time);
void* g_HandleTimeoutAddr = nullptr;
BYTE g_HandleTimeoutOrig[14];
bool g_HandleTimeoutHooked = false;

bool g_AntiTimeoutEnabled = false;

void __fastcall Hook_KcpPeer_HandleTimeout(void* self, uint32_t time) {
    if (g_AntiTimeoutEnabled) {
        // Simply don't call — connection never times out
        return;
    }
    RemoveHook(g_HandleTimeoutAddr, g_HandleTimeoutOrig);
    __try { ((KcpPeer_HandleTimeout_t)g_HandleTimeoutAddr)(self, time); }
    __except (1) {}
    InstallHook(g_HandleTimeoutAddr, &Hook_KcpPeer_HandleTimeout, g_HandleTimeoutOrig);
}

// Hook: HandleDeadLink — keep connection alive even when KCP says it's dead
constexpr uintptr_t KCP_PEER_HANDLEDEADLINK_OFFSET = 0x1165310;
typedef void(__fastcall* KcpPeer_HandleDeadLink_t)(void* self);
void* g_HandleDeadLinkAddr = nullptr;
BYTE g_HandleDeadLinkOrig[14];
bool g_HandleDeadLinkHooked = false;

void __fastcall Hook_KcpPeer_HandleDeadLink(void* self) {
    if (g_AntiTimeoutEnabled) {
        return; // Never dead
    }
    RemoveHook(g_HandleDeadLinkAddr, g_HandleDeadLinkOrig);
    __try { ((KcpPeer_HandleDeadLink_t)g_HandleDeadLinkAddr)(self); }
    __except (1) {}
    InstallHook(g_HandleDeadLinkAddr, &Hook_KcpPeer_HandleDeadLink, g_HandleDeadLinkOrig);
}

// Hook: HandleChoked — prevent disconnection when too many packets queue up
constexpr uintptr_t KCP_PEER_HANDLECHOKED_OFFSET = 0x1164E80;
typedef void(__fastcall* KcpPeer_HandleChoked_t)(void* self);
void* g_HandleChokedAddr = nullptr;
BYTE g_HandleChokedOrig[14];
bool g_HandleChokedHooked = false;

void __fastcall Hook_KcpPeer_HandleChoked(void* self) {
    if (g_AntiTimeoutEnabled) {
        return; // Never choked
    }
    RemoveHook(g_HandleChokedAddr, g_HandleChokedOrig);
    __try { ((KcpPeer_HandleChoked_t)g_HandleChokedAddr)(self); }
    __except (1) {}
    InstallHook(g_HandleChokedAddr, &Hook_KcpPeer_HandleChoked, g_HandleChokedOrig);
}

typedef void(__fastcall* KcpPeer_TickOutgoing_t)(void* self);
KcpPeer_TickOutgoing_t KcpPeer_TickOutgoing_Orig = nullptr;

typedef void(__fastcall* KcpTransport_ClientLateUpdate_t)(void* self);
void* g_KcpLateUpdateAddr = nullptr;
BYTE g_KcpLateUpdateOrig[14];
bool g_KcpLateUpdateHooked = false;

void* g_KcpClientInstance = nullptr;  // Cached KcpClient

void __fastcall Hook_KcpTransport_ClientLateUpdate(void* self) {
    // Вызываем оригинал
    RemoveHook(g_KcpLateUpdateAddr, g_KcpLateUpdateOrig);
    __try {
        ((KcpTransport_ClientLateUpdate_t)g_KcpLateUpdateAddr)(self);
    }
    __except (1) {}
    InstallHook(g_KcpLateUpdateAddr, &Hook_KcpTransport_ClientLateUpdate, g_KcpLateUpdateOrig);

    // Extra ticks для speed hack
    if (g_SpeedMultiplier > 1 && g_KcpClientInstance) {
        for (int i = 1; i < g_SpeedMultiplier; i++) {
            __try {
                // KcpClient offset to peer: typically at +0x38 or +0x40
                RemoveHook(g_KcpLateUpdateAddr, g_KcpLateUpdateOrig);
                ((KcpTransport_ClientLateUpdate_t)g_KcpLateUpdateAddr)(self);
                InstallHook(g_KcpLateUpdateAddr, &Hook_KcpTransport_ClientLateUpdate, g_KcpLateUpdateOrig);
            }
            __except (1) { break; }
        }
    }
}



// ==================== RAW PACKET INJECTION ====================

// Replay captured raw packet
void ReplayRawPacket(int index) {
    if (index < 0 || index >= g_PacketLogCount) {
        CmdLog("[-] Invalid packet index");
        return;
    }

    int realIdx = (g_PacketLogHead - g_PacketLogCount + index + 2048) % 2048;
    auto& pkt = g_PacketLog[realIdx];

    if (!pkt.isOutgoing) {
        CmdLog("[-] Can only replay outgoing packets");
        return;
    }

    // Use KcpPeer::SendData to inject
    // Need the KcpPeer instance — discover from KcpClient
    CmdLog("[*] Replaying packet #%d (%d bytes, ch=%d)", index, pkt.dataSize, pkt.channel);

    // TODO: Create ArraySegment and call SendData
    // This requires knowing the KcpClient/KcpPeer instance
}

// Flood — spam packets (use with caution, can crash server)
bool g_FloodEnabled = false;
int g_FloodRate = 100;  // packets per tick

void FloodTick() {
    if (!g_FloodEnabled) return;
    // Send garbage unreliable packets to stress server
    // This is a basic DoS — use responsibly
}

// ==================== BANDWIDTH MONITOR ====================
void PrintBandwidthStats() {
    CmdLog("=== BANDWIDTH ===");
    CmdLog("  Sent: %llu bytes total, %u pkt/s", g_TotalBytesSent, g_PacketsSentPerSec);
    CmdLog("  Recv: %llu bytes total, %u pkt/s", g_TotalBytesRecv, g_PacketsRecvPerSec);
    CmdLog("  Captured: %d packets in buffer", g_PacketLogCount);
}



void* g_PlayerKickAddr = nullptr;
BYTE g_PlayerKickOrig[14];
bool g_PlayerKickHooked = false;

void __fastcall Hook_PlayerKick(void* self, void* reasonStr) {
    if (g_AntiKickEnabled) {
        char reason[256] = "?";
        SafeReadString((Il2CppString*)reasonStr, reason, 256);
        CmdLog("[ANTIKICK] Player::Kick blocked! Reason: \"%s\"", reason);
        return;
    }
    RemoveHook(g_PlayerKickAddr, g_PlayerKickOrig);
    __try { ((GenericVoidStr_t)g_PlayerKickAddr)(self, reasonStr); }
    __except (1) {}
    InstallHook(g_PlayerKickAddr, &Hook_PlayerKick, g_PlayerKickOrig);
}

// Hook 7: PlayerProxy::Kick (Lua kick)
void* g_ProxyKickAddr = nullptr;
BYTE g_ProxyKickOrig[14];
bool g_ProxyKickHooked = false;

void __fastcall Hook_ProxyKick(void* self, void* reasonStr) {
    if (g_AntiKickEnabled) {
        char reason[256] = "?";
        SafeReadString((Il2CppString*)reasonStr, reason, 256);
        CmdLog("[ANTIKICK] Lua Kick blocked! Reason: \"%s\"", reason);
        return;
    }
    RemoveHook(g_ProxyKickAddr, g_ProxyKickOrig);
    __try { ((GenericVoidStr_t)g_ProxyKickAddr)(self, reasonStr); }
    __except (1) {}
    InstallHook(g_ProxyKickAddr, &Hook_ProxyKick, g_ProxyKickOrig);
}

// ================================================================
// HOOK: Disconnect — anti-kick
// ================================================================
void __fastcall Hook_KickRpc(void* self, void* reasonStr) {
    if (g_AntiKickEnabled) {
        char reason[256] = "?";
        SafeReadString((Il2CppString*)reasonStr, reason, 256);
        CmdLog("[ANTIKICK] Kick blocked! Reason: \"%s\"", reason);
        return; // не выполняем = не кикают
    }
    RemoveHook(g_KickRpcAddr, g_KickRpcOrig);
    __try { ((GenericVoidStr_t)g_KickRpcAddr)(self, reasonStr); }
    __except (1) {}
    InstallHook(g_KickRpcAddr, &Hook_KickRpc, g_KickRpcOrig);
}

// Hook 2: Player::DelayedDisconnect — backup
void* g_PlayerDelayDiscAddr = nullptr;
BYTE g_PlayerDelayDiscOrig[14];
bool g_PlayerDelayDiscHooked = false;

void __fastcall Hook_PlayerDelayedDisconnect(void* self) {
    if (g_AntiKickEnabled) {
        CmdLog("[ANTIKICK] Player::DelayedDisconnect blocked");
        return;
    }
    RemoveHook(g_PlayerDelayDiscAddr, g_PlayerDelayDiscOrig);
    __try { ((GenericVoid_t)g_PlayerDelayDiscAddr)(self); }
    __except (1) {}
    InstallHook(g_PlayerDelayDiscAddr, &Hook_PlayerDelayedDisconnect, g_PlayerDelayDiscOrig);
}

// Hook 3: PTNetworkManager::OnClientDisconnect — another path
void* g_ClientDiscAddr = nullptr;
BYTE g_ClientDiscOrig[14];
bool g_ClientDiscHooked = false;

void __fastcall Hook_OnClientDisconnect(void* self) {
    if (g_AntiKickEnabled) {
        CmdLog("[ANTIKICK] OnClientDisconnect blocked");
        return;
    }
    RemoveHook(g_ClientDiscAddr, g_ClientDiscOrig);
    __try { ((GenericVoid_t)g_ClientDiscAddr)(self); }
    __except (1) {}
    InstallHook(g_ClientDiscAddr, &Hook_OnClientDisconnect, g_ClientDiscOrig);
}

// Hook 4: ShowDisconnectMessage — UI
void* g_ShowDiscMsgAddr = nullptr;
BYTE g_ShowDiscMsgOrig[14];
bool g_ShowDiscMsgHooked = false;

void __fastcall Hook_ShowDisconnectMessage(void* self, void* msgStr) {
    if (g_AntiKickEnabled) {
        char msg[256] = "?";
        SafeReadString((Il2CppString*)msgStr, msg, 256);
        CmdLog("[ANTIKICK] ShowDisconnectMessage blocked: \"%s\"", msg);
        return;
    }
    RemoveHook(g_ShowDiscMsgAddr, g_ShowDiscMsgOrig);
    __try { ((GenericVoidStr_t)g_ShowDiscMsgAddr)(self, msgStr); }
    __except (1) {}
    InstallHook(g_ShowDiscMsgAddr, &Hook_ShowDisconnectMessage, g_ShowDiscMsgOrig);
}


void __fastcall Hook_DelayedDisconnect(void* self, void* conn, float delay) {
    if (g_AntiKickEnabled) {
        CmdLog("[ANTIKICK] PTAuth::DelayedDisconnect(%.1fs) blocked", delay);
        return;
    }
    RemoveHook(g_DelayedDiscAddr, g_DelayedDiscOrig);
    __try { ((DelayedDisconnect_t)g_DelayedDiscAddr)(self, conn, delay); }
    __except (1) {}
    InstallHook(g_DelayedDiscAddr, &Hook_DelayedDisconnect, g_DelayedDiscOrig);
}

// Install all anti-kick hooks
void InstallAntiKickHooks() {
    uintptr_t b = (uintptr_t)g_GameAssembly;

    if (!g_KickRpcHooked) {
        g_KickRpcAddr = (void*)(b + USERCODE_DISCONNECT_RPC_OFFSET);
        InstallHook(g_KickRpcAddr, &Hook_KickRpc, g_KickRpcOrig);
        g_KickRpcHooked = true;
    }
    if (!g_PlayerDelayDiscHooked) {
        g_PlayerDelayDiscAddr = (void*)(b + PLAYER_DELAYED_DISCONNECT_OFFSET);
        InstallHook(g_PlayerDelayDiscAddr, &Hook_PlayerDelayedDisconnect, g_PlayerDelayDiscOrig);
        g_PlayerDelayDiscHooked = true;
    }
    if (!g_ClientDiscHooked) {
        g_ClientDiscAddr = (void*)(b + PTNETMGR_CLIENT_DISCONNECT_OFFSET);
        InstallHook(g_ClientDiscAddr, &Hook_OnClientDisconnect, g_ClientDiscOrig);
        g_ClientDiscHooked = true;
    }
    if (!g_ShowDiscMsgHooked) {
        g_ShowDiscMsgAddr = (void*)(b + SHOW_DISCONNECT_MSG_OFFSET);
        InstallHook(g_ShowDiscMsgAddr, &Hook_ShowDisconnectMessage, g_ShowDiscMsgOrig);
        g_ShowDiscMsgHooked = true;
    }
    if (!g_DelayedDiscHooked) {
        g_DelayedDiscAddr = (void*)(b + PT_AUTH_DELAYED_DISC_OFFSET);
        InstallHook(g_DelayedDiscAddr, &Hook_DelayedDisconnect, g_DelayedDiscOrig);
        g_DelayedDiscHooked = true;
    }
    if (!g_PlayerKickHooked) {
        g_PlayerKickAddr = (void*)(b + PLAYER_KICK_OFFSET);
        InstallHook(g_PlayerKickAddr, &Hook_PlayerKick, g_PlayerKickOrig);
        g_PlayerKickHooked = true;
    }
    if (!g_ProxyKickHooked) {
        g_ProxyKickAddr = (void*)(b + PLAYERPROXY_KICK_OFFSET);
        InstallHook(g_ProxyKickAddr, &Hook_ProxyKick, g_ProxyKickOrig);
        g_ProxyKickHooked = true;
    }
}

void RemoveAntiKickHooks() {
    if (g_KickRpcHooked) { RemoveHook(g_KickRpcAddr, g_KickRpcOrig); g_KickRpcHooked = false; }
    if (g_PlayerDelayDiscHooked) { RemoveHook(g_PlayerDelayDiscAddr, g_PlayerDelayDiscOrig); g_PlayerDelayDiscHooked = false; }
    if (g_ClientDiscHooked) { RemoveHook(g_ClientDiscAddr, g_ClientDiscOrig); g_ClientDiscHooked = false; }
    if (g_ShowDiscMsgHooked) { RemoveHook(g_ShowDiscMsgAddr, g_ShowDiscMsgOrig); g_ShowDiscMsgHooked = false; }
    if (g_DelayedDiscHooked) { RemoveHook(g_DelayedDiscAddr, g_DelayedDiscOrig); g_DelayedDiscHooked = false; }
    if (g_PlayerKickHooked) { RemoveHook(g_PlayerKickAddr, g_PlayerKickOrig); g_PlayerKickHooked = false; }
    if (g_ProxyKickHooked) { RemoveHook(g_ProxyKickAddr, g_ProxyKickOrig); g_ProxyKickHooked = false; }
}

// IsAlive — always alive
void* g_IsAliveAddr = nullptr;
BYTE g_IsAliveOrig[14];
bool g_IsAliveHooked = false;

bool __fastcall Hook_IsAlive(void* self, float timeout) {
    if (g_AntiKickEnabled) return true;
    RemoveHook(g_IsAliveAddr, g_IsAliveOrig);
    bool r = true;
    __try { r = ((ConnIsAlive_t)g_IsAliveAddr)(self, timeout); }
    __except (1) {}
    InstallHook(g_IsAliveAddr, &Hook_IsAlive, g_IsAliveOrig);
    return r;
}




// ================================================================
// ==================== RPC NAME RESOLVER =========================
// ================================================================

typedef bool(__cdecl* GetFunctionMethodName_t)(uint16_t hash, Il2CppString** outName);
typedef bool(__cdecl* CommandRequiresAuthority_t)(uint16_t hash);

constexpr uintptr_t GET_FUNC_NAME_OFFSET = 0x136BF40;
constexpr uintptr_t CMD_REQUIRES_AUTH_OFFSET = 0x136BDB0;

GetFunctionMethodName_t GetFunctionMethodName = nullptr;
CommandRequiresAuthority_t CommandRequiresAuthority = nullptr;

// Cache
struct RpcNameEntry {
    uint16_t hash;
    char name[128];
    bool requiresAuth;
};
RpcNameEntry g_RpcNames[1024];
int g_RpcNameCount = 0;

const char* ResolveRpcHash(uint16_t hash) {
    // Check cache
    for (int i = 0; i < g_RpcNameCount; i++) {
        if (g_RpcNames[i].hash == hash) return g_RpcNames[i].name;
    }

    if (!GetFunctionMethodName || g_RpcNameCount >= 1024) return nullptr;

    Il2CppString* nameStr = nullptr;
    bool found = false;

    __try {
        found = GetFunctionMethodName(hash, &nameStr);
    }
    __except (1) { return nullptr; }

    if (!found || !nameStr) return nullptr;

    // Add to cache
    auto& e = g_RpcNames[g_RpcNameCount];
    e.hash = hash;
    e.requiresAuth = false;

    // Read string
    __try {
        int len = *(int*)((uintptr_t)nameStr + STRING_LENGTH_OFFSET);
        if (len <= 0 || len >= 128) {
            strcpy_s(e.name, "???");
        }
        else {
            wchar_t* chars = (wchar_t*)((uintptr_t)nameStr + STRING_CHARS_OFFSET);
            for (int i = 0; i < len && i < 127; i++) {
                e.name[i] = (char)chars[i];
            }
            e.name[len < 127 ? len : 127] = 0;
        }
    }
    __except (1) {
        strcpy_s(e.name, "???");
    }

    // Get requires auth
    if (CommandRequiresAuthority) {
        __try { e.requiresAuth = CommandRequiresAuthority(hash); }
        __except (1) {}
    }

    g_RpcNameCount++;
    return e.name;
}

void NetLog(NetLogType type, uint16_t hash, uint32_t netId, int size,
    bool blocked, const char* fmt, ...)
{
    EnterCriticalSection(&g_NetLogCS);

    auto& e = g_NetLog[g_NetLogHead];
    e.timestamp = GetTickCount();
    e.type = type;
    e.rpcHash = hash;
    e.netId = netId;
    e.dataSize = size;
    e.wasBlocked = blocked;
    e.detail[0] = 0;
    e.rpcName[0] = 0;

    // Resolve RPC name
    if (hash != 0) {
        const char* name = ResolveRpcHash(hash);
        if (name && name[0] && strcmp(name, "???") != 0)
            strncpy_s(e.rpcName, name, 63);
    }

    // Format summary
    va_list a;
    va_start(a, fmt);
    vsnprintf(e.summary, sizeof(e.summary), fmt, a);
    va_end(a);

    g_NetLogHead = (g_NetLogHead + 1) % NETLOG_SIZE;
    if (g_NetLogCount < NETLOG_SIZE) g_NetLogCount++;

    LeaveCriticalSection(&g_NetLogCS);

    // Notify window to update
    if (g_NetMonWindow && !g_NetMonPaused) {
        PostMessage(g_NetMonWindow, WM_USER + 1, 0, 0);
    }
}

void __fastcall Hook_RecvPipe_Enqueue(
    void* self, int connectionId, int eventType, void* segmentPtr)
{
    uint8_t* rawData = nullptr;
    int rawSize = 0;

    __try {
        // ArraySegment<byte> on x64: passed as pointer to struct {void* array, int offset, int count}
        if (segmentPtr) {
            void* arr = *(void**)((uintptr_t)segmentPtr);
            int offset = *(int*)((uintptr_t)segmentPtr + 8);
            int count = *(int*)((uintptr_t)segmentPtr + 12);
            if (arr && count > 0 && count < 65536) {
                rawData = (uint8_t*)((uintptr_t)arr + 0x20 + offset);
                rawSize = count;
            }
        }
    }
    __except (1) {}

    UpdateTcpStats();
    g_TcpBytesRecv += rawSize;
    g_TcpRecvCounter++;

    const char* evtStr = "DATA";
    if (eventType == 0) evtStr = "CONN";
    if (eventType == 2) evtStr = "DISC";

    // Parse Mirror message ID from data
    uint16_t mirrorMsgId = 0;
    const char* mirrorMsgName = nullptr;
    if (eventType == 1 && rawData && rawSize >= 2) {
        mirrorMsgId = rawData[0] | (rawData[1] << 8);
        mirrorMsgName = LookupMirrorMsg(mirrorMsgId);
    }

    // Log to NetMon
    if (g_TcpSnifferEnabled) {
        if (mirrorMsgName) {
            NetLog(NLOG_TCP_IN, mirrorMsgId, 0, rawSize, false,
                "TCP IN %s cid=%d %d bytes [%s]",
                evtStr, connectionId, rawSize, mirrorMsgName);
        }
        else if (eventType == 1) {
            NetLog(NLOG_TCP_IN, mirrorMsgId, 0, rawSize, false,
                "TCP IN %s cid=%d %d bytes [msg:0x%04X]",
                evtStr, connectionId, rawSize, mirrorMsgId);
        }
        else {
            NetLog(NLOG_TCP_IN, 0, 0, rawSize, false,
                "TCP IN %s cid=%d", evtStr, connectionId);
        }
        if (rawData && rawSize > 0) NetLogHex(rawData, rawSize);
    }

    // === ANTI-KICK: Block TCP disconnect events ===
    if (eventType == 2 && g_TcpDropDisconnect) {
        NetLog(NLOG_BLOCKED, 0, 0, 0, true,
            "TCP DISC event BLOCKED cid=%d", connectionId);
        CmdLog("[TCP-ANTIKICK] Disconnect event BLOCKED (cid=%d)", connectionId);
        return;
    }

    // === FULL TCP DESYNC ===
    if (g_TcpDropAllIncoming && eventType == 1) return;

    // === BLOCK BY MIRROR MSG ID ===
    if (eventType == 1 && mirrorMsgId && IsMsgIdBlocked(mirrorMsgId)) {
        NetLog(NLOG_BLOCKED, mirrorMsgId, 0, rawSize, true,
            "TCP BLOCKED msg 0x%04X (%s)",
            mirrorMsgId, mirrorMsgName ? mirrorMsgName : "unknown");
        return;
    }

    RemoveHook(g_RecvEnqueueAddr, g_RecvEnqueueOrig);
    __try {
        ((RecvPipe_Enqueue_t)g_RecvEnqueueAddr)(self, connectionId, eventType, segmentPtr);
    }
    __except (1) {}
    InstallHook(g_RecvEnqueueAddr, &Hook_RecvPipe_Enqueue, g_RecvEnqueueOrig);
}

// ==================== HOOK: MagnificentSendPipe::Enqueue ====================
// void Enqueue(ArraySegment<byte> data)

typedef void(__fastcall* SendPipe_Enqueue_t)(void* self, void* segmentPtr);

void* g_SendEnqueueAddr = nullptr;
BYTE g_SendEnqueueOrig[14];
bool g_SendEnqueueHooked = false;

void __fastcall Hook_SendPipe_Enqueue(void* self, void* segmentPtr) {
    uint8_t* rawData = nullptr;
    int rawSize = 0;

    __try {
        if (segmentPtr) {
            void* arr = *(void**)((uintptr_t)segmentPtr);
            int offset = *(int*)((uintptr_t)segmentPtr + 8);
            int count = *(int*)((uintptr_t)segmentPtr + 12);
            if (arr && count > 0 && count < 65536) {
                rawData = (uint8_t*)((uintptr_t)arr + 0x20 + offset);
                rawSize = count;
            }
        }
    }
    __except (1) {}

    UpdateTcpStats();
    g_TcpBytesSent += rawSize;
    g_TcpSentCounter++;

    if (g_TcpSnifferEnabled && rawSize > 0) {
        uint16_t mirrorMsgId = 0;
        const char* mirrorMsgName = nullptr;
        if (rawData && rawSize >= 2) {
            mirrorMsgId = rawData[0] | (rawData[1] << 8);
            mirrorMsgName = LookupMirrorMsg(mirrorMsgId);
        }

        if (mirrorMsgName) {
            NetLog(NLOG_TCP_OUT, mirrorMsgId, 0, rawSize, false,
                "TCP OUT %d bytes [%s]", rawSize, mirrorMsgName);
        }
        else {
            NetLog(NLOG_TCP_OUT, mirrorMsgId, 0, rawSize, false,
                "TCP OUT %d bytes [msg:0x%04X]", rawSize, mirrorMsgId);
        }
        if (rawData && rawSize > 0) NetLogHex(rawData, rawSize);
    }

    if (g_TcpDropOutgoing) return;

    RemoveHook(g_SendEnqueueAddr, g_SendEnqueueOrig);
    __try {
        ((SendPipe_Enqueue_t)g_SendEnqueueAddr)(self, segmentPtr);
    }
    __except (1) {}
    InstallHook(g_SendEnqueueAddr, &Hook_SendPipe_Enqueue, g_SendEnqueueOrig);
}

// ==================== HOOK: Client::Disconnect ====================
typedef void(__fastcall* TeleClient_Disconnect_t)(void* self);

void* g_TeleDiscAddr = nullptr;
BYTE g_TeleDiscOrig[14];
bool g_TeleDiscHooked = false;

void __fastcall Hook_TeleClient_Disconnect(void* self) {
    if (g_AntiKickEnabled || g_TcpDropDisconnect) {
        NetLog(NLOG_BLOCKED, 0, 0, 0, true, "TCP Client::Disconnect BLOCKED");
        CmdLog("[TCP-ANTIKICK] Client::Disconnect BLOCKED");
        return;
    }
    RemoveHook(g_TeleDiscAddr, g_TeleDiscOrig);
    __try { ((TeleClient_Disconnect_t)g_TeleDiscAddr)(self); }
    __except (1) {}
    InstallHook(g_TeleDiscAddr, &Hook_TeleClient_Disconnect, g_TeleDiscOrig);
}

// ==================== HOOK: Client::Tick — capture instance ====================
typedef void(__fastcall* TeleClient_Tick_t)(void* self, int processLimit, void* checkEnabled);

void* g_TeleTickAddr = nullptr;
BYTE g_TeleTickOrig[14];
bool g_TeleTickHooked = false;

void __fastcall Hook_TeleClient_Tick(void* self, int processLimit, void* checkEnabled) {
    if (!g_TeleClientInstance) {
        g_TeleClientInstance = self;
        CmdLog("[TCP] Captured Telepathy::Client @ 0x%p", self);
    }
    RemoveHook(g_TeleTickAddr, g_TeleTickOrig);
    __try {
        ((TeleClient_Tick_t)g_TeleTickAddr)(self, processLimit, checkEnabled);
    }
    __except (1) {}
    InstallHook(g_TeleTickAddr, &Hook_TeleClient_Tick, g_TeleTickOrig);
}

// ==================== INSTALL / REMOVE ====================
void InstallTelepathyHooks() {
    uintptr_t b = (uintptr_t)g_GameAssembly;

    if (!g_RecvEnqueueHooked) {
        g_RecvEnqueueAddr = (void*)(b + TELE_RECV_ENQUEUE_OFFSET);
        InstallHook(g_RecvEnqueueAddr, &Hook_RecvPipe_Enqueue, g_RecvEnqueueOrig);
        g_RecvEnqueueHooked = true;
    }
    if (!g_SendEnqueueHooked) {
        g_SendEnqueueAddr = (void*)(b + TELE_SEND_ENQUEUE_OFFSET);
        InstallHook(g_SendEnqueueAddr, &Hook_SendPipe_Enqueue, g_SendEnqueueOrig);
        g_SendEnqueueHooked = true;
    }
    if (!g_TeleDiscHooked) {
        g_TeleDiscAddr = (void*)(b + TELE_CLIENT_DISCONNECT_OFFSET);
        InstallHook(g_TeleDiscAddr, &Hook_TeleClient_Disconnect, g_TeleDiscOrig);
        g_TeleDiscHooked = true;
    }
    if (!g_TeleTickHooked) {
        g_TeleTickAddr = (void*)(b + TELE_CLIENT_TICK_OFFSET);
        InstallHook(g_TeleTickAddr, &Hook_TeleClient_Tick, g_TeleTickOrig);
        g_TeleTickHooked = true;
    }

    g_TcpSnifferEnabled = true;
    CmdLog("[+] Telepathy hooks installed (4 hooks)");
}

void RemoveTelepathyHooks() {
    if (g_RecvEnqueueHooked) { RemoveHook(g_RecvEnqueueAddr, g_RecvEnqueueOrig);   g_RecvEnqueueHooked = false; }
    if (g_SendEnqueueHooked) { RemoveHook(g_SendEnqueueAddr, g_SendEnqueueOrig);   g_SendEnqueueHooked = false; }
    if (g_TeleDiscHooked) { RemoveHook(g_TeleDiscAddr, g_TeleDiscOrig);         g_TeleDiscHooked = false; }
    if (g_TeleTickHooked) { RemoveHook(g_TeleTickAddr, g_TeleTickOrig);         g_TeleTickHooked = false; }

    g_TcpSnifferEnabled = false;
    g_TcpDropDisconnect = false;
    g_TcpDropAllIncoming = false;
    g_TcpDropOutgoing = false;
    CmdLog("[+] Telepathy hooks removed");
}


// HOOK: HandleRemoteCall — ALL incoming RPCs pass through here
// ================================================================
void __fastcall Hook_HandleRemoteCall(
    void* self, uint8_t componentIndex, uint16_t functionHash,
    int remoteCallType, void* reader, void* conn)
{
    if (!g_PCEnabled) goto call_original;

    {
        uint32_t netId = 0;
        if (g_NI_netId_offset) {
            __try { netId = *(uint32_t*)((uintptr_t)self + g_NI_netId_offset); }
            __except (1) {}
        }

        const char* typeStr = "???";
        switch (remoteCallType) {
        case 0: typeStr = "Cmd"; break;
        case 1: typeStr = "Rpc"; break;
        case 2: typeStr = "TgtRpc"; break;
        }

        // RESOLVE NAME - это ключевая строка!
        const char* rpcName = ResolveRpcHash(functionHash);

        int blockedIdx = FindBlockedIndex(functionHash);
        bool blocked = (blockedIdx >= 0);

        if (g_FullDesyncEnabled && (remoteCallType == 1 || remoteCallType == 2))
            blocked = true;

        if (g_PCAutoBlock && !blocked && (remoteCallType == 1 || remoteCallType == 2)) {
            if (g_BlockedCount < 256) {
                g_Blocked[g_BlockedCount].hash = functionHash;
                if (rpcName && rpcName[0])
                    snprintf(g_Blocked[g_BlockedCount].label, 64, "%s", rpcName);
                else
                    snprintf(g_Blocked[g_BlockedCount].label, 64, "auto_%04X", functionHash);
                g_Blocked[g_BlockedCount].blockCount = 0;
                g_Blocked[g_BlockedCount].enabled = true;
                g_BlockedCount++;
                blockedIdx = g_BlockedCount - 1;
                blocked = true;
            }
        }

        // LOG WITH NAME
        if (g_PCLogging) {

            /*if (rpcName && rpcName[0] && strcmp(rpcName, "???") != 0) {
                CmdLog("[%s] %s 0x%04X (%s) nid=%u",
                    blocked ? "BLOCK" : "PASS", typeStr, functionHash, rpcName, netId);
            }
            else {
                CmdLog("[%s] %s 0x%04X nid=%u",
                    blocked ? "BLOCK" : "PASS", typeStr, functionHash, netId);
            }*/

            NetLog(
                (remoteCallType == 0) ? NLOG_MIRROR_CMD_OUT :
                (blocked ? NLOG_BLOCKED : NLOG_MIRROR_RPC_IN),
                functionHash, netId, 0, blocked,
                "%s 0x%04X nid=%u comp=%d",
                typeStr, functionHash, netId, componentIndex);

        }

        // Ring buffer
        auto& entry = g_RpcLog[g_RpcLogHead];
        entry.hash = functionHash;
        entry.componentIndex = componentIndex;
        entry.callType = (uint8_t)remoteCallType;
        entry.netId = netId;
        entry.timestamp = GetTickCount();
        entry.wasBlocked = blocked;
        g_RpcLogHead = (g_RpcLogHead + 1) % 512;
        if (g_RpcLogCount < 512) g_RpcLogCount++;

        if (blocked && blockedIdx >= 0) {
            g_Blocked[blockedIdx].blockCount++;
            return;
        }
    }

call_original:
    RemoveHook(g_HandleRCAddr, g_HandleRCOrig);
    __try {
        ((HandleRemoteCall_t)g_HandleRCAddr)(
            self, componentIndex, functionHash, remoteCallType, reader, conn);
    }
    __except (1) {}
    InstallHook(g_HandleRCAddr, &Hook_HandleRemoteCall, g_HandleRCOrig);
}


// Dump ALL registered RPCs
void DumpAllRpcNames() {
    CmdLog("[*] Scanning all 65536 hashes... (this takes ~30 seconds)");

    int found = 0;
    for (uint32_t h = 0; h <= 0xFFFF; h++) {
        const char* name = ResolveRpcHash((uint16_t)h);
        if (name && name[0] && strcmp(name, "???") != 0) {
            bool auth = false;
            for (int i = 0; i < g_RpcNameCount; i++) {
                if (g_RpcNames[i].hash == (uint16_t)h) {
                    auth = g_RpcNames[i].requiresAuth;
                    break;
                }
            }
            CmdLog("  0x%04X = %-50s %s", h, name, auth ? "[AUTH]" : "[NO AUTH]");
            found++;
        }

        // Progress every 4096
        if ((h & 0x0FFF) == 0) {
            // Silent progress - just keep going
        }
    }

    CmdLog("[+] Found %d registered RPCs/Commands", found);
}

// ================================================================
// HOOK: DeserializeClient — SyncVar updates
// ================================================================
bool g_SyncVarBlockAll = false;

void __fastcall Hook_DeserializeClient(void* self, void* reader, bool initialState) {
    if (g_SyncVarBlockAll && !initialState) {
        // Block all SyncVar updates (except initial spawn)
        if (g_PCLogging) {
            uint32_t netId = 0;
            if (g_NI_netId_offset) {
                __try { netId = *(uint32_t*)((uintptr_t)self + g_NI_netId_offset); }
                __except (1) {}
            }
            /*CmdLog("[BLOCK] SyncVar update nid=%u", netId);*/

            NetLog(NLOG_MIRROR_SYNCVAR, 0, netId, 0,
                (g_SyncVarBlockAll && !initialState),
                "SyncVar %s nid=%u",
                initialState ? "INIT" : "UPDATE", netId);
        }
        return;
    }

    RemoveHook(g_DeserializeAddr, g_DeserializeOrig);
    __try { ((DeserializeClient_t)g_DeserializeAddr)(self, reader, initialState); }
    __except (1) {}
    InstallHook(g_DeserializeAddr, &Hook_DeserializeClient, g_DeserializeOrig);
}

// ================================================================
// INSTALL / REMOVE all hooks
// ================================================================
void InstallAllPCHooks() {
    uintptr_t b = (uintptr_t)g_GameAssembly;

    if (!g_HandleRCHooked) {
        g_HandleRCAddr = (void*)(b + HANDLE_REMOTE_CALL_OFFSET);
        InstallHook(g_HandleRCAddr, &Hook_HandleRemoteCall, g_HandleRCOrig);
        g_HandleRCHooked = true;
    }
    if (!g_DeserializeHooked) {
        g_DeserializeAddr = (void*)(b + DESERIALIZE_CLIENT_OFFSET);
        InstallHook(g_DeserializeAddr, &Hook_DeserializeClient, g_DeserializeOrig);
        g_DeserializeHooked = true;
    }
}

void RemoveAllPCHooks() {
    if (g_HandleRCHooked) { RemoveHook(g_HandleRCAddr, g_HandleRCOrig); g_HandleRCHooked = false; }
    if (g_DelayedDiscHooked) { RemoveHook(g_DelayedDiscAddr, g_DelayedDiscOrig); g_DelayedDiscHooked = false; }
    if (g_DeserializeHooked) { RemoveHook(g_DeserializeAddr, g_DeserializeOrig); g_DeserializeHooked = false; }

    g_PCEnabled = false;
    g_PCLogging = false;
    g_AntiKickEnabled = false;
    g_FullDesyncEnabled = false;
    g_SyncVarBlockAll = false;
    g_PCAutoBlock = false;
}

void EnableEventLogger() {
    if (!g_HooksInstalled) {
        InstallHook(g_InvokeServerAddr, &Hook_InvokeServer, g_InvokeServerOrig);
        g_HooksInstalled = true;
    }
    g_EventLoggerEnabled = true;
    CmdLog("[+] Event Logger ENABLED");
}

void DisableEventLogger() {
    g_EventLoggerEnabled = false;
    if (g_HooksInstalled) {
        RemoveHook(g_InvokeServerAddr, g_InvokeServerOrig);
        g_HooksInstalled = false;
    }
    CmdLog("[+] Event Logger DISABLED");
}

void DumpSelectedScriptSource() {
    if (!g_SelectedInstance) { Log("[-] No instance selected"); return; }

    char cls[64] = {};
    SafeGetClassName(g_SelectedInstance, cls, 64);
    if (strcmp(cls, "ScriptInstance") != 0 && strcmp(cls, "LocalScript") != 0 && strcmp(cls, "ModuleScript") != 0) {
        Log("[-] Not a script");
        return;
    }

    char name[128] = {};
    SafeGetName(g_SelectedInstance, name, 128);

    Il2CppString* srcStr = nullptr;
    __try {
        srcStr = *(Il2CppString**)((uintptr_t)g_SelectedInstance + BASESCRIPT_SOURCE_FIELD_OFFSET);
    }
    __except (1) {
        Log("[-] Failed to read source field");
        return;
    }

    if (!srcStr) { Log("[-] Source is NULL"); return; }

    int len = 0;
    wchar_t* chars = nullptr;
    __try {
        len = *(int*)((uintptr_t)srcStr + STRING_LENGTH_OFFSET);
        chars = (wchar_t*)((uintptr_t)srcStr + STRING_CHARS_OFFSET);
    }
    __except (1) {
        Log("[-] Failed to read string");
        return;
    }

    if (len <= 0 || len > 500000) { Log("[-] Invalid source length: %d", len); return; }

    char* src = (char*)malloc(len + 1);
    if (!src) { Log("[-] malloc failed"); return; }
    for (int i = 0; i < len; i++) src[i] = (char)chars[i];
    src[len] = 0;

    // Save dialog без std::string
    char filepath[MAX_PATH] = "script.lua";
    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_Window;
    ofn.lpstrFilter = "Lua Files (*.lua)\0*.lua\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filepath;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
    ofn.lpstrTitle = "Save Script Source";

    if (!GetSaveFileNameA(&ofn)) { free(src); return; }

    FILE* f = nullptr;
    fopen_s(&f, filepath, "w");
    if (!f) { Log("[-] Can't create file"); free(src); return; }
    fwrite(src, 1, len, f);
    fclose(f);
    free(src);

    Log("[+] Saved '%s' source to %s (%d chars)", name, filepath, len);
}

void SaveAllScripts() {
    if (!g_GameSingleton) {
        g_GameSingleton = SafeFindGame(g_Domain);
        if (!g_GameSingleton) { CmdLog("[-] No game. Refresh first."); return; }
    }

    // Выбрать папку через save dialog (сохраняем как маркер)
    char filename[MAX_PATH] = "savedscripts.txt";
    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_Window;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_NOCHANGEDIR;
    ofn.lpstrTitle = "Choose folder (select any filename)";
    if (!GetSaveFileNameA(&ofn)) return;

    // Получаем директорию
    char dir[MAX_PATH];
    strcpy_s(dir, filename);
    char* lastSlash = strrchr(dir, '\\');
    if (lastSlash) *(lastSlash + 1) = 0;

    int saved = 0;

    // Рекурсивная лямбда через статическую функцию
    struct Helper {
        static void Collect(void* inst, const char* dir, int& saved, int depth) {
            if (!inst || depth > 20) return;

            char cls[64] = {};
            SafeGetClassName(inst, cls, 64);

            if (strcmp(cls, "ScriptInstance") == 0 || strcmp(cls, "LocalScript") == 0 || strcmp(cls, "ModuleScript") == 0) {
                char name[128] = {};
                SafeGetName(inst, name, 128);

                __try {
                    Il2CppString* srcStr = *(Il2CppString**)((uintptr_t)inst + BASESCRIPT_SOURCE_FIELD_OFFSET);
                    if (srcStr) {
                        int len = *(int*)((uintptr_t)srcStr + STRING_LENGTH_OFFSET);
                        if (len > 0 && len < 500000) {
                            wchar_t* chars = (wchar_t*)((uintptr_t)srcStr + STRING_CHARS_OFFSET);

                            char filepath[MAX_PATH];
                            snprintf(filepath, MAX_PATH, "%s%s_%d.lua", dir, name, saved);

                            FILE* f = nullptr;
                            fopen_s(&f, filepath, "w");
                            if (f) {
                                for (int i = 0; i < len; i++) fputc((char)chars[i], f);
                                fclose(f);
                                saved++;
                            }
                        }
                    }
                }
                __except (1) {}
            }

            void* children[512];
            int cnt = SafeGetChildren(inst, children, 512);
            for (int i = 0; i < cnt; i++) {
                Collect(children[i], dir, saved, depth + 1);
            }
        }
    };

    Helper::Collect(g_GameSingleton, dir, saved, 0);
    CmdLog("[+] Saved %d scripts to %s", saved, dir);
    Log("[+] Saved %d scripts to %s", saved, dir);
}

void CopyInstancePath() {
    if (!g_SelectedInstance) { Log("[-] Nothing selected"); return; }

    // Строим путь от корня
    char path[2048] = {};
    char segments[20][128];
    int segCount = 0;

    void* current = g_SelectedInstance;
    while (current && segCount < 20) {
        char name[128] = {};
        SafeGetName(current, name, 128);
        if (!name[0]) break;
        strcpy_s(segments[segCount++], name);

        // Ищем parent в нашем дереве
        bool found = false;
        for (auto& pair : g_Instances) {
            void* children[512];
            int cnt = SafeGetChildren(pair.second.ptr, children, 512);
            for (int i = 0; i < cnt; i++) {
                if (children[i] == current) {
                    current = pair.second.ptr;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) break;
    }

    // Собираем в game["X"]["Y"]["Z"]
    int pos = 0;
    pos += snprintf(path + pos, sizeof(path) - pos, "game");
    for (int i = segCount - 2; i >= 0; i--) {  // -2 чтобы пропустить "Game"
        pos += snprintf(path + pos, sizeof(path) - pos, "[\"%s\"]", segments[i]);
    }

    // В буфер обмена
    if (OpenClipboard(g_Window)) {
        EmptyClipboard();
        HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(path) + 1);
        if (hg) {
            memcpy(GlobalLock(hg), path, strlen(path) + 1);
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
        }
        CloseClipboard();
        Log("[+] Copied: %s", path);
    }
}

// ==================== NETWORK WRITER ====================

void* FindClassInAssemblies(const char* ns, const char* name) {
    size_t cnt = 0;
    auto asms = il2cpp_domain_get_assemblies(g_Domain, &cnt);
    for (size_t i = 0; i < cnt; i++) {
        auto img = il2cpp_assembly_get_image(asms[i]);
        if (!img) continue;
        auto cls = il2cpp_class_from_name(img, ns, name);
        if (cls) return cls;
    }
    return nullptr;
}

void* CreateNetworkWriter() {
    if (!g_NetworkWriterClass) {
        g_NetworkWriterClass = FindClassInAssemblies("Mirror", "NetworkWriter");
        if (!g_NetworkWriterClass) {
            CmdLog("[-] NetworkWriter class not found");
            return nullptr;
        }
    }
    void* writer = il2cpp_object_new(g_NetworkWriterClass);
    if (!writer) { CmdLog("[-] il2cpp_object_new failed"); return nullptr; }
    __try { NW_ctor(writer); }
    __except (1) { CmdLog("[-] NW ctor crashed"); return nullptr; }
    return writer;
}

int GetWriterPosition(void* writer) {
    __try { return *(int*)((uintptr_t)writer + NW_POSITION_OFFSET); }
    __except (1) { return -1; }
}

bool ManualWriteBytes(void* writer, const void* data, int size) {
    __try {
        void* buffer = *(void**)((uintptr_t)writer + NW_BUFFER_OFFSET);
        int pos = *(int*)((uintptr_t)writer + NW_POSITION_OFFSET);
        int capacity = *(int*)((uintptr_t)buffer + 0x18);
        if (pos + size > capacity) return false;
        memcpy((void*)((uintptr_t)buffer + 0x20 + pos), data, size);
        *(int*)((uintptr_t)writer + NW_POSITION_OFFSET) = pos + size;
        return true;
    }
    __except (1) { return false; }
}

// ==================== NETID DISCOVERY ====================

bool DiscoverNetIdOffsets() {
    void* lp = SafeGetLocalPlayer();
    if (!lp || !NB_get_netId) {
        CmdLog("[-] Need LocalPlayer. Click Refresh first.");
        return false;
    }

    uint32_t ourNetId = 0;
    __try { ourNetId = NB_get_netId(lp); }
    __except (1) { CmdLog("[-] get_netId crashed"); return false; }

    if (ourNetId == 0) { CmdLog("[-] netId=0, not spawned?"); return false; }
    CmdLog("[*] Our netId = %u", ourNetId);

    for (uintptr_t nbOff = 0x18; nbOff < 0x200; nbOff += 8) {
        __try {
            void* potentialNI = *(void**)((uintptr_t)lp + nbOff);
            if (!potentialNI) continue;
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQuery(potentialNI, &mbi, sizeof(mbi))) continue;
            if (mbi.State != MEM_COMMIT) continue;

            for (uintptr_t niOff = 0x18; niOff < 0x100; niOff += 4) {
                __try {
                    uint32_t val = *(uint32_t*)((uintptr_t)potentialNI + niOff);
                    if (val == ourNetId && val != 0) {
                        g_NB_netIdentity_offset = nbOff;
                        g_NI_netId_offset = niOff;
                        CmdLog("[+] Player+0x%X -> NI+0x%X -> netId=%u", (int)nbOff, (int)niOff, val);
                        return true;
                    }
                }
                __except (1) {}
            }
        }
        __except (1) {}
    }
    CmdLog("[-] Could not find netId offsets");
    return false;
}

// ==================== PLAYER SCANNER ====================

void ScanPlayers() {
    g_ScannedPlayerCount = 0;
    if (!g_PlayersInstance) { CmdLog("[-] No Players. Click Refresh."); return; }

    void* children[64];
    int cnt = SafeGetChildren(g_PlayersInstance, children, 64);
    void* localPlayer = SafeGetLocalPlayer();

    CmdLog("=== PLAYERS (%d) ===", cnt);
    for (int i = 0; i < cnt && g_ScannedPlayerCount < 64; i++) {
        auto& info = g_ScannedPlayers[g_ScannedPlayerCount];
        info.ptr = children[i];
        SafeGetName(children[i], info.name, 128);
        info.netId = 0;
        __try { if (NB_get_netId) info.netId = NB_get_netId(children[i]); }
        __except (1) {}

        bool isLocal = (children[i] == localPlayer);
        CmdLog("  [%d] %s%s  netId=%u  @0x%p",
            g_ScannedPlayerCount, info.name, isLocal ? " (YOU)" : "", info.netId, info.ptr);
        g_ScannedPlayerCount++;
    }
}


// ==================== COMMAND SNIFFER HOOK ====================

void __fastcall Hook_SendCommandInternal(
    void* self, Il2CppString* funcName, int functionHash,
    void* writer, int channelId, bool requireAuthority)
{
    if (g_CmdSnifferEnabled) {
        char fn[128] = "?";
        SafeReadString(funcName, fn, 128);
        uint32_t netId = 0;
        __try { netId = NB_get_netId(self); }
        __except (1) {}
        int payloadSize = GetWriterPosition(writer);

        /*CmdLog("[CMD] hash=0x%08X netId=%u fn=%s size=%d auth=%d",
            functionHash, netId, fn, payloadSize, requireAuthority);*/

        NetLog(NLOG_MIRROR_CMD_OUT, (uint16_t)functionHash, netId, payloadSize, false,
            "CMD %s hash=0x%08X auth=%d", fn, functionHash, requireAuthority);
        if (payloadSize > 0 && writer) {
            __try {
                void* buf = *(void**)((uintptr_t)writer + NW_BUFFER_OFFSET);
                if (buf) NetLogHex((uint8_t*)((uintptr_t)buf + 0x20),
                    payloadSize > 256 ? 256 : payloadSize);
            }
            __except (1) {}
        }

        // Capture
        if (g_CapturedCmdCount < 256) {
            auto& c = g_CapturedCmds[g_CapturedCmdCount];
            c.hash = functionHash;
            strcpy_s(c.funcName, fn);
            c.fromNetId = netId;
            c.payloadSize = payloadSize > 256 ? 256 : payloadSize;
            if (writer && payloadSize > 0) {
                __try {
                    void* buf = *(void**)((uintptr_t)writer + NW_BUFFER_OFFSET);
                    if (buf) memcpy(c.payload, (void*)((uintptr_t)buf + 0x20), c.payloadSize);
                }
                __except (1) {}
            }
            // Hex dump
            if (c.payloadSize > 0) {
                char hex[768] = {};
                int p = 0;
                int n = c.payloadSize > 48 ? 48 : c.payloadSize;
                for (int i = 0; i < n; i++) p += snprintf(hex + p, sizeof(hex) - p, "%02X ", c.payload[i]);
                CmdLog("[CMD]   %s", hex);
            }
            g_CapturedCmdCount++;
        }

        // Auto-detect known hashes
        if (strstr(fn, "SetHealth") || strstr(fn, "CmdSetHealth")) {
            g_CmdSetHealth_Hash = functionHash;
            CmdLog("[*] CmdSetHealth hash = 0x%08X", functionHash);
        }
    }

    if (g_AuthBypassEnabled) requireAuthority = false;

    RemoveHook(g_SendCmdAddr, g_SendCmdOrig);
    __try {
        ((SendCommandInternal_t)g_SendCmdAddr)(self, funcName, functionHash, writer, channelId, requireAuthority);
    }
    __except (1) { CmdLog("[-] SendCmd crashed"); }
    InstallHook(g_SendCmdAddr, &Hook_SendCommandInternal, g_SendCmdOrig);
}

void EnableCmdSniffer() {
    if (g_CmdSnifferEnabled) return;
    uintptr_t b = (uintptr_t)g_GameAssembly;
    g_SendCmdAddr = (void*)(b + SEND_CMD_INTERNAL_OFFSET);
    InstallHook(g_SendCmdAddr, &Hook_SendCommandInternal, g_SendCmdOrig);
    g_CmdSnifferEnabled = true;
    g_CapturedCmdCount = 0;
    CmdLog("[+] Sniffer ON");
}

void DisableCmdSniffer() {
    if (!g_CmdSnifferEnabled) return;
    RemoveHook(g_SendCmdAddr, g_SendCmdOrig);
    g_CmdSnifferEnabled = false;
    CmdLog("[+] Sniffer OFF (%d captured)", g_CapturedCmdCount);
}

// === конец блока новых функций ===

bool HttpGet(const char* url, char* outBuf, int maxLen) {
    HINTERNET hInternet = InternetOpenA("Elytra/1.0", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (!hInternet) return false;

    HINTERNET hUrl = InternetOpenUrlA(hInternet, url, nullptr, 0,
        INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);
    if (!hUrl) { InternetCloseHandle(hInternet); return false; }

    int totalRead = 0;
    DWORD bytesRead = 0;
    while (totalRead < maxLen - 1) {
        if (!InternetReadFile(hUrl, outBuf + totalRead, maxLen - totalRead - 1, &bytesRead))
            break;
        if (bytesRead == 0) break;
        totalRead += bytesRead;
    }
    outBuf[totalRead] = 0;

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
    return totalRead > 0;
}

void __fastcall Hook_KcpPeer_SendData(void* self, void* segmentPtr, int channel) {
    // segmentPtr = ArraySegment<byte> passed by value on stack (или pointer)
    // channel: 0 = Reliable (KcpChannel.Reliable), 1 = Unreliable

    __try {
        // Достаем данные из ArraySegment
        // В IL2CPP ArraySegment передается как struct:
        // На x64 большие struct передаются по указателю
        ArraySegment* seg = (ArraySegment*)segmentPtr;
        if (seg && seg->array && seg->count > 0) {
            uint8_t* rawData = (uint8_t*)((uintptr_t)seg->array + 0x20 + seg->offset);
            /*LogRawPacket(true, channel, rawData, seg->count);*/
            NetLog(NLOG_KCP_RAW_OUT, 0, 0, seg->count, false,
                "KCP OUT ch=%d %d bytes", channel, seg->count);
            if (rawData && seg->count > 0) NetLogHex(rawData, seg->count);

        }
    }
    __except (1) {}

    // Фильтрация
    if (g_DropOutgoing) return;
    if (g_DropOutgoingUnreliable && channel == 1) return;

    RemoveHook(g_KcpSendDataAddr, g_KcpSendDataOrig);
    __try {
        ((KcpPeer_SendData_t)g_KcpSendDataAddr)(self, segmentPtr, channel);
    }
    __except (1) {}
    InstallHook(g_KcpSendDataAddr, &Hook_KcpPeer_SendData, g_KcpSendDataOrig);
}


void __fastcall Hook_KcpPeer_Disconnect(void* self) {
    if (g_AntiKickEnabled) {
        CmdLog("[KCP-ANTIKICK] KcpPeer::Disconnect BLOCKED");
        return;
    }
    RemoveHook(g_KcpDisconnectAddr, g_KcpDisconnectOrig);
    __try { ((KcpPeer_Disconnect_t)g_KcpDisconnectAddr)(self); }
    __except (1) {}
    InstallHook(g_KcpDisconnectAddr, &Hook_KcpPeer_Disconnect, g_KcpDisconnectOrig);
}


void __fastcall Hook_KcpPeer_SendDisconnect(void* self) {
    if (g_AntiKickEnabled) {
        CmdLog("[KCP-ANTIKICK] SendDisconnect BLOCKED (not sending goodbye)");
        return;
    }
    RemoveHook(g_KcpSendDiscAddr, g_KcpSendDiscOrig);
    __try { ((KcpPeer_SendDisconnect_t)g_KcpSendDiscAddr)(self); }
    __except (1) {}
    InstallHook(g_KcpSendDiscAddr, &Hook_KcpPeer_SendDisconnect, g_KcpSendDiscOrig);
}

void __fastcall Hook_KcpClient_RawInput(void* self, void* segmentPtr) {
    __try {
        ArraySegment* seg = (ArraySegment*)segmentPtr;
        if (seg && seg->array && seg->count > 0) {
            uint8_t* rawData = (uint8_t*)((uintptr_t)seg->array + 0x20 + seg->offset);
            int size = seg->count;

            LogRawPacket(false, -1, rawData, size);

            // KCP header parsing:
            // Byte 0: KcpHeader (Hello=1, Ping=2, Data=3, Disconnect=4)
            if (size > 0) {
                uint8_t header = rawData[0];

                // Block disconnect packets at transport level!
                if (header == 4 && g_AntiKickEnabled) {
                    /*CmdLog("[KCP-ANTIKICK] Blocked Disconnect packet at transport level!");*/
                    NetLog(NLOG_KCP_RAW_IN, 0, 0, size, false,
                        "KCP IN %d bytes hdr=%d", size, size > 0 ? rawData[0] : -1);
                    if (rawData && size > 0) NetLogHex(rawData, size);
                    return;
                }
            }
        }
    }
    __except (1) {}

    if (g_DropIncoming) return;

    RemoveHook(g_KcpRawInputAddr, g_KcpRawInputOrig);
    __try {
        ((KcpClient_RawInput_t)g_KcpRawInputAddr)(self, segmentPtr);
    }
    __except (1) {}
    InstallHook(g_KcpRawInputAddr, &Hook_KcpClient_RawInput, g_KcpRawInputOrig);
}


void InstallKcpHooks() {
    uintptr_t b = (uintptr_t)g_GameAssembly;

    // Raw packet interception
    if (!g_KcpRawInputHooked) {
        g_KcpRawInputAddr = (void*)(b + KCP_CLIENT_RAWINPUT_OFFSET);
        InstallHook(g_KcpRawInputAddr, &Hook_KcpClient_RawInput, g_KcpRawInputOrig);
        g_KcpRawInputHooked = true;
    }

    if (!g_KcpSendDataHooked) {
        g_KcpSendDataAddr = (void*)(b + KCP_PEER_SENDDATA_OFFSET);
        InstallHook(g_KcpSendDataAddr, &Hook_KcpPeer_SendData, g_KcpSendDataOrig);
        g_KcpSendDataHooked = true;
    }

    // Anti-disconnect at transport level
    if (!g_KcpDisconnectHooked) {
        g_KcpDisconnectAddr = (void*)(b + KCP_PEER_DISCONNECT_OFFSET);
        InstallHook(g_KcpDisconnectAddr, &Hook_KcpPeer_Disconnect, g_KcpDisconnectOrig);
        g_KcpDisconnectHooked = true;
    }

    if (!g_KcpSendDiscHooked) {
        g_KcpSendDiscAddr = (void*)(b + KCP_PEER_SENDDISCONNECT_OFFSET);
        InstallHook(g_KcpSendDiscAddr, &Hook_KcpPeer_SendDisconnect, g_KcpSendDiscOrig);
        g_KcpSendDiscHooked = true;
    }

    // Anti-timeout
    if (!g_HandleTimeoutHooked) {
        g_HandleTimeoutAddr = (void*)(b + KCP_PEER_HANDLETIMEOUT_OFFSET);
        InstallHook(g_HandleTimeoutAddr, &Hook_KcpPeer_HandleTimeout, g_HandleTimeoutOrig);
        g_HandleTimeoutHooked = true;
    }

    if (!g_HandleDeadLinkHooked) {
        g_HandleDeadLinkAddr = (void*)(b + KCP_PEER_HANDLEDEADLINK_OFFSET);
        InstallHook(g_HandleDeadLinkAddr, &Hook_KcpPeer_HandleDeadLink, g_HandleDeadLinkOrig);
        g_HandleDeadLinkHooked = true;
    }

    if (!g_HandleChokedHooked) {
        g_HandleChokedAddr = (void*)(b + KCP_PEER_HANDLECHOKED_OFFSET);
        InstallHook(g_HandleChokedAddr, &Hook_KcpPeer_HandleChoked, g_HandleChokedOrig);
        g_HandleChokedHooked = true;
    }

    CmdLog("[+] All KCP hooks installed (7 hooks)");
}

void RemoveKcpHooks() {
    if (g_KcpRawInputHooked) { RemoveHook(g_KcpRawInputAddr, g_KcpRawInputOrig);     g_KcpRawInputHooked = false; }
    if (g_KcpSendDataHooked) { RemoveHook(g_KcpSendDataAddr, g_KcpSendDataOrig);     g_KcpSendDataHooked = false; }
    if (g_KcpDisconnectHooked) { RemoveHook(g_KcpDisconnectAddr, g_KcpDisconnectOrig); g_KcpDisconnectHooked = false; }
    if (g_KcpSendDiscHooked) { RemoveHook(g_KcpSendDiscAddr, g_KcpSendDiscOrig);     g_KcpSendDiscHooked = false; }
    if (g_HandleTimeoutHooked) { RemoveHook(g_HandleTimeoutAddr, g_HandleTimeoutOrig); g_HandleTimeoutHooked = false; }
    if (g_HandleDeadLinkHooked) { RemoveHook(g_HandleDeadLinkAddr, g_HandleDeadLinkOrig); g_HandleDeadLinkHooked = false; }
    if (g_HandleChokedHooked) { RemoveHook(g_HandleChokedAddr, g_HandleChokedOrig);   g_HandleChokedHooked = false; }

    g_RawSnifferEnabled = false;
    g_DropOutgoing = false;
    g_DropIncoming = false;
    g_AntiTimeoutEnabled = false;

    CmdLog("[+] All KCP hooks removed");
}


void CleanupScripts() {
    int cleaned = 0;
    for (int i = 0; i < g_CreatedScriptCount; i++) {
        if (g_CreatedScripts[i]) {
            __try {
                Instance_Destroy(g_CreatedScripts[i], 0);
                cleaned++;
            }
            __except (1) {}
            g_CreatedScripts[i] = nullptr;
        }
    }
    g_CreatedScriptCount = 0;
    if (cleaned > 0) Log("[+] Cleaned %d ScriptInstances", cleaned);
}

bool g_Lua2LuauEnabled = false;

void ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.size(), to);
        pos += to.size();
    }
}

std::string TranslateLuau(const std::string& source) {
    std::string r = source;

    // Instance.new → Instance.New
    ReplaceAll(r, "Instance.new(", "Instance.New(");

    // game.Workspace → game["Environment"]
    ReplaceAll(r, "game.Workspace", "game[\"Environment\"]");
    ReplaceAll(r, "game.workspace", "game[\"Environment\"]");

    // .Something → ["Something"] для game доступа
    // game.Players → game["Players"]
    // game.Lighting → game["Lighting"]
    // Ищем паттерн game.Word и конвертируем
    {
        size_t pos = 0;
        while ((pos = r.find("game.", pos)) != std::string::npos) {
            size_t nameStart = pos + 5;
            // Уже сконвертировано в ["..."]?
            if (nameStart < r.size() && r[nameStart] == '[') { pos = nameStart; continue; }
            // Собираем имя
            size_t nameEnd = nameStart;
            while (nameEnd < r.size() && (isalnum(r[nameEnd]) || r[nameEnd] == '_'))
                nameEnd++;
            if (nameEnd == nameStart) { pos = nameEnd; continue; }
            std::string name = r.substr(nameStart, nameEnd - nameStart);
            std::string rep = "game[\"" + name + "\"]";
            r.replace(pos, nameEnd - pos, rep);
            pos += rep.size();
        }
    }

    ReplaceAll(r, ":FindFirstChild(", ":FindChild(");
    ReplaceAll(r, ":WaitForChild(", ":FindChild(");
    ReplaceAll(r, ":GetDescendants(", ":GetChildren(");
    ReplaceAll(r, ":ClearAllChildren(", ":ClearChildren(");

    return r;
}


void Cmd_L2S_Preview() {
    int len = GetWindowTextLengthA(g_ScriptEdit);
    if (len <= 0) { CmdLog("[-] Empty"); return; }

    char* buf = (char*)malloc(len + 1);
    if (!buf) { CmdLog("[-] Alloc failed"); return; }

    GetWindowTextA(g_ScriptEdit, buf, len + 1);

    std::string translated = TranslateLuau(buf);
    CmdLog("%s", translated.c_str());

    free(buf);
}

void ProcessCommand(const char* cmd) {
    CmdLog(">> %s", cmd);
    char command[64] = {}, arg1[256] = {};
    sscanf_s(cmd, "%63s %255[^\n]", command, (unsigned)sizeof(command), arg1, (unsigned)sizeof(arg1));

    if (strcmp(command, "sh") == 0) {
        if (!arg1[0]) { CmdLog("[!] sh <health>"); return; }
        float hv = (float)atof(arg1);
        void* lp = SafeGetLocalPlayer();
        if (!lp) { CmdLog("[-] No LocalPlayer. Refresh first."); return; }
        if (!Plr_CmdSetHealth) { CmdLog("[-] CmdSetHealth not resolved"); return; }
        __try { Plr_CmdSetHealth(lp, hv); CmdLog("[+] Health=%.0f", hv); }
        __except (1) { CmdLog("[-] Crashed"); }
    }
    // =============== PACKET CANCELLER ===============
    if (strcmp(command, "pc") == 0) {
        if (strcmp(arg1, "on") == 0) {
            InstallAllPCHooks();
            g_PCEnabled = true;
            g_PCLogging = true;
            CmdLog("[+] Packet Canceller ON — logging all RPCs");
            CmdLog("[*] Use 'block <hash>' to block, 'blocks' to list");
        }
        else if (strcmp(arg1, "off") == 0) {
            RemoveAllPCHooks();
            CmdLog("[+] Packet Canceller OFF — all hooks removed");
        }
        else if (strcmp(arg1, "quiet") == 0) {
            g_PCLogging = false;
            CmdLog("[+] Logging OFF (still blocking)");
        }
        else if (strcmp(arg1, "loud") == 0) {
            g_PCLogging = true;
            CmdLog("[+] Logging ON");
        }
        else CmdLog("[!] pc on/off/quiet/loud");
    }

    else if (strcmp(command, "l2s") == 0) {
        if (strcmp(arg1, "on") == 0) {
            g_Lua2LuauEnabled = true;
            CmdLog("[+] Translator ON");
        }
        else if (strcmp(arg1, "off") == 0) {
            g_Lua2LuauEnabled = false;
            CmdLog("[+] Translator OFF");
        }
        else if (strcmp(arg1, "preview") == 0) {
            Cmd_L2S_Preview();
        }
        else {
            CmdLog("[*] l2s: %s", g_Lua2LuauEnabled ? "ON" : "OFF");
            CmdLog("[!] l2s on/off");
        }
    }

    else if (strcmp(command, "netmon") == 0) {
        CreateNetMonWindow();
        CmdLog("[+] Network Monitor opened");
    }

    else if (strcmp(command, "antikick") == 0) {
        if (strcmp(arg1, "on") == 0) {
            InstallAntiKickHooks();
            g_AntiKickEnabled = true;
            CmdLog("[+] ANTI-KICK ON");
            CmdLog("[*] Hooked 5 disconnect paths.");
        }
        else if (strcmp(arg1, "off") == 0) {
            g_AntiKickEnabled = false;
            RemoveAntiKickHooks();
            CmdLog("[+] ANTI-KICK OFF");
        }
        else CmdLog("[!] antikick on/off");
    }

    else if (strcmp(command, "netmon") == 0) {
        CreateNetMonWindow();
        CmdLog("[+] Network Monitor opened");
        CmdLog("[*] Double-click row for detail, right-click for actions");
    }

    else if (strcmp(command, "cleanup") == 0) {
        CleanupScripts();
        g_CurrentScript = nullptr;
        CmdLog("[+] All ScriptInstances cleaned");
    }
    else if (strcmp(command, "autoclean") == 0) {
        if (strcmp(arg1, "on") == 0) {
            g_AutoCleanup = true;
            CmdLog("[+] Auto-cleanup ON — previous script destroyed before new one");
        }
        else if (strcmp(arg1, "off") == 0) {
            g_AutoCleanup = false;
            CmdLog("[+] Auto-cleanup OFF — scripts persist in ScriptService");
        }
        else {
            CmdLog("[*] Auto-cleanup: %s (%d tracked)",
                g_AutoCleanup ? "ON" : "OFF", g_CreatedScriptCount);
        }
    }
    // =============== KCP ===========================
    else if (strcmp(command, "kcp") == 0) {
        char sub[64] = {};
        sscanf_s(arg1, "%63s", sub, (unsigned)sizeof(sub));

        if (strcmp(sub, "on") == 0) {
            InstallKcpHooks();
            g_RawSnifferEnabled = true;
            g_RawLogToConsole = false;
            CmdLog("[+] KCP layer hooks active");
        }
        else if (strcmp(sub, "off") == 0) {
            RemoveKcpHooks();
            CmdLog("[+] KCP layer hooks removed");
        }
        else if (strcmp(sub, "sniff") == 0) {
            g_RawSnifferEnabled = true;
            g_RawLogToConsole = true;
            CmdLog("[+] Raw packet logging ON (use 'kcp quiet' to silence)");
        }
        else if (strcmp(sub, "quiet") == 0) {
            g_RawLogToConsole = false;
            CmdLog("[+] Raw console logging OFF (still capturing)");
        }
        else if (strcmp(sub, "stats") == 0) {
            PrintBandwidthStats();
        }
        else if (strcmp(sub, "drop") == 0) {
            char what[32] = {};
            sscanf_s(arg1 + 5, "%31s", what, (unsigned)sizeof(what));
            if (strcmp(what, "out") == 0) {
                g_DropOutgoing = !g_DropOutgoing;
                CmdLog("[+] Drop outgoing: %s", g_DropOutgoing ? "ON" : "OFF");
            }
            else if (strcmp(what, "in") == 0) {
                g_DropIncoming = !g_DropIncoming;
                CmdLog("[+] Drop incoming: %s", g_DropIncoming ? "ON" : "OFF");
            }
            else if (strcmp(what, "unrel") == 0) {
                g_DropOutgoingUnreliable = !g_DropOutgoingUnreliable;
                CmdLog("[+] Drop unreliable out: %s", g_DropOutgoingUnreliable ? "ON" : "OFF");
            }
            else CmdLog("[!] kcp drop out/in/unrel");
        }
        else if (strcmp(sub, "antitimeout") == 0) {
            g_AntiTimeoutEnabled = !g_AntiTimeoutEnabled;
            if (g_AntiTimeoutEnabled && !g_HandleTimeoutHooked) InstallKcpHooks();
            CmdLog("[+] Anti-timeout: %s", g_AntiTimeoutEnabled ? "ON" : "OFF");
        }
        else if (strcmp(sub, "packets") == 0) {
            int count = 20;
            sscanf_s(arg1 + 8, "%d", &count);
            if (count > g_PacketLogCount) count = g_PacketLogCount;
            if (count > 50) count = 50;

            CmdLog("=== LAST %d PACKETS ===", count);
            for (int i = 0; i < count; i++) {
                int idx = (g_PacketLogHead - 1 - i + 2048) % 2048;
                auto& p = g_PacketLog[idx];

                char hex[96] = {};
                int hp = 0;
                int n = p.dataSize > 24 ? 24 : p.dataSize;
                for (int j = 0; j < n; j++)
                    hp += snprintf(hex + hp, sizeof(hex) - hp, "%02X ", p.data[j]);

                CmdLog("  %s ch=%d %4d bytes | %s%s",
                    p.isOutgoing ? "OUT" : " IN",
                    p.channel, p.dataSize, hex,
                    p.dataSize > 24 ? "..." : "");
            }
        }
        else if (strcmp(sub, "speed") == 0) {
            int mult = 1;
            sscanf_s(arg1 + 6, "%d", &mult);
            if (mult < 1) mult = 1;
            if (mult > 10) mult = 10;
            g_SpeedMultiplier = mult;
            CmdLog("[+] Speed multiplier: %dx", mult);
            if (mult > 1 && !g_KcpLateUpdateHooked) {
                g_KcpLateUpdateAddr = (void*)((uintptr_t)g_GameAssembly + KCP_TRANSPORT_CLIENT_LATEUPDATE_OFFSET);
                InstallHook(g_KcpLateUpdateAddr, &Hook_KcpTransport_ClientLateUpdate, g_KcpLateUpdateOrig);
                g_KcpLateUpdateHooked = true;
            }
        }
    }
    //================telepathy=======================
    else if (strcmp(command, "tcp") == 0) {
        char sub[64] = {}, subarg[256] = {};
        sscanf_s(arg1, "%63s %255[^\n]", sub, (unsigned)sizeof(sub),
            subarg, (unsigned)sizeof(subarg));

        if (strcmp(sub, "on") == 0) {
            InstallTelepathyHooks();
        }
        else if (strcmp(sub, "off") == 0) {
            RemoveTelepathyHooks();
        }
        else if (strcmp(sub, "antikick") == 0) {
            g_TcpDropDisconnect = !g_TcpDropDisconnect;
            if (g_TcpDropDisconnect && !g_RecvEnqueueHooked) InstallTelepathyHooks();
            CmdLog("[+] TCP disconnect blocking: %s", g_TcpDropDisconnect ? "ON" : "OFF");
        }
        else if (strcmp(sub, "desync") == 0) {
            g_TcpDropAllIncoming = !g_TcpDropAllIncoming;
            if (g_TcpDropAllIncoming && !g_RecvEnqueueHooked) InstallTelepathyHooks();
            CmdLog("[+] TCP full desync: %s", g_TcpDropAllIncoming ? "ON" : "OFF");
        }
        else if (strcmp(sub, "mute") == 0) {
            g_TcpDropOutgoing = !g_TcpDropOutgoing;
            if (g_TcpDropOutgoing && !g_SendEnqueueHooked) InstallTelepathyHooks();
            CmdLog("[+] TCP outgoing mute: %s", g_TcpDropOutgoing ? "ON" : "OFF");
        }
        else if (strcmp(sub, "blockmsg") == 0) {
            int msgId = 0;
            if (sscanf_s(subarg, "%i", &msgId) == 1 && g_BlockedMsgIdCount < 32) {
                g_BlockedMsgIds[g_BlockedMsgIdCount++] = (uint16_t)msgId;
                const char* name = LookupMirrorMsg((uint16_t)msgId);
                CmdLog("[+] Blocking Mirror msg 0x%04X (%s)", msgId, name ? name : "unknown");
            }
            else CmdLog("[!] tcp blockmsg <msgId>  (e.g. tcp blockmsg 0x000A)");
        }
        else if (strcmp(sub, "unblockmsg") == 0) {
            if (strcmp(subarg, "all") == 0) {
                g_BlockedMsgIdCount = 0;
                CmdLog("[+] All TCP msg blocks cleared");
            }
            else {
                int msgId = 0;
                if (sscanf_s(subarg, "%i", &msgId) == 1) {
                    for (int i = 0; i < g_BlockedMsgIdCount; i++) {
                        if (g_BlockedMsgIds[i] == (uint16_t)msgId) {
                            g_BlockedMsgIds[i] = g_BlockedMsgIds[--g_BlockedMsgIdCount];
                            CmdLog("[+] Unblocked msg 0x%04X", msgId);
                            break;
                        }
                    }
                }
                else CmdLog("[!] tcp unblockmsg <msgId>/all");
            }
        }
        else if (strcmp(sub, "stats") == 0) {
            CmdLog("=== TCP STATS ===");
            CmdLog("  Sent: %llu bytes, %u pkt/s", g_TcpBytesSent, g_TcpPktSentPerSec);
            CmdLog("  Recv: %llu bytes, %u pkt/s", g_TcpBytesRecv, g_TcpPktRecvPerSec);
            CmdLog("  Client: 0x%p", g_TeleClientInstance);
            CmdLog("  Blocked msgs: %d", g_BlockedMsgIdCount);
            for (int i = 0; i < g_BlockedMsgIdCount; i++) {
                const char* n = LookupMirrorMsg(g_BlockedMsgIds[i]);
                CmdLog("    0x%04X (%s)", g_BlockedMsgIds[i], n ? n : "unknown");
            }
        }
        else if (strcmp(sub, "msgs") == 0) {
            CmdLog("=== KNOWN MIRROR MESSAGES ===");
            for (int i = 0; g_KnownMsgs[i].name; i++)
                CmdLog("  0x%04X = %s", g_KnownMsgs[i].id, g_KnownMsgs[i].name);
        }
        else {
            CmdLog("=== TCP (TELEPATHY) ===");
            CmdLog("  tcp on/off            Install/remove hooks");
            CmdLog("  tcp antikick          Block TCP disconnect events");
            CmdLog("  tcp desync            Block ALL incoming TCP data");
            CmdLog("  tcp mute              Block ALL outgoing TCP data");
            CmdLog("  tcp blockmsg <id>     Block specific Mirror message");
            CmdLog("  tcp unblockmsg <id>/all  Unblock message");
            CmdLog("  tcp stats             Show TCP stats");
            CmdLog("  tcp msgs              List known Mirror message IDs");
        }
    }
    // =============== BLOCK / UNBLOCK ===============
    else if (strcmp(command, "block") == 0) {
        int hash = 0;
        char label[64] = {};
        int parsed = sscanf_s(arg1, "%i %63[^\n]", &hash, label, (unsigned)sizeof(label));

        if (parsed >= 1 && g_BlockedCount < 256) {
            // Check if already exists
            bool found = false;
            for (int i = 0; i < g_BlockedCount; i++) {
                if (g_Blocked[i].hash == (uint16_t)hash) {
                    g_Blocked[i].enabled = true;
                    CmdLog("[+] Re-enabled block 0x%04X", hash);
                    found = true;
                    break;
                }
            }
            if (!found) {
                auto& b = g_Blocked[g_BlockedCount++];
                b.hash = (uint16_t)hash;
                b.blockCount = 0;
                b.enabled = true;
                if (label[0]) strcpy_s(b.label, label);
                else snprintf(b.label, 64, "rpc_%04X", hash);
                CmdLog("[+] Blocking 0x%04X (%s)", hash, b.label);
            }

            if (!g_PCEnabled) {
                InstallAllPCHooks();
                g_PCEnabled = true;
                CmdLog("[*] Packet Canceller auto-enabled");
            }
        }
        else CmdLog("[!] block <hash> [label]  (e.g. block 0x1234 damage)");
    }
    else if (strcmp(command, "unblock") == 0) {
        if (strcmp(arg1, "all") == 0) {
            for (int i = 0; i < g_BlockedCount; i++) g_Blocked[i].enabled = false;
            CmdLog("[+] All %d blocks disabled", g_BlockedCount);
        }
        else {
            int hash = 0;
            if (sscanf_s(arg1, "%i", &hash) == 1) {
                for (int i = 0; i < g_BlockedCount; i++) {
                    if (g_Blocked[i].hash == (uint16_t)hash) {
                        g_Blocked[i].enabled = false;
                        CmdLog("[+] Unblocked 0x%04X (%s)", hash, g_Blocked[i].label);
                        break;
                    }
                }
            }
            else CmdLog("[!] unblock <hash> / unblock all");
        }
    }
    else if (strcmp(command, "resolve") == 0) {
        int hash = 0;
        if (sscanf_s(arg1, "%i", &hash) == 1) {
            CmdLog("[*] Resolving 0x%04X...", hash);

            // Method 1: Direct call
            Il2CppString* nameStr = nullptr;
            __try {
                bool ok = GetFunctionMethodName((uint16_t)hash, &nameStr);
                CmdLog("[*] GetFunctionMethodName returned %d, str=0x%p", ok, nameStr);
                if (nameStr) {
                    char buf[256] = {};
                    if (SafeReadString(nameStr, buf, 256))
                        CmdLog("[+] Name: %s", buf);
                    else
                        CmdLog("[-] String read failed");
                }
            }
            __except (1) {
                CmdLog("[-] Crashed (wrong calling convention?)");
            }

            // Method 2: GetDelegate
            constexpr uintptr_t GET_DELEGATE_OFFSET = 0x136BE90;
            typedef void* (__cdecl* GetDelegate_t)(uint16_t);
            GetDelegate_t GetDelegate = (GetDelegate_t)((uintptr_t)g_GameAssembly + GET_DELEGATE_OFFSET);

            __try {
                void* del = GetDelegate((uint16_t)hash);
                CmdLog("[*] GetDelegate = 0x%p", del);
            }
            __except (1) {
                CmdLog("[-] GetDelegate crashed");
            }

            // Method 3: GetInvokerForHash
            constexpr uintptr_t GET_INVOKER_OFFSET = 0x136C080;
            typedef bool(__cdecl* GetInvoker_t)(uint16_t, int, void*);
            GetInvoker_t GetInvoker = (GetInvoker_t)((uintptr_t)g_GameAssembly + GET_INVOKER_OFFSET);

            uint8_t invokerBuf[128] = {};
            __try {
                // Try RemoteCallType = 1 (ClientRpc)
                bool ok = GetInvoker((uint16_t)hash, 1, invokerBuf);
                CmdLog("[*] GetInvokerForHash(Rpc) = %d", ok);
                if (ok) {
                    // Invoker struct: 
                    // +0x00: Type invokeClass
                    // +0x08: string functionName
                    // +0x10: RemoteCallDelegate
                    // +0x18: bool cmdRequiresAuthority
                    // +0x19: RemoteCallType callType
                    for (uintptr_t off = 0; off <= 0x20; off += 8) {
                        void* ptr = *(void**)(invokerBuf + off);
                        if (ptr) {
                            char buf[256] = {};
                            if (SafeReadString((Il2CppString*)ptr, buf, 256) && buf[0])
                                CmdLog("[+] Invoker+0x%X string: %s", (int)off, buf);
                        }
                    }
                }

                // Try RemoteCallType = 0 (Command)
                ok = GetInvoker((uint16_t)hash, 0, invokerBuf);
                CmdLog("[*] GetInvokerForHash(Cmd) = %d", ok);
                if (ok) {
                    for (uintptr_t off = 0; off <= 0x20; off += 8) {
                        void* ptr = *(void**)(invokerBuf + off);
                        if (ptr) {
                            char buf[256] = {};
                            if (SafeReadString((Il2CppString*)ptr, buf, 256) && buf[0])
                                CmdLog("[+] Invoker+0x%X string: %s", (int)off, buf);
                        }
                    }
                }
            }
            __except (1) {
                CmdLog("[-] GetInvoker crashed");
            }
        }
        else CmdLog("[!] resolve <hash>  (e.g. resolve 0x6F28)");
    }
    else if (strcmp(command, "blocks") == 0) {
        CmdLog("=== BLOCKED RPCs (%d) ===", g_BlockedCount);
        for (int i = 0; i < g_BlockedCount; i++) {
            CmdLog("  [%s] 0x%04X  %-20s  blocked %d times",
                g_Blocked[i].enabled ? "ON " : "OFF",
                g_Blocked[i].hash,
                g_Blocked[i].label,
                g_Blocked[i].blockCount);
        }
    }
    // =============== DESYNC ===============
    else if (strcmp(command, "desync") == 0) {
        if (strcmp(arg1, "on") == 0) {
            InstallAllPCHooks();
            g_PCEnabled = true;
            g_FullDesyncEnabled = true;
            g_SyncVarBlockAll = true;
            CmdLog("[+] FULL DESYNC — ALL RPCs and SyncVars blocked");
        }
        else if (strcmp(arg1, "off") == 0) {
            g_FullDesyncEnabled = false;
            g_SyncVarBlockAll = false;
            CmdLog("[+] DESYNC OFF");
        }
        else if (strcmp(arg1, "rpc") == 0) {
            InstallAllPCHooks();
            g_PCEnabled = true;
            g_FullDesyncEnabled = true;
            g_SyncVarBlockAll = false;
            CmdLog("[+] RPC DESYNC — RPCs blocked, SyncVars pass");
        }
        else if (strcmp(arg1, "sync") == 0) {
            InstallAllPCHooks();
            g_PCEnabled = true;
            g_FullDesyncEnabled = false;
            g_SyncVarBlockAll = true;
            CmdLog("[+] SYNC DESYNC — SyncVars blocked, RPCs pass");
        }
        else CmdLog("[!] desync on/off/rpc/sync");
    }
    // =============== AUTO-BLOCK ===============
    else if (strcmp(command, "autoblock") == 0) {
        if (strcmp(arg1, "on") == 0) {
            InstallAllPCHooks();
            g_PCEnabled = true;
            g_PCAutoBlock = true;
            g_PCLogging = true;
            CmdLog("[+] AUTO-BLOCK ON — every new RPC will be blocked");
            CmdLog("[!] Useful: enable, take damage, see what gets blocked");
        }
        else if (strcmp(arg1, "off") == 0) {
            g_PCAutoBlock = false;
            CmdLog("[+] AUTO-BLOCK OFF");
        }
        else CmdLog("[!] autoblock on/off");
    }
    // =============== RECENT LOG ===============
    else if (strcmp(command, "recent") == 0) {
        int count = 20;
        if (arg1[0]) count = atoi(arg1);
        if (count > g_RpcLogCount) count = g_RpcLogCount;
        if (count > 100) count = 100;

        CmdLog("=== RECENT RPCs (last %d) ===", count);
        for (int i = 0; i < count; i++) {
            int idx = (g_RpcLogHead - 1 - i + 512) % 512;
            auto& e = g_RpcLog[idx];

            const char* t = "???";
            switch (e.callType) {
            case 0: t = "Cmd"; break;
            case 1: t = "Rpc"; break;
            case 2: t = "TgtRpc"; break;
            }

            // Resolve name
            const char* name = ResolveRpcHash(e.hash);

            if (name && name[0] && strcmp(name, "???") != 0)
                CmdLog("  %s 0x%04X %-35s nid=%-4u %s",
                    t, e.hash, name, e.netId, e.wasBlocked ? "[BLOCKED]" : "");
            else
                CmdLog("  %s 0x%04X %-35s nid=%-4u %s",
                    t, e.hash, "(unknown)", e.netId, e.wasBlocked ? "[BLOCKED]" : "");
        }
    }
    // =============== FIND RPCs BY ACTION ===============
    else if (strcmp(command, "learn") == 0) {
        if (strcmp(arg1, "start") == 0) {
            // Clear log and start fresh
            g_RpcLogCount = 0;
            g_RpcLogHead = 0;
            InstallAllPCHooks();
            g_PCEnabled = true;
            g_PCLogging = false;  // quiet mode
            CmdLog("[+] LEARN MODE — do the action in game, then 'learn stop'");
            CmdLog("[!] Example: 'learn start' → get hit → 'learn stop'");
        }
        else if (strcmp(arg1, "stop") == 0) {
            CmdLog("[+] LEARN STOP — %d RPCs recorded:", g_RpcLogCount);

            uint16_t seen[256];
            int seenCount = 0;

            for (int i = 0; i < g_RpcLogCount; i++) {
                uint16_t h = g_RpcLog[i].hash;
                bool dup = false;
                for (int j = 0; j < seenCount; j++) {
                    if (seen[j] == h) { dup = true; break; }
                }
                if (!dup && seenCount < 256) {
                    seen[seenCount++] = h;

                    int occ = 0;
                    for (int j = 0; j < g_RpcLogCount; j++) {
                        if (g_RpcLog[j].hash == h) occ++;
                    }

                    const char* t = "???";
                    switch (g_RpcLog[i].callType) {
                    case 0: t = "Cmd"; break;
                    case 1: t = "Rpc"; break;
                    case 2: t = "TgtRpc"; break;
                    }

                    // Resolve name
                    const char* name = ResolveRpcHash(h);
                    if (name && name[0] && strcmp(name, "???") != 0)
                        CmdLog("  %s 0x%04X  %-40s  (%d times)", t, h, name, occ);
                    else
                        CmdLog("  %s 0x%04X  %-40s  (%d times)", t, h, "(unknown)", occ);
                }
            }
            CmdLog("[*] Use 'block 0x<hash> <label>' to block any of these");
        }
        else CmdLog("[!] learn start/stop");
    }

    else if (strcmp(command, "rpcnames") == 0) {
        if (strcmp(arg1, "dump") == 0) {
            DumpAllRpcNames();
        }
        else if (strcmp(arg1, "list") == 0) {
            CmdLog("[*] Cached: %d", g_RpcNameCount);
            for (int i = 0; i < g_RpcNameCount; i++) {
                CmdLog("  0x%04X = %-40s %s",
                    g_RpcNames[i].hash, g_RpcNames[i].name,
                    g_RpcNames[i].requiresAuth ? "[AUTH]" : "[NO AUTH]");
            }
        }
        else {
            CmdLog("[!] rpcnames dump    - scan ALL 65536 hashes (slow but complete)");
            CmdLog("[!] rpcnames list    - show cached names");
        }
    }

    else if (strcmp(command, "elogger") == 0) {
        if (strcmp(arg1, "on") == 0) EnableEventLogger();
        else if (strcmp(arg1, "off") == 0) DisableEventLogger();
        else CmdLog("[!] elogger on/off");
    }
    else if (strcmp(command, "exec") == 0) {
        if (!arg1[0]) { CmdLog("[!] exec <url>"); return; }
        CmdLog("[*] Getting %s...", arg1);
        static char httpBuf[512000];
        if (!HttpGet(arg1, httpBuf, sizeof(httpBuf))) { CmdLog("[-] Failed"); return; }
        int len = (int)strlen(httpBuf);
        CmdLog("[+] %d bytes", len);
        EnsureScriptService();
        if (!g_ScriptService) { CmdLog("[-] No SS"); return; }
        void* script = nullptr;
        __try { script = Instance_New(il2cpp_string_new("ScriptInstance"), g_ScriptService); }
        __except (1) { CmdLog("[-] Crash"); return; }
        if (!script) { CmdLog("[-] Failed"); return; }
        __try { BaseScript_set_Source(script, il2cpp_string_new(httpBuf)); CmdLog("[+] Executed!"); }
        __except (1) { CmdLog("[-] Failed"); }
    }
    else if (strcmp(command, "saveall") == 0) {
        SaveAllScripts();
    }
    // ===== NEW COMMANDS =====
    else if (strcmp(command, "discover") == 0) {
        if (DiscoverNetIdOffsets()) CmdLog("[+] Ready.");
    }
    else if (strcmp(command, "scan") == 0) {
        ScanPlayers();
    }
    else if (strcmp(command, "sniff") == 0) {
        if (strcmp(arg1, "on") == 0) EnableCmdSniffer();
        else if (strcmp(arg1, "off") == 0) DisableCmdSniffer();
        else CmdLog("[!] sniff on/off");
    }
    else if (strcmp(command, "captures") == 0) {
        CmdLog("[*] %d captured:", g_CapturedCmdCount);
        for (int i = 0; i < g_CapturedCmdCount; i++) {
            auto& c = g_CapturedCmds[i];
            CmdLog("  #%d hash=0x%08X fn=%s netId=%u size=%d",
                i, c.hash, c.funcName, c.fromNetId, c.payloadSize);
        }
    }
    else if (strcmp(command, "clear") == 0) {
        SetWindowTextA(g_CmdOutput, "");
    }
    else if (strcmp(command, "help") == 0) {
        CmdLog("============== MONITOR =============");
        CmdLog("  netmon              Open Network Monitor window");
        CmdLog("========= PACKET TAMPERING =========");
        CmdLog("  pc on/off/quiet/loud   Main switch");
        CmdLog("  antikick on/off        Cancel disconnection packets");
        CmdLog("  block <hash> [label]   Block specific RPC");
        CmdLog("  unblock <hash>/all     Unblock RPC");
        CmdLog("  blocks                 List all blocks");
        CmdLog("  autoblock on/off       Auto-block new RPCs");
        CmdLog("  desync on/off/rpc/sync Full server block");
        CmdLog("  recent [n]             Show recent RPCs");
        CmdLog("  learn start/stop       Record RPCs from action");
        CmdLog("======= KCP TRANSPORT LAYER =========");
        CmdLog("  kcp on/off           Install/remove hooks");
        CmdLog("  kcp sniff            Log all raw packets");
        CmdLog("  kcp quiet            Stop console spam");
        CmdLog("  kcp stats            Bandwidth monitor");
        CmdLog("  kcp packets [n]      Show last N raw packets");
        CmdLog("  kcp drop out/in/unrel  Toggle packet dropping");
        CmdLog("  kcp antitimeout      Prevent timeout disconnect");
        CmdLog("  kcp speed <1-10>     Packet tick multiplier");
        CmdLog("======== TRANSPORT LAYER =============");
        CmdLog("  kcp ...             UDP transport hooks");
        CmdLog("  tcp ...             TCP transport hooks");
        CmdLog("========= RPC NAMES ===============");
        CmdLog("  rpcnames dump     Dump ALL RPC/Cmd names");
        CmdLog("  rpcnames list     Show cached");
        CmdLog("========= NETWORK =================");
        CmdLog("  discover    Find netId offsets");
        CmdLog("  scan        List players");
        CmdLog("  sniff on/off  Capture outgoing Cmds");
        CmdLog("  captures    List captured Cmds");
        CmdLog("========= SCRIPTING ================");
        CmdLog("  cleanup             Destroy all created ScriptInstances");
        CmdLog("  autoclean on/off    Auto-destroy previous before new exec");
        CmdLog("========== GAME ===================");
        CmdLog("  sh <hp>     Set your own health");
        CmdLog("  elogger     NetworkEvent logger");
        CmdLog("  exec <url>  Execute script from URL");
        CmdLog("  saveall     Save all game scripts");
        CmdLog("  clear       Clear output");
    }
    else {
        CmdLog("[-] Unknown: '%s'. Type 'help'.", command);
    }
}


void LoadSelectedScript() {
    int sel = (int)SendMessage(g_ScriptListBox, LB_GETCURSEL, 0, 0);
    if (sel < 0 || sel >= g_ScriptFileCount) return;

    auto& sf = g_ScriptFiles[sel];
    std::string content = ReadFileContents(sf.fullpath);
    if (content.empty()) {
        Log("[-] Failed to read: %s", sf.fullpath);
        return;
    }

    // Сохраняем текущий таб перед заменой
    SaveCurrentTabContent();

    // Обновляем имя таба
    strncpy_s(g_ScriptTabs[g_CurrentScriptTab].title, sf.filename, 63);
    TCITEMA tie = {};
    tie.mask = TCIF_TEXT;
    tie.pszText = g_ScriptTabs[g_CurrentScriptTab].title;
    TabCtrl_SetItem(g_ScriptTabControl, g_CurrentScriptTab, &tie);

    // Загружаем в редактор (лимит 512КБ установлен при создании)
    SetWindowTextA(g_ScriptEdit, content.c_str());

    // Обновляем буфер таба
    if (g_ScriptTabs[g_CurrentScriptTab].buffer) {
        free(g_ScriptTabs[g_CurrentScriptTab].buffer);
    }
    g_ScriptTabs[g_CurrentScriptTab].bufferSize = content.size() + 4096;
    g_ScriptTabs[g_CurrentScriptTab].buffer = (char*)malloc(g_ScriptTabs[g_CurrentScriptTab].bufferSize);
    strcpy_s(g_ScriptTabs[g_CurrentScriptTab].buffer, g_ScriptTabs[g_CurrentScriptTab].bufferSize, content.c_str());

    Log("[+] Loaded: %s (%d bytes)", sf.filename, (int)content.size());
    UpdateScriptStatus(sf.filename);
}

void OpenScriptsFolder() {
    ShellExecuteA(nullptr, "open", g_ScriptsDir, nullptr, nullptr, SW_SHOW);
}

void SaveTabToFile(int idx) {
    if (idx < 0 || idx >= g_ScriptTabCount) return;
    auto& tab = g_ScriptTabs[idx];

    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "%s\\tab_%d.lua", g_TabsDir, idx);

    FILE* f = nullptr;
    fopen_s(&f, path, "w");
    if (!f) return;

    // Первая строка = title
    fprintf(f, "-- TAB_TITLE: %s\n", tab.title);

    if (tab.buffer && tab.buffer[0]) {
        fwrite(tab.buffer, 1, strlen(tab.buffer), f);
    }
    fclose(f);
}

void SaveAllTabs() {
    // Сохраняем текущий контент
    SaveCurrentTabContent();

    // Удаляем старые файлы табов
    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\tab_*.lua", g_TabsDir);
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPath, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            char fullpath[MAX_PATH];
            snprintf(fullpath, MAX_PATH, "%s\\%s", g_TabsDir, fd.cFileName);
            DeleteFileA(fullpath);
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
    }

    // Сохраняем текущие табы
    for (int i = 0; i < g_ScriptTabCount; i++) {
        SaveTabToFile(i);
    }

    // Сохраняем метаданные
    char metaPath[MAX_PATH];
    snprintf(metaPath, MAX_PATH, "%s\\meta.txt", g_TabsDir);
    FILE* f = nullptr;
    fopen_s(&f, metaPath, "w");
    if (f) {
        fprintf(f, "%d\n%d\n", g_ScriptTabCount, g_CurrentScriptTab);
        fclose(f);
    }
}

void LoadAllTabs() {
    char metaPath[MAX_PATH];
    snprintf(metaPath, MAX_PATH, "%s\\meta.txt", g_TabsDir);

    FILE* f = nullptr;
    fopen_s(&f, metaPath, "r");
    if (!f) {
        // Нет сохранённых табов — создаём дефолтный
        AddScriptTab("Script 1", "print('Hello World!')");
        return;
    }

    int tabCount = 0, currentTab = 0;
    fscanf_s(f, "%d\n%d\n", &tabCount, &currentTab);
    fclose(f);

    if (tabCount <= 0 || tabCount > MAX_SCRIPT_TABS) {
        AddScriptTab("Script 1", "print('Hello World!')");
        return;
    }

    for (int i = 0; i < tabCount; i++) {
        char path[MAX_PATH];
        snprintf(path, MAX_PATH, "%s\\tab_%d.lua", g_TabsDir, i);

        std::string content = ReadFileContents(path);

        // Извлекаем title из первой строки
        char title[64] = {};
        snprintf(title, sizeof(title), "Script %d", i + 1);

        if (content.size() > 15) {
            const char* prefix = "-- TAB_TITLE: ";
            if (content.compare(0, strlen(prefix), prefix) == 0) {
                size_t end = content.find('\n');
                if (end != std::string::npos) {
                    std::string t = content.substr(strlen(prefix), end - strlen(prefix));
                    strncpy_s(title, t.c_str(), 63);
                    content = content.substr(end + 1);
                }
            }
        }

        AddScriptTab(title, content.c_str());
    }

    if (currentTab >= 0 && currentTab < g_ScriptTabCount) {
        g_CurrentScriptTab = currentTab;
        TabCtrl_SetCurSel(g_ScriptTabControl, currentTab);
        LoadTabContent(currentTab);
    }
}

void NetMonContextMenu(int x, int y) {
    int sel = ListView_GetNextItem(g_NetMonListView, -1, LVNI_SELECTED);
    if (sel < 0) return;

    // Get hash from selected row
    char hashBuf[32] = {};
    ListView_GetItemText(g_NetMonListView, sel, 4, hashBuf, 32);
    uint16_t hash = (uint16_t)strtoul(hashBuf, nullptr, 16);

    HMENU menu = CreatePopupMenu();
    AppendMenuA(menu, MF_STRING, 1, "View Detail");
    AppendMenuA(menu, MF_SEPARATOR, 0, nullptr);

    char blockLabel[128];
    snprintf(blockLabel, sizeof(blockLabel), "Block 0x%04X", hash);
    AppendMenuA(menu, MF_STRING, 2, blockLabel);

    snprintf(blockLabel, sizeof(blockLabel), "Unblock 0x%04X", hash);
    AppendMenuA(menu, MF_STRING, 3, blockLabel);

    AppendMenuA(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuA(menu, MF_STRING, 4, "Copy Hash");
    AppendMenuA(menu, MF_STRING, 5, "Copy Row");
    AppendMenuA(menu, MF_STRING, 6, "Copy Hex Dump");

    POINT pt = { x, y };
    ClientToScreen(g_NetMonListView, &pt);
    int cmd = TrackPopupMenu(menu, TPM_RETURNCMD, pt.x, pt.y, 0, g_NetMonWindow, nullptr);
    DestroyMenu(menu);

    switch (cmd) {
    case 1: ShowPacketDetail(sel); break;
    case 2: {
        char cmdBuf[128];
        snprintf(cmdBuf, sizeof(cmdBuf), "block 0x%04X", hash);
        ProcessCommand(cmdBuf);
        break;
    }
    case 3: {
        char cmdBuf[128];
        snprintf(cmdBuf, sizeof(cmdBuf), "unblock 0x%04X", hash);
        ProcessCommand(cmdBuf);
        break;
    }
    case 4: {
        char clip[32];
        snprintf(clip, sizeof(clip), "0x%04X", hash);
        if (OpenClipboard(g_NetMonWindow)) {
            EmptyClipboard();
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(clip) + 1);
            memcpy(GlobalLock(hg), clip, strlen(clip) + 1);
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
            CloseClipboard();
        }
        break;
    }
    case 5: {
        char row[1024] = {};
        int p = 0;
        for (int col = 0; col < 10; col++) {
            char cell[256] = {};
            ListView_GetItemText(g_NetMonListView, sel, col, cell, 256);
            p += snprintf(row + p, sizeof(row) - p, "%s\t", cell);
        }
        if (OpenClipboard(g_NetMonWindow)) {
            EmptyClipboard();
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(row) + 1);
            memcpy(GlobalLock(hg), row, strlen(row) + 1);
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
            CloseClipboard();
        }
        break;
    }
    case 6: {
        char idxBuf[32] = {};
        ListView_GetItemText(g_NetMonListView, sel, 0, idxBuf, 32);
        int logIdx = atoi(idxBuf);
        int realIdx = (g_NetLogHead - g_NetLogCount + logIdx + NETLOG_SIZE) % NETLOG_SIZE;
        auto& e = g_NetLog[realIdx];
        if (e.detail[0] && OpenClipboard(g_NetMonWindow)) {
            EmptyClipboard();
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(e.detail) + 1);
            memcpy(GlobalLock(hg), e.detail, strlen(e.detail) + 1);
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
            CloseClipboard();
        }
        break;
    }
    }
}



// ==================== WNDPROC ====================

LRESULT CALLBACK NetMonWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_USER + 1:  // Update notification
        NetMonRefresh();
        return 0;

    case WM_NOTIFY: {
        NMHDR* nm = (NMHDR*)lp;
        if (nm->idFrom == ID_NETMON_TAB && nm->code == TCN_SELCHANGE) {
            g_NetMonCurrentTab = TabCtrl_GetCurSel(g_NetMonTabControl);
            NetMonRefresh(true);  // full refresh on tab change
        }
        else if (nm->idFrom == ID_NETMON_LISTVIEW) {
            if (nm->code == NM_DBLCLK) {
                NMITEMACTIVATE* nia = (NMITEMACTIVATE*)lp;
                if (nia->iItem >= 0) ShowPacketDetail(nia->iItem);
            }
            else if (nm->code == NM_RCLICK) {
                NMITEMACTIVATE* nia = (NMITEMACTIVATE*)lp;
                if (nia->iItem >= 0) {
                    NetMonContextMenu(nia->ptAction.x, nia->ptAction.y);
                }
            }
        }
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_NETMON_PAUSE:
            g_NetMonPaused = !g_NetMonPaused;
            SetWindowTextA(g_NetMonBtnPause,
                g_NetMonPaused ? "Resume" : "Pause");
            if (!g_NetMonPaused) NetMonRefresh();
            break;

        case ID_NETMON_CLEAR:
            EnterCriticalSection(&g_NetLogCS);
            g_NetLogCount = 0;
            g_NetLogHead = 0;
            g_NetMonLastCount = 0;
            LeaveCriticalSection(&g_NetLogCS);
            ListView_DeleteAllItems(g_NetMonListView);
            break;

        case ID_NETMON_EXPORT:
            NetMonExport();
            break;

        case ID_NETMON_AUTOSCROLL:
            g_NetMonAutoScroll = !g_NetMonAutoScroll;
            SetWindowTextA(g_NetMonBtnAutoScroll,
                g_NetMonAutoScroll ? "Scroll:ON" : "Scroll:OFF");
            break;

        case ID_NETMON_FILTER:
            if (HIWORD(wp) == EN_CHANGE) {
                NetMonRefresh(true);
            }
            break;
        }
        break;

    case WM_SIZE: {
        int w = LOWORD(lp), h = HIWORD(lp);
        MoveWindow(g_NetMonTabControl, 0, 0, w, 30, TRUE);
        MoveWindow(g_NetMonFilterEdit, 340, 3, w - 350, 22, TRUE);
        MoveWindow(g_NetMonListView, 0, 30, w, h - 60, TRUE);

        // Bottom bar
        int btnY = h - 28;
        MoveWindow(g_NetMonBtnPause, 5, btnY, 60, 24, TRUE);
        MoveWindow(g_NetMonBtnClear, 70, btnY, 55, 24, TRUE);
        MoveWindow(g_NetMonBtnExport, 130, btnY, 60, 24, TRUE);
        MoveWindow(g_NetMonBtnAutoScroll, 195, btnY, 80, 24, TRUE);
        MoveWindow(g_NetMonStatusBar, 290, btnY + 2, w - 300, 20, TRUE);
        break;
    }

    case WM_CLOSE:
        ShowWindow(hwnd, SW_HIDE);  // Скрываем а не уничтожаем
        return 0;

    case WM_DESTROY:
        g_NetMonWindow = nullptr;
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}


void OnCmdSend() {
    char input[512] = {};
    GetWindowTextA(g_CmdInput, input, 512);
    char* s = input;
    while (*s == ' ') s++;
    if (!*s) return;
    ProcessCommand(s);
    SetWindowTextA(g_CmdInput, "");
    SetFocus(g_CmdInput);
}
void CleanupPreviousScript() {
    // Удаляем ПРЕДЫДУЩИЙ скрипт перед созданием нового
    if (!g_AutoCleanup) return;
    if (g_CurrentScript) {
        __try {
            Instance_Destroy(g_CurrentScript, 0);
        }
        __except (1) {}

        // Убираем из трекера
        for (int i = 0; i < g_CreatedScriptCount; i++) {
            if (g_CreatedScripts[i] == g_CurrentScript) {
                g_CreatedScripts[i] = nullptr;
                break;
            }
        }
        g_CurrentScript = nullptr;
    }
}

void TrackScript(void* script) {
    if (g_CreatedScriptCount < 128) {
        g_CreatedScripts[g_CreatedScriptCount++] = script;
    }
}

void ExecuteScriptFromString(const std::string& source) {
    if (source.empty()) { Log("[-] Empty!"); return; }
    EnsureScriptService();
    if (!g_ScriptService) { Log("[-] No SS!"); return; }

    CleanupPreviousScript();

    void* script = nullptr;
    Log("[*] Executing (%d chars)...", (int)source.size());
    __try {
        script = Instance_New(il2cpp_string_new("ScriptInstance"), g_ScriptService);
    }
    __except (1) { Log("[-] Crash!"); return; }

    if (!script) { Log("[-] Failed!"); return; }
    g_CurrentScript = script;
    TrackScript(script);
    Log("[+] @ 0x%p", script);

    // Запускаем скрипт
    __try {
        BaseScript_set_Source(script, il2cpp_string_new(source.c_str()));
        Log("[+] Executed!");
        UpdateScriptStatus("OK");
    }
    __except (1) {
        Log("[-] Script crashed!");
        UpdateScriptStatus("Failed");
    }

    /* == = ИНЖЕКТ ПОСЛЕ ВЫПОЛНЕНИЯ == =
    // Если во время выполнения скрипта захватили VM -> инжектим хуки
    if (g_MsReady && !g_HookFuncsInjected) {
        EnsureHookFunctionsInjected();
    }*/
}


void ExecuteScript() {
    static DWORD lastExecTime = 0;
    DWORD now = GetTickCount();
    if (now - lastExecTime < 500) return;
    lastExecTime = now;

    // ВСЕГДА читаем из редактора (Visible text)
    int len = GetWindowTextLengthA(g_ScriptEdit);
    if (len <= 0) { Log("[-] Empty!"); return; }

    std::vector<char> buf(len + 1);
    GetWindowTextA(g_ScriptEdit, buf.data(), len + 1);
    std::string source = buf.data();

    // Translation if enabled
    if (g_Lua2LuauEnabled) {
        source = TranslateLuau(source);
    }

    UpdateScriptStatus("Executing...");
    ExecuteScriptFromString(source);
}

void ClearScript() {
    SetWindowTextA(g_ScriptEdit, "");
    // g_LoadedLuaFile.clear(); // Больше не нужно
    g_CurrentScript = nullptr;
    UpdateScriptStatus("Cleared");
}

void LoadFileLua() {
    std::string path = OpenFileDialog(g_Window);
    if (path.empty()) return;
    g_LoadedLuaFile = ReadFileContents(path);
    if (g_LoadedLuaFile.empty()) {
        Log("[-] Failed to read: %s", path.c_str());
        UpdateScriptStatus("Load failed");
        return;
    }
    Log("[+] Loaded: %s (%d bytes)", path.c_str(), (int)g_LoadedLuaFile.size());
    if (g_LoadedLuaFile.size() <= 30000) {
        SetWindowTextA(g_ScriptEdit, g_LoadedLuaFile.c_str());
    }
    else {
        std::string preview = g_LoadedLuaFile.substr(0, 1000) +
            "\n\n-- [FILE TOO LARGE - " + std::to_string(g_LoadedLuaFile.size()) + " bytes]";
        SetWindowTextA(g_ScriptEdit, preview.c_str());
    }
    std::string fname = path.substr(path.find_last_of("\\/") + 1);
    UpdateScriptStatus(("Loaded: " + fname).c_str());
}

// ==================== Explorer ====================
void ShowProperties(void* inst) {
    SendMessage(g_PropertyList, LB_RESETCONTENT, 0, 0);
    if (!inst) return;

    char buf[256], name[128] = {}, cls[64] = {};
    SafeGetName(inst, name, 128);
    SafeGetClassName(inst, cls, 64);
    SetWindowTextA(g_NameEdit, name);

    sprintf_s(buf, "Address: 0x%p", inst);
    SendMessageA(g_PropertyList, LB_ADDSTRING, 0, (LPARAM)buf);
    sprintf_s(buf, "Name: %s", name);
    SendMessageA(g_PropertyList, LB_ADDSTRING, 0, (LPARAM)buf);
    sprintf_s(buf, "ClassName: %s", cls);
    SendMessageA(g_PropertyList, LB_ADDSTRING, 0, (LPARAM)buf);

    void* ch[512];
    int cnt = SafeGetChildren(inst, ch, 512);
    sprintf_s(buf, "Children: %d", cnt);
    SendMessageA(g_PropertyList, LB_ADDSTRING, 0, (LPARAM)buf);
    // В ShowProperties, после строки с Children:
    if (strcmp(cls, "ScriptInstance") == 0 || strcmp(cls, "LocalScript") == 0 || strcmp(cls, "ModuleScript") == 0) {
        SendMessageA(g_PropertyList, LB_ADDSTRING, 0, (LPARAM)"=== Script ===");
        SendMessageA(g_PropertyList, LB_ADDSTRING, 0, (LPARAM)"<double-click to dump Source>");
    }
}

void AddInstanceToTree(HTREEITEM parent, void* inst) {
    if (!inst) return;

    char name[128] = {}, cls[64] = {};
    if (!SafeGetName(inst, name, 128)) strcpy_s(name, "?");
    if (!SafeGetClassName(inst, cls, 64)) strcpy_s(cls, "?");

    char disp[256];
    sprintf_s(disp, "%s [%s]", name, cls);

    TVINSERTSTRUCT tv = {};
    tv.hParent = parent;
    tv.hInsertAfter = TVI_LAST;
    tv.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
    tv.item.pszText = disp;
    tv.item.lParam = (LPARAM)inst;
    
    // Check for children (optimization: just check if count > 0)
    void* tempCh[1]; 
    int childCount = SafeGetChildren(inst, tempCh, 1);
    tv.item.cChildren = (childCount > 0) ? 1 : 0;

    HTREEITEM item = TreeView_InsertItem(g_TreeView, &tv);

    InstanceInfo info;
    info.ptr = inst;
    strcpy_s(info.name, name);
    strcpy_s(info.className, cls);
    info.treeItem = item;
    g_Instances[item] = info;
}

void ExpandTreeItem(HTREEITEM item) {
    // Check if we already loaded children (look for dummy or check if children > 0 but no child items)
    // Actually, TVN_ITEMEXPANDING is simpler.
    // Here we just need to populate.
    
    // Find the instance
    auto it = g_Instances.find(item);
    if (it == g_Instances.end()) return;
    
    void* inst = it->second.ptr;
    if (!inst) return;

    // Check if already populated (check first child)
    HTREEITEM child = TreeView_GetChild(g_TreeView, item);
    if (child) return; // Already populated

    // Fetch children
    void* children[512]; // Batch size
    int cnt = SafeGetChildren(inst, children, 512);
    
    // Optimization: turn off redraw for the item if many children? 
    // Usually Refresh handles the global redraw.
    
    for (int i = 0; i < cnt; i++) {
        AddInstanceToTree(item, children[i]);
    }
}

void Refresh() {
    SendMessage(g_TreeView, WM_SETREDRAW, FALSE, 0);
    TreeView_DeleteAllItems(g_TreeView);
    g_Instances.clear();
    g_SelectedInstance = nullptr;
    g_ScriptService = nullptr;
    g_PlayersInstance = nullptr;
    SendMessage(g_PropertyList, LB_RESETCONTENT, 0, 0);

    g_GameSingleton = SafeFindGame(g_Domain);
    if (!g_GameSingleton) {
        Log("[-] Game not found");
        SendMessage(g_TreeView, WM_SETREDRAW, TRUE, 0);
        return;
    }

    Log("[+] Game @ 0x%p", g_GameSingleton);

    // Pre-fetch ScriptService
    EnsureScriptService();
    
    // Explicitly scan for Players service (since lazy loading skips it)
    void* temp[64];
    int topLevelCount = SafeGetChildren(g_GameSingleton, temp, 64);
    for (int i = 0; i < topLevelCount; i++) {
        char cls[64] = {};
        SafeGetClassName(temp[i], cls, 64);
        if (strcmp(cls, "Players") == 0) {
            g_PlayersInstance = temp[i];
            Log("[*] Found Players Service manually @ 0x%p", g_PlayersInstance);
            ScanPlayers(); // Update player list immediately
            break;
        }
    }

    AddInstanceToTree(TVI_ROOT, g_GameSingleton);
    
    // Expand the root "Game" node by default
    HTREEITEM root = TreeView_GetRoot(g_TreeView);
    if (root) {
        TreeView_Expand(g_TreeView, root, TVE_EXPAND);
        // Force expand logic for root to populate first level
        ExpandTreeItem(root);
    }

    SendMessage(g_TreeView, WM_SETREDRAW, TRUE, 0);
    Log("[+] Refreshed (Lazy v2)");
}

void Rename() {
    if (!g_SelectedInstance || !Instance_set_Name) return;
    char n[128] = {};
    GetWindowTextA(g_NameEdit, n, 128);
    __try {
        Instance_set_Name(g_SelectedInstance, il2cpp_string_new(n));
        Log("[+] Renamed to '%s'", n);
        // Update tree item text
        if (g_Instances.find(TreeView_GetSelection(g_TreeView)) != g_Instances.end()) {
             // Re-read name and class to update label properly
             char cls[64];
             SafeGetClassName(g_SelectedInstance, cls, 64);
             char disp[256];
             sprintf_s(disp, "%s [%s]", n, cls);
             
             TVITEM tvi = {};
             tvi.mask = TVIF_TEXT;
             tvi.hItem = TreeView_GetSelection(g_TreeView);
             tvi.pszText = disp;
             TreeView_SetItem(g_TreeView, &tvi);
        }
    }
    __except (1) { Log("[-] Rename failed!"); }
}

void Delete() {
    if (!g_SelectedInstance || !Instance_Destroy) return;
    __try {
        Instance_Destroy(g_SelectedInstance, 0);
        Log("[+] Deleted");
        
        HTREEITEM sel = TreeView_GetSelection(g_TreeView);
        if (sel) {
            TreeView_DeleteItem(g_TreeView, sel);
            g_Instances.erase(sel);
        }
        g_SelectedInstance = nullptr;
    }
    __except (1) { Log("[-] Delete failed!"); }
}

void Clone() {
    if (!g_SelectedInstance || !Instance_Clone) return;
    __try {
        void* cloned = Instance_Clone(g_SelectedInstance);
        if (cloned) {
            Log("[+] Cloned @ 0x%p", cloned);
            // Add to tree under same parent
            HTREEITEM sel = TreeView_GetSelection(g_TreeView);
            if (sel) {
                HTREEITEM parent = TreeView_GetParent(g_TreeView, sel);
                if (parent) {
                     ExpandTreeItem(parent); // Ensure parent expanded/populated
                     AddInstanceToTree(parent, cloned);
                }
            }
        }
        else Log("[-] Clone returned NULL");
    }
    __except (1) { Log("[-] Clone failed!"); }
}



// ==================== Init ====================
bool InitIL2CPP() {
    g_GameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!g_GameAssembly) return false;

    il2cpp_string_new = (il2cpp_string_new_t)GetProcAddress(g_GameAssembly, "il2cpp_string_new");
    il2cpp_domain_get = (il2cpp_domain_get_t)GetProcAddress(g_GameAssembly, "il2cpp_domain_get");
    il2cpp_thread_attach = (il2cpp_thread_attach_t)GetProcAddress(g_GameAssembly, "il2cpp_thread_attach");
    il2cpp_thread_detach = (il2cpp_thread_detach_t)GetProcAddress(g_GameAssembly, "il2cpp_thread_detach");
    il2cpp_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)GetProcAddress(g_GameAssembly, "il2cpp_domain_get_assemblies");
    il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)GetProcAddress(g_GameAssembly, "il2cpp_assembly_get_image");
    il2cpp_class_from_name = (il2cpp_class_from_name_t)GetProcAddress(g_GameAssembly, "il2cpp_class_from_name");
    il2cpp_class_get_static_field_data = (il2cpp_class_get_static_field_data_t)GetProcAddress(g_GameAssembly, "il2cpp_class_get_static_field_data");

    if (!il2cpp_string_new || !il2cpp_domain_get || !il2cpp_thread_attach) return false;

    uintptr_t b = (uintptr_t)g_GameAssembly;
    Instance_GetChildren = (Instance_GetChildren_t)(b + INSTANCE_GETCHILDREN_OFFSET);
    Instance_get_Name = (Instance_get_Name_t)(b + INSTANCE_GET_NAME_OFFSET);
    Instance_set_Name = (Instance_set_Name_t)(b + INSTANCE_SET_NAME_OFFSET);
    Instance_get_ClassName = (Instance_get_ClassName_t)(b + INSTANCE_GET_CLASSNAME_OFFSET);
    Instance_Destroy = (Instance_Destroy_t)(b + INSTANCE_DESTROY_OFFSET);
    Instance_Clone = (Instance_Clone_t)(b + INSTANCE_CLONE_OFFSET);
    Instance_New = (Instance_New_t)(b + INSTANCE_NEW_OFFSET);
    BaseScript_set_Source = (BaseScript_set_Source_t)(b + BASESCRIPT_SET_SOURCE_OFFSET);
    BaseScript_Run = (BaseScript_Run_t)(b + BASESCRIPT_RUN_OFFSET);
    ScriptService_get_Instance = (ScriptService_get_Instance_t)(b + SCRIPTSERVICE_GET_INSTANCE_OFFSET);
    ScriptService_RunScript = (ScriptService_RunScript_t)(b + SCRIPTSERVICE_RUNSCRIPT_OFFSET);
    g_InvokeServerAddr = (void*)(b + NETEVENT_INVOKESERVER_OFFSET);
    Plr_CmdSetHealth = (Plr_CmdSetHealth_t)(b + PLR_CMDSETHEALTH_OFFSET);

    il2cpp_object_new = (il2cpp_object_new_t)GetProcAddress(g_GameAssembly, "il2cpp_object_new");
    NW_ctor = (NW_ctor_t)(b + NW_CTOR_OFFSET);
    NW_WriteByte = (NW_WriteByte_t)(b + NW_WRITEBYTE_OFFSET);
    NW_WriteFloat = (NW_WriteBlittableFloat_t)(b + NW_WRITE_FLOAT_OFFSET);
    NW_WriteUInt = (NW_WriteBlittableUInt_t)(b + NW_WRITE_UINT_OFFSET);
    NW_WriteUShort = (NW_WriteBlittableUShort_t)(b + NW_WRITE_USHORT_OFFSET);
    NW_WriteBool = (NW_WriteBool_t)(b + NW_WRITE_BOOL_OFFSET);
    NW_WriteVector3 = (NW_WriteVector3_t)(b + NW_WRITE_VEC3_OFFSET);
    NW_WriteString = (NW_WriteString_t)(b + NW_WRITE_STRING_OFFSET);
    SendCmdInternal = (SendCommandInternal_t)(b + SEND_CMD_INTERNAL_OFFSET);
    NB_get_netId = (NB_get_netId_t)(b + NB_GET_NETID_OFFSET);
    GetFunctionMethodName = (GetFunctionMethodName_t)(b + GET_FUNC_NAME_OFFSET);
    CommandRequiresAuthority = (CommandRequiresAuthority_t)(b + CMD_REQUIRES_AUTH_OFFSET);


    return true;
}

bool AttachIL2CPP() {
    g_Domain = il2cpp_domain_get();
    g_Thread = il2cpp_thread_attach(g_Domain);
    return g_Thread != nullptr;
}

// ==================== WndProc ====================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_NOTIFY: {
        NMHDR* nm = (NMHDR*)lp;

        if (nm->idFrom == ID_TABCONTROL && nm->code == TCN_SELCHANGE) {
            int tab = TabCtrl_GetCurSel(g_TabControl);

            // Explorer
            ShowWindow(g_TreeView, tab == 0 ? SW_SHOW : SW_HIDE);
            ShowWindow(g_PropertyList, tab == 0 ? SW_SHOW : SW_HIDE);
            ShowWindow(g_NameEdit, tab == 0 ? SW_SHOW : SW_HIDE);

            // LUA
            BOOL lua = (tab == 1);
            ShowWindow(g_ScriptEdit, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ExecuteBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ClearBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_LoadFileBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ScriptStatus, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ScriptTabControl, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_AddTabBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_CloseTabBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ScriptListBox, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ScriptListLoadBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ScriptListRefreshBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_ScriptListOpenBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_PrevTabBtn, lua ? SW_SHOW : SW_HIDE);
            ShowWindow(g_NextTabBtn, lua ? SW_SHOW : SW_HIDE);

            // CMD
            ShowWindow(g_CmdOutput, tab == 2 ? SW_SHOW : SW_HIDE);
            ShowWindow(g_CmdInput, tab == 2 ? SW_SHOW : SW_HIDE);
            ShowWindow(g_CmdSendBtn, tab == 2 ? SW_SHOW : SW_HIDE);

            if (lua) RefreshScriptList();
        }

        if (nm->idFrom == ID_SCRIPTTAB && nm->code == TCN_SELCHANGE) {
            SwitchScriptTab(TabCtrl_GetCurSel(g_ScriptTabControl));
        }

        if (nm->idFrom == ID_TREEVIEW) {
             if (nm->code == TVN_SELCHANGED) {
                NMTREEVIEW* tv = (NMTREEVIEW*)lp;
                auto it = g_Instances.find(tv->itemNew.hItem);
                if (it != g_Instances.end()) {
                    g_SelectedInstance = it->second.ptr;
                    ShowProperties(g_SelectedInstance);
                }
             }
             if (nm->code == TVN_ITEMEXPANDING) {
                 NMTREEVIEW* tv = (NMTREEVIEW*)lp;
                 if (tv->action == TVE_EXPAND) {
                     ExpandTreeItem(tv->itemNew.hItem);
                 }
             }
             if (nm->code == TVN_DELETEITEM) {
                 NMTREEVIEW* tv = (NMTREEVIEW*)lp;
                 g_Instances.erase(tv->itemOld.hItem);
             }
        }
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case ID_REFRESH: Refresh(); break;
        case ID_DELETE: Delete(); break;
        case ID_CLONE: Clone(); break;
        case ID_SETNAME: Rename(); break;
        case ID_EXECUTE: ExecuteScript(); break;
        case ID_CLEAR: ClearScript(); break;
        case ID_LOADFILE: LoadFileLua(); break;
        case ID_CMD_SEND: OnCmdSend(); break;
        case ID_COPYPATH: CopyInstancePath(); break;

        case ID_PREVTAB: {
            if (g_CurrentScriptTab > 0) {
                SaveCurrentTabContent();
                g_CurrentScriptTab--;
                TabCtrl_SetCurSel(g_ScriptTabControl, g_CurrentScriptTab);
                LoadTabContent(g_CurrentScriptTab);
            }
            break;
        }
        case ID_NEXTTAB: {
            if (g_CurrentScriptTab < g_ScriptTabCount - 1) {
                SaveCurrentTabContent();
                g_CurrentScriptTab++;
                TabCtrl_SetCurSel(g_ScriptTabControl, g_CurrentScriptTab);
                LoadTabContent(g_CurrentScriptTab);
            }
            break;
        }

        case ID_ADDTAB: {
            SaveCurrentTabContent();
            char name[32];
            snprintf(name, sizeof(name), "Script %d", g_ScriptTabCount + 1);
            int idx = AddScriptTab(name, "");
            if (idx >= 0) {
                g_CurrentScriptTab = idx;
                TabCtrl_SetCurSel(g_ScriptTabControl, idx);
                LoadTabContent(idx);
            }
            break;
        }
        case ID_CLOSETAB:
            if (g_ScriptTabCount > 1) {
                RemoveScriptTab(g_CurrentScriptTab);
            }
            break;

            // Script list
        case ID_SCRIPTLIST:
            if (HIWORD(wp) == LBN_DBLCLK) {
                LoadSelectedScript();
            }
            break;
        case ID_SCRIPTLIST_LOAD:
            LoadSelectedScript();
            break;
        case ID_SCRIPTLIST_REFRESH:
            RefreshScriptList();
            break;
        case ID_SCRIPTLIST_OPENFOLDER:
            OpenScriptsFolder();
            break;

        case ID_PROPERTYLIST:
            if (HIWORD(wp) == LBN_DBLCLK) {
                char text[256] = {};
                int idx = (int)SendMessage(g_PropertyList, LB_GETCURSEL, 0, 0);
                SendMessageA(g_PropertyList, LB_GETTEXT, idx, (LPARAM)text);
                if (strstr(text, "dump Source"))
                    DumpSelectedScriptSource();
            }
            break;
        }
        break;

    case WM_SIZE: {
        int w = LOWORD(lp), h = HIWORD(lp);
        int logH = 100;
        int logY = h - logH - 10;
        int contentH = logY - 70;
        int btnY = logY - 35;
        int listW = 185;

        MoveWindow(g_TabControl, 0, 0, w, logY, TRUE);

        // Explorer
        int halfW = (w - 30) / 2;
        MoveWindow(g_TreeView, 10, 70, halfW, contentH - 10, TRUE);
        MoveWindow(g_PropertyList, halfW + 20, 70, halfW, contentH, TRUE);

        // LUA: Script tabs
        MoveWindow(g_ScriptTabControl, listW + 10, 35, w - listW - 130, 24, TRUE);
        MoveWindow(g_PrevTabBtn, w - 115, 35, 26, 24, TRUE);
        MoveWindow(g_NextTabBtn, w - 89, 35, 26, 24, TRUE);
        MoveWindow(g_AddTabBtn, w - 60, 35, 26, 24, TRUE);
        MoveWindow(g_CloseTabBtn, w - 34, 35, 26, 24, TRUE);

        // LUA: Script list
        MoveWindow(g_ScriptListBox, 10, 65, listW - 5, contentH - 30, TRUE);
        MoveWindow(g_ScriptListLoadBtn, 10, btnY - 0, 55, 24, TRUE);
        MoveWindow(g_ScriptListRefreshBtn, 70, btnY - 0, 55, 24, TRUE);
        MoveWindow(g_ScriptListOpenBtn, 130, btnY - 0, 55, 24, TRUE);


        // LUA: Editor
        MoveWindow(g_ScriptEdit, listW + 10, 65, w - listW - 20, contentH - 30, TRUE);

        // LUA: Bottom
        MoveWindow(g_ExecuteBtn, listW + 10, btnY, 100, 30, TRUE);
        MoveWindow(g_ClearBtn, listW + 120, btnY, 80, 30, TRUE);
        MoveWindow(g_LoadFileBtn, listW + 210, btnY, 90, 30, TRUE);
        MoveWindow(g_ScriptStatus, listW + 310, btnY + 5, 300, 20, TRUE);

        // CMD
        MoveWindow(g_CmdOutput, 10, 70, w - 20, contentH - 40, TRUE);
        MoveWindow(g_CmdInput, 10, btnY, w - 110, 26, TRUE);
        MoveWindow(g_CmdSendBtn, w - 90, btnY, 80, 26, TRUE);

        // Log
        MoveWindow(g_LogBox, 10, logY, w - 20, logH, TRUE);
        break;
    }

    case WM_CLOSE:
        SaveAllTabs();
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        g_Window = nullptr;
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// ==================== GUI ====================
void CreateGUI() {
    InitCommonControls();
    InitDirectories();

    WNDCLASSEXA wc = { sizeof(wc) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = g_Module;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = "ELYTRA";
    RegisterClassExA(&wc);

    g_Window = CreateWindowExA(WS_EX_TOPMOST, "ELYTRA", "Elytra v1.4.1",
        WS_OVERLAPPEDWINDOW, 50, 50, 1050, 720, nullptr, nullptr, g_Module, nullptr);

    HFONT font = CreateFontA(14, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, "Consolas");

    // Main tabs
    g_TabControl = CreateWindowExA(0, WC_TABCONTROLA, "", WS_CHILD | WS_VISIBLE,
        0, 0, 1030, 500, g_Window, (HMENU)ID_TABCONTROL, g_Module, nullptr);
    TCITEMA tie = {}; tie.mask = TCIF_TEXT;
    tie.pszText = (LPSTR)"EXPLORER"; TabCtrl_InsertItem(g_TabControl, 0, &tie);
    tie.pszText = (LPSTR)"LUA";      TabCtrl_InsertItem(g_TabControl, 1, &tie);
    tie.pszText = (LPSTR)"CMD";      TabCtrl_InsertItem(g_TabControl, 2, &tie);

    // Explorer toolbar
    int x = 10, y = 35;
    CreateWindowExA(0, "BUTTON", "Refresh", WS_CHILD | WS_VISIBLE, x, y, 70, 26, g_Window, (HMENU)ID_REFRESH, g_Module, nullptr); x += 80;
    CreateWindowExA(0, "BUTTON", "Delete", WS_CHILD | WS_VISIBLE, x, y, 60, 26, g_Window, (HMENU)ID_DELETE, g_Module, nullptr); x += 70;
    CreateWindowExA(0, "BUTTON", "Clone", WS_CHILD | WS_VISIBLE, x, y, 60, 26, g_Window, (HMENU)ID_CLONE, g_Module, nullptr); x += 80;
    CreateWindowExA(0, "BUTTON", "CPath", WS_CHILD | WS_VISIBLE, x, y, 70, 26, g_Window, (HMENU)ID_COPYPATH, g_Module, nullptr); x += 90;
    CreateWindowExA(0, "STATIC", "Name:", WS_CHILD | WS_VISIBLE, x, y + 4, 40, 20, g_Window, nullptr, g_Module, nullptr); x += 45;
    g_NameEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE, x, y, 150, 24, g_Window, (HMENU)ID_NAMEEDIT, g_Module, nullptr); x += 160;
    CreateWindowExA(0, "BUTTON", "Set", WS_CHILD | WS_VISIBLE, x, y, 40, 26, g_Window, (HMENU)ID_SETNAME, g_Module, nullptr);

    // Explorer tree + properties
    g_TreeView = CreateWindowExA(WS_EX_CLIENTEDGE, WC_TREEVIEWA, "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT,
        10, 70, 450, 400, g_Window, (HMENU)ID_TREEVIEW, g_Module, nullptr);
    SendMessage(g_TreeView, WM_SETFONT, (WPARAM)font, TRUE);

    g_PropertyList = CreateWindowExA(WS_EX_CLIENTEDGE, "LISTBOX", "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
        470, 70, 450, 400, g_Window, (HMENU)ID_PROPERTYLIST, g_Module, nullptr);
    SendMessage(g_PropertyList, WM_SETFONT, (WPARAM)font, TRUE);

    // === LUA TAB ===
    // Script tabs bar
    g_ScriptTabControl = CreateWindowExA(0, WC_TABCONTROLA, "",
        WS_CHILD, 200, 35, 700, 24,
        g_Window, (HMENU)ID_SCRIPTTAB, g_Module, nullptr);
    SendMessage(g_ScriptTabControl, WM_SETFONT, (WPARAM)font, TRUE);

    g_AddTabBtn = CreateWindowExA(0, "BUTTON", "+",
        WS_CHILD, 905, 35, 26, 24,
        g_Window, (HMENU)ID_ADDTAB, g_Module, nullptr);

    g_CloseTabBtn = CreateWindowExA(0, "BUTTON", "x",
        WS_CHILD, 935, 35, 26, 24,
        g_Window, (HMENU)ID_CLOSETAB, g_Module, nullptr);

    // Script list (left side)
    g_ScriptListBox = CreateWindowExA(WS_EX_CLIENTEDGE, "LISTBOX", "",
        WS_CHILD | WS_VSCROLL | LBS_NOTIFY,
        10, 65, 180, 340,
        g_Window, (HMENU)ID_SCRIPTLIST, g_Module, nullptr);
    SendMessage(g_ScriptListBox, WM_SETFONT, (WPARAM)font, TRUE);

    g_ScriptListLoadBtn = CreateWindowExA(0, "BUTTON", "INS",
        WS_CHILD, 10, 410, 55, 24,
        g_Window, (HMENU)ID_SCRIPTLIST_LOAD, g_Module, nullptr);

    g_ScriptListRefreshBtn = CreateWindowExA(0, "BUTTON", "RES",
        WS_CHILD, 70, 410, 55, 24,
        g_Window, (HMENU)ID_SCRIPTLIST_REFRESH, g_Module, nullptr);

    g_ScriptListOpenBtn = CreateWindowExA(0, "BUTTON", "LOC",
        WS_CHILD, 130, 410, 55, 24,
        g_Window, (HMENU)ID_SCRIPTLIST_OPENFOLDER, g_Module, nullptr);

    g_ScriptTabControl = CreateWindowExA(0, WC_TABCONTROLA, "",
        WS_CHILD, 200, 35, 650, 24,
        g_Window, (HMENU)ID_SCRIPTTAB, g_Module, nullptr);
    SendMessage(g_ScriptTabControl, WM_SETFONT, (WPARAM)font, TRUE);

    g_PrevTabBtn = CreateWindowExA(0, "BUTTON", "<",
        WS_CHILD, 855, 35, 24, 24,
        g_Window, (HMENU)ID_PREVTAB, g_Module, nullptr);

    g_NextTabBtn = CreateWindowExA(0, "BUTTON", ">",
        WS_CHILD, 881, 35, 24, 24,
        g_Window, (HMENU)ID_NEXTTAB, g_Module, nullptr);

    g_AddTabBtn = CreateWindowExA(0, "BUTTON", "+",
        WS_CHILD, 910, 35, 24, 24,
        g_Window, (HMENU)ID_ADDTAB, g_Module, nullptr);

    g_CloseTabBtn = CreateWindowExA(0, "BUTTON", "x",
        WS_CHILD, 936, 35, 24, 24,
        g_Window, (HMENU)ID_CLOSETAB, g_Module, nullptr);

    // Script editor (right of script list)
    g_ScriptEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_CHILD | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN,
        200, 65, 760, 345, g_Window, (HMENU)ID_SCRIPTEDIT, g_Module, nullptr);
    SendMessage(g_ScriptEdit, WM_SETFONT, (WPARAM)font, TRUE);
    SendMessage(g_ScriptEdit, EM_SETLIMITTEXT, 512000, 0);

    // Buttons
    g_ExecuteBtn = CreateWindowExA(0, "BUTTON", "Execute", WS_CHILD, 200, 415, 100, 30, g_Window, (HMENU)ID_EXECUTE, g_Module, nullptr);
    g_ClearBtn = CreateWindowExA(0, "BUTTON", "Clear", WS_CHILD, 310, 415, 80, 30, g_Window, (HMENU)ID_CLEAR, g_Module, nullptr);
    g_LoadFileBtn = CreateWindowExA(0, "BUTTON", "Load File", WS_CHILD, 400, 415, 90, 30, g_Window, (HMENU)ID_LOADFILE, g_Module, nullptr);
    g_ScriptStatus = CreateWindowExA(0, "STATIC", "Ready", WS_CHILD, 500, 420, 300, 20, g_Window, (HMENU)ID_SCRIPTSTATUS, g_Module, nullptr);

    // CMD tab
    g_CmdOutput = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
        10, 70, 940, 100, g_Window, (HMENU)ID_CMD_OUTPUT, g_Module, nullptr);
    SendMessage(g_CmdOutput, WM_SETFONT, (WPARAM)font, TRUE);

    g_CmdInput = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_CHILD | ES_AUTOHSCROLL,
        10, 435, 850, 26, g_Window, (HMENU)ID_CMD_INPUT, g_Module, nullptr);
    SendMessage(g_CmdInput, WM_SETFONT, (WPARAM)font, TRUE);

    g_CmdSendBtn = CreateWindowExA(0, "BUTTON", "Send", WS_CHILD,
        865, 435, 70, 26, g_Window, (HMENU)ID_CMD_SEND, g_Module, nullptr);

    // Log box
    g_LogBox = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
        10, 500, 940, 100, g_Window, (HMENU)ID_LOGBOX, g_Module, nullptr);
    SendMessage(g_LogBox, WM_SETFONT, (WPARAM)font, TRUE);


    // Load saved tabs or create default
    LoadAllTabs();

    // Load script list
    RefreshScriptList();

    ShowWindow(g_Window, SW_SHOW);
}

void Run() {
    CreateGUI();
    Log("[+] Elytra v1.4.2!");
    Log("[*] Click Refresh to load game tree");
    Log("[*] LUA tab to execute scripts");
    Log("[*] Discord: https://discord.gg/kCYjY2gxu4");
    Log("[*] Made by 74235 & intplatinum");

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_TAB && GetFocus() == g_ScriptEdit) {
            SendMessageA(g_ScriptEdit, EM_REPLACESEL, TRUE, (LPARAM)"    ");
            continue;
        }
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN && GetFocus() == g_CmdInput) {
            OnCmdSend();
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (!g_Window) break;
    }
}

DWORD WINAPI MainThread(LPVOID p) {
    g_Module = (HMODULE)p;
    Sleep(3000);

    if (!InitIL2CPP() || !AttachIL2CPP()) {
        MessageBoxA(nullptr, "Init failed!", "Elytra", MB_OK | MB_ICONERROR);
        FreeLibraryAndExitThread(g_Module, 1);
        return 1;
    }

    Run();

    if (g_Thread && il2cpp_thread_detach) il2cpp_thread_detach(g_Thread);
    if (g_HooksInstalled) DisableEventLogger();
    if (g_CmdSnifferEnabled) DisableCmdSniffer();
    if (g_NetMonWindow) DestroyWindow(g_NetMonWindow);
    DeleteCriticalSection(&g_NetLogCS);
    RemoveAllPCHooks();
    RemoveAntiKickHooks();
    RemoveTelepathyHooks();
    CleanupScripts();
    SaveAllTabs();
    for (int i = 0; i < g_ScriptTabCount; i++) {
        if (g_ScriptTabs[i].buffer) free(g_ScriptTabs[i].buffer);
    }
    FreeLibraryAndExitThread(g_Module, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE m, DWORD r, LPVOID) {
    if (r == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(m);
        CreateThread(nullptr, 0, MainThread, m, 0, nullptr);
    }
    return TRUE;
}
