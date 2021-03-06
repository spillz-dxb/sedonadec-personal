//
// Generated by sedonac 1.2.28
// 25-Oct-2017 21:08
//

#include "sedona.h"

////////////////////////////////////////////////////////////////
// sys (kitId=0)
////////////////////////////////////////////////////////////////

// sys::Str Sys.platformType()
Cell sys_Sys_platformType(SedonaVM* vm, Cell* params);

// void Sys.copy(byte[], int, byte[], int, int)
Cell sys_Sys_copy(SedonaVM* vm, Cell* params);

// byte[] Sys.malloc(int)
Cell sys_Sys_malloc(SedonaVM* vm, Cell* params);

// void Sys.free(sys::Obj)
Cell sys_Sys_free(SedonaVM* vm, Cell* params);

// sys::Str Sys.intStr(int)
Cell sys_Sys_intStr(SedonaVM* vm, Cell* params);

// sys::Str Sys.hexStr(int)
Cell sys_Sys_hexStr(SedonaVM* vm, Cell* params);

// sys::Str Sys.longStr(long)
Cell sys_Sys_longStr(SedonaVM* vm, Cell* params);

// sys::Str Sys.longHexStr(long)
Cell sys_Sys_longHexStr(SedonaVM* vm, Cell* params);

// sys::Str Sys.floatStr(float)
Cell sys_Sys_floatStr(SedonaVM* vm, Cell* params);

// sys::Str Sys.doubleStr(double)
Cell sys_Sys_doubleStr(SedonaVM* vm, Cell* params);

// int Sys.floatToBits(float)
Cell sys_Sys_floatToBits(SedonaVM* vm, Cell* params);

// long Sys.doubleToBits(double)
Cell sys_Sys_doubleToBits(SedonaVM* vm, Cell* params);

// float Sys.bitsToFloat(int)
Cell sys_Sys_bitsToFloat(SedonaVM* vm, Cell* params);

// double Sys.bitsToDouble(long)
Cell sys_Sys_bitsToDouble(SedonaVM* vm, Cell* params);

// long Sys.ticks()
Cell sys_Sys_ticks(SedonaVM* vm, Cell* params);

// void Sys.sleep(long)
Cell sys_Sys_sleep(SedonaVM* vm, Cell* params);

// int Sys.compareBytes(byte[], int, byte[], int, int)
Cell sys_Sys_compareBytes(SedonaVM* vm, Cell* params);

// void Sys.setBytes(int, byte[], int, int)
Cell sys_Sys_setBytes(SedonaVM* vm, Cell* params);

// void Sys.andBytes(int, byte[], int, int)
Cell sys_Sys_andBytes(SedonaVM* vm, Cell* params);

// void Sys.orBytes(int, byte[], int, int)
Cell sys_Sys_orBytes(SedonaVM* vm, Cell* params);

// byte[] Sys.scodeAddr()
Cell sys_Sys_scodeAddr(SedonaVM* vm, Cell* params);

// int Sys.rand()
Cell sys_Sys_rand(SedonaVM* vm, Cell* params);

// void Component.invokeVoid(sys::Slot)
Cell sys_Component_invokeVoid(SedonaVM* vm, Cell* params);

// void Component.invokeBool(sys::Slot, bool)
Cell sys_Component_invokeBool(SedonaVM* vm, Cell* params);

// void Component.invokeInt(sys::Slot, int)
Cell sys_Component_invokeInt(SedonaVM* vm, Cell* params);

// void Component.invokeLong(sys::Slot, long)
Cell sys_Component_invokeLong(SedonaVM* vm, Cell* params);

// void Component.invokeFloat(sys::Slot, float)
Cell sys_Component_invokeFloat(SedonaVM* vm, Cell* params);

// void Component.invokeDouble(sys::Slot, double)
Cell sys_Component_invokeDouble(SedonaVM* vm, Cell* params);

// void Component.invokeBuf(sys::Slot, sys::Buf)
Cell sys_Component_invokeBuf(SedonaVM* vm, Cell* params);

// bool Component.getBool(sys::Slot)
Cell sys_Component_getBool(SedonaVM* vm, Cell* params);

// int Component.getInt(sys::Slot)
Cell sys_Component_getInt(SedonaVM* vm, Cell* params);

// long Component.getLong(sys::Slot)
Cell sys_Component_getLong(SedonaVM* vm, Cell* params);

// float Component.getFloat(sys::Slot)
Cell sys_Component_getFloat(SedonaVM* vm, Cell* params);

// double Component.getDouble(sys::Slot)
Cell sys_Component_getDouble(SedonaVM* vm, Cell* params);

// sys::Buf Component.getBuf(sys::Slot)
Cell sys_Component_getBuf(SedonaVM* vm, Cell* params);

// bool Component.doSetBool(sys::Slot, bool)
Cell sys_Component_doSetBool(SedonaVM* vm, Cell* params);

// bool Component.doSetInt(sys::Slot, int)
Cell sys_Component_doSetInt(SedonaVM* vm, Cell* params);

// bool Component.doSetLong(sys::Slot, long)
Cell sys_Component_doSetLong(SedonaVM* vm, Cell* params);

// bool Component.doSetFloat(sys::Slot, float)
Cell sys_Component_doSetFloat(SedonaVM* vm, Cell* params);

// bool Component.doSetDouble(sys::Slot, double)
Cell sys_Component_doSetDouble(SedonaVM* vm, Cell* params);

// sys::Obj Type.malloc()
Cell sys_Type_malloc(SedonaVM* vm, Cell* params);

// bool StdOutStream.doWrite(int)
Cell sys_StdOutStream_doWrite(SedonaVM* vm, Cell* params);

// bool StdOutStream.doWriteBytes(byte[], int, int)
Cell sys_StdOutStream_doWriteBytes(SedonaVM* vm, Cell* params);

// void StdOutStream.doFlush()
Cell sys_StdOutStream_doFlush(SedonaVM* vm, Cell* params);

// int FileStore.doSize(sys::Str)
Cell sys_FileStore_doSize(SedonaVM* vm, Cell* params);

// sys::Obj FileStore.doOpen(sys::Str, sys::Str)
Cell sys_FileStore_doOpen(SedonaVM* vm, Cell* params);

// int FileStore.doRead(sys::Obj)
Cell sys_FileStore_doRead(SedonaVM* vm, Cell* params);

// int FileStore.doReadBytes(sys::Obj, byte[], int, int)
Cell sys_FileStore_doReadBytes(SedonaVM* vm, Cell* params);

// bool FileStore.doWrite(sys::Obj, int)
Cell sys_FileStore_doWrite(SedonaVM* vm, Cell* params);

// bool FileStore.doWriteBytes(sys::Obj, byte[], int, int)
Cell sys_FileStore_doWriteBytes(SedonaVM* vm, Cell* params);

// int FileStore.doTell(sys::Obj)
Cell sys_FileStore_doTell(SedonaVM* vm, Cell* params);

// bool FileStore.doSeek(sys::Obj, int)
Cell sys_FileStore_doSeek(SedonaVM* vm, Cell* params);

// void FileStore.doFlush(sys::Obj)
Cell sys_FileStore_doFlush(SedonaVM* vm, Cell* params);

// bool FileStore.doClose(sys::Obj)
Cell sys_FileStore_doClose(SedonaVM* vm, Cell* params);

// bool FileStore.rename(sys::Str, sys::Str)
Cell sys_FileStore_rename(SedonaVM* vm, Cell* params);

// int Test.doMain()
Cell sys_Test_doMain(SedonaVM* vm, Cell* params);

// sys::Str Str.fromBytes(byte[], int)
Cell sys_Str_fromBytes(SedonaVM* vm, Cell* params);

// sys::Str PlatformService.doPlatformId()
Cell sys_PlatformService_doPlatformId(SedonaVM* vm, Cell* params);

// sys::Str PlatformService.getPlatVersion()
Cell sys_PlatformService_getPlatVersion(SedonaVM* vm, Cell* params);

// long PlatformService.getNativeMemAvailable()
Cell sys_PlatformService_getNativeMemAvailable(SedonaVM* vm, Cell* params);

// native table for kit 0
NativeMethod kitNatives0[] = 
{
  sys_Sys_platformType,           // 0::0
  sys_Sys_copy,                   // 0::1
  sys_Sys_malloc,                 // 0::2
  sys_Sys_free,                   // 0::3
  sys_Sys_intStr,                 // 0::4
  sys_Sys_hexStr,                 // 0::5
  sys_Sys_longStr,                // 0::6
  sys_Sys_longHexStr,             // 0::7
  sys_Sys_floatStr,               // 0::8
  sys_Sys_doubleStr,              // 0::9
  sys_Sys_floatToBits,            // 0::10
  sys_Sys_doubleToBits,           // 0::11
  sys_Sys_bitsToFloat,            // 0::12
  sys_Sys_bitsToDouble,           // 0::13
  sys_Sys_ticks,                  // 0::14
  sys_Sys_sleep,                  // 0::15
  sys_Sys_compareBytes,           // 0::16
  sys_Sys_setBytes,               // 0::17
  sys_Sys_andBytes,               // 0::18
  sys_Sys_orBytes,                // 0::19
  sys_Sys_scodeAddr,              // 0::20
  sys_Sys_rand,                   // 0::21
  sys_Component_invokeVoid,       // 0::22
  sys_Component_invokeBool,       // 0::23
  sys_Component_invokeInt,        // 0::24
  sys_Component_invokeLong,       // 0::25
  sys_Component_invokeFloat,      // 0::26
  sys_Component_invokeDouble,     // 0::27
  sys_Component_invokeBuf,        // 0::28
  sys_Component_getBool,          // 0::29
  sys_Component_getInt,           // 0::30
  sys_Component_getLong,          // 0::31
  sys_Component_getFloat,         // 0::32
  sys_Component_getDouble,        // 0::33
  sys_Component_getBuf,           // 0::34
  sys_Component_doSetBool,        // 0::35
  sys_Component_doSetInt,         // 0::36
  sys_Component_doSetLong,        // 0::37
  sys_Component_doSetFloat,       // 0::38
  sys_Component_doSetDouble,      // 0::39
  sys_Type_malloc,                // 0::40
  sys_StdOutStream_doWrite,       // 0::41
  sys_StdOutStream_doWriteBytes,  // 0::42
  sys_StdOutStream_doFlush,       // 0::43
  sys_FileStore_doSize,           // 0::44
  sys_FileStore_doOpen,           // 0::45
  sys_FileStore_doRead,           // 0::46
  sys_FileStore_doReadBytes,      // 0::47
  sys_FileStore_doWrite,          // 0::48
  sys_FileStore_doWriteBytes,     // 0::49
  sys_FileStore_doTell,           // 0::50
  sys_FileStore_doSeek,           // 0::51
  sys_FileStore_doFlush,          // 0::52
  sys_FileStore_doClose,          // 0::53
  sys_FileStore_rename,           // 0::54
  sys_Test_doMain,                // 0::55
  sys_Str_fromBytes,              // 0::56
  sys_PlatformService_doPlatformId,  // 0::57
  sys_PlatformService_getPlatVersion,  // 0::58
  sys_PlatformService_getNativeMemAvailable,  // 0::59
};

////////////////////////////////////////////////////////////////
// inet (kitId=2)
////////////////////////////////////////////////////////////////

// bool TcpSocket.connect(inet::IpAddr, int)
Cell inet_TcpSocket_connect(SedonaVM* vm, Cell* params);

// bool TcpSocket.finishConnect()
Cell inet_TcpSocket_finishConnect(SedonaVM* vm, Cell* params);

// int TcpSocket.write(byte[], int, int)
Cell inet_TcpSocket_write(SedonaVM* vm, Cell* params);

// int TcpSocket.read(byte[], int, int)
Cell inet_TcpSocket_read(SedonaVM* vm, Cell* params);

// void TcpSocket.close()
Cell inet_TcpSocket_close(SedonaVM* vm, Cell* params);

// bool TcpServerSocket.bind(int)
Cell inet_TcpServerSocket_bind(SedonaVM* vm, Cell* params);

// bool TcpServerSocket.accept(inet::TcpSocket)
Cell inet_TcpServerSocket_accept(SedonaVM* vm, Cell* params);

// void TcpServerSocket.close()
Cell inet_TcpServerSocket_close(SedonaVM* vm, Cell* params);

// bool UdpSocket.open()
Cell inet_UdpSocket_open(SedonaVM* vm, Cell* params);

// bool UdpSocket.bind(int)
Cell inet_UdpSocket_bind(SedonaVM* vm, Cell* params);

// bool UdpSocket.send(inet::UdpDatagram)
Cell inet_UdpSocket_send(SedonaVM* vm, Cell* params);

// bool UdpSocket.receive(inet::UdpDatagram)
Cell inet_UdpSocket_receive(SedonaVM* vm, Cell* params);

// void UdpSocket.close()
Cell inet_UdpSocket_close(SedonaVM* vm, Cell* params);

// int UdpSocket.maxPacketSize()
Cell inet_UdpSocket_maxPacketSize(SedonaVM* vm, Cell* params);

// int UdpSocket.idealPacketSize()
Cell inet_UdpSocket_idealPacketSize(SedonaVM* vm, Cell* params);

// void Crypto.sha1(byte[], int, int, byte[], int)
Cell inet_Crypto_sha1(SedonaVM* vm, Cell* params);

// bool UdpSocket.join()
Cell inet_UdpSocket_join(SedonaVM* vm, Cell* params);

// native table for kit 2
NativeMethod kitNatives2[] = 
{
  inet_TcpSocket_connect,         // 2::0
  inet_TcpSocket_finishConnect,   // 2::1
  inet_TcpSocket_write,           // 2::2
  inet_TcpSocket_read,            // 2::3
  inet_TcpSocket_close,           // 2::4
  inet_TcpServerSocket_bind,      // 2::5
  inet_TcpServerSocket_accept,    // 2::6
  inet_TcpServerSocket_close,     // 2::7
  inet_UdpSocket_open,            // 2::8
  inet_UdpSocket_bind,            // 2::9
  inet_UdpSocket_send,            // 2::10
  inet_UdpSocket_receive,         // 2::11
  inet_UdpSocket_close,           // 2::12
  inet_UdpSocket_maxPacketSize,   // 2::13
  inet_UdpSocket_idealPacketSize,  // 2::14
  inet_Crypto_sha1,               // 2::15
  inet_UdpSocket_join,            // 2::16
};

////////////////////////////////////////////////////////////////
// rpiDigitalIo (kitId=4)
////////////////////////////////////////////////////////////////

// int Dio.doInit(int, bool)
Cell rpiDigitalIo_Dio_doInit(SedonaVM* vm, Cell* params);

// int Dio.doRead(int)
Cell rpiDigitalIo_Dio_doRead(SedonaVM* vm, Cell* params);

// int Dio.doWrite(int, bool)
Cell rpiDigitalIo_Dio_doWrite(SedonaVM* vm, Cell* params);

// native table for kit 4
NativeMethod kitNatives4[] = 
{
  rpiDigitalIo_Dio_doInit,        // 4::0
  rpiDigitalIo_Dio_doRead,        // 4::1
  rpiDigitalIo_Dio_doWrite,       // 4::2
};

////////////////////////////////////////////////////////////////
// datetimeStd (kitId=9)
////////////////////////////////////////////////////////////////

// long DateTimeServiceStd.doNow()
Cell datetimeStd_DateTimeServiceStd_doNow(SedonaVM* vm, Cell* params);

// void DateTimeServiceStd.doSetClock(long)
Cell datetimeStd_DateTimeServiceStd_doSetClock(SedonaVM* vm, Cell* params);

// int DateTimeServiceStd.doGetUtcOffset()
Cell datetimeStd_DateTimeServiceStd_doGetUtcOffset(SedonaVM* vm, Cell* params);

// native table for kit 9
NativeMethod kitNatives9[] = 
{
  datetimeStd_DateTimeServiceStd_doNow,  // 9::0
  datetimeStd_DateTimeServiceStd_doSetClock,  // 9::1
  datetimeStd_DateTimeServiceStd_doGetUtcOffset,  // 9::2
};

////////////////////////////////////////////////////////////////
// BACnet (kitId=85)
////////////////////////////////////////////////////////////////

// int BACnetDev.doBacnetInit(bool)
Cell BACnet_BACnetDev_doBacnetInit(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetInitStatus()
Cell BACnet_BACnetDev_doBacnetInitStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBOValueStatus(int)
Cell BACnet_BACnetDev_doBacnetBOValueStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBOPriorityStatus(int, bool, int)
Cell BACnet_BACnetDev_doBacnetBOPriorityStatus(SedonaVM* vm, Cell* params);

// bool BACnetDev.doBacnetBOOverrideStatus()
Cell BACnet_BACnetDev_doBacnetBOOverrideStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBOValueUpdate(bool, bool, int)
Cell BACnet_BACnetDev_doBacnetBOValueUpdate(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBOOverrideInst()
Cell BACnet_BACnetDev_doBacnetBOOverrideInst(SedonaVM* vm, Cell* params);

// float BACnetDev.doBacnetAOValueStatus(int)
Cell BACnet_BACnetDev_doBacnetAOValueStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAOPriorityStatus(int, bool, int)
Cell BACnet_BACnetDev_doBacnetAOPriorityStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAOOverrideStatus()
Cell BACnet_BACnetDev_doBacnetAOOverrideStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAOValueUpdate(float, bool, int)
Cell BACnet_BACnetDev_doBacnetAOValueUpdate(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAOOverrideInst()
Cell BACnet_BACnetDev_doBacnetAOOverrideInst(SedonaVM* vm, Cell* params);

// float BACnetDev.doBacnetAVValueStatus(int)
Cell BACnet_BACnetDev_doBacnetAVValueStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAVPriorityStatus(int, bool, int)
Cell BACnet_BACnetDev_doBacnetAVPriorityStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAVOverrideStatus()
Cell BACnet_BACnetDev_doBacnetAVOverrideStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAVValueUpdate(float, bool, int)
Cell BACnet_BACnetDev_doBacnetAVValueUpdate(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAVOverrideInst()
Cell BACnet_BACnetDev_doBacnetAVOverrideInst(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetSendPort(int)
Cell BACnet_BACnetDev_doBacnetSendPort(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetSendDeviceID(int)
Cell BACnet_BACnetDev_doBacnetSendDeviceID(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBOObjectIdUpdate(int, bool, int)
Cell BACnet_BACnetDev_doBacnetBOObjectIdUpdate(SedonaVM* vm, Cell* params);

// bool BACnetDev.doBacnetBOObjectIdBkp(int)
Cell BACnet_BACnetDev_doBacnetBOObjectIdBkp(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAOObjectIdUpdate(int, float, int)
Cell BACnet_BACnetDev_doBacnetAOObjectIdUpdate(SedonaVM* vm, Cell* params);

// float BACnetDev.doBacnetAOObjectIdBkp(int)
Cell BACnet_BACnetDev_doBacnetAOObjectIdBkp(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetAVObjectIdUpdate(int, float, int)
Cell BACnet_BACnetDev_doBacnetAVObjectIdUpdate(SedonaVM* vm, Cell* params);

// float BACnetDev.doBacnetAVObjectIdBkp(int)
Cell BACnet_BACnetDev_doBacnetAVObjectIdBkp(SedonaVM* vm, Cell* params);

// float BACnetDev.doBacnetAIValueStatus(int)
Cell BACnet_BACnetDev_doBacnetAIValueStatus(SedonaVM* vm, Cell* params);

// bool BACnetDev.doBacnetBIValueStatus(int)
Cell BACnet_BACnetDev_doBacnetBIValueStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBVValueStatus(int)
Cell BACnet_BACnetDev_doBacnetBVValueStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBVPriorityStatus(int, bool, int)
Cell BACnet_BACnetDev_doBacnetBVPriorityStatus(SedonaVM* vm, Cell* params);

// bool BACnetDev.doBacnetBVOverrideStatus()
Cell BACnet_BACnetDev_doBacnetBVOverrideStatus(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBVValueUpdate(bool, bool, int)
Cell BACnet_BACnetDev_doBacnetBVValueUpdate(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBVOverrideInst()
Cell BACnet_BACnetDev_doBacnetBVOverrideInst(SedonaVM* vm, Cell* params);

// int BACnetDev.doBacnetBVObjectIdUpdate(int, bool, int)
Cell BACnet_BACnetDev_doBacnetBVObjectIdUpdate(SedonaVM* vm, Cell* params);

// bool BACnetDev.doBacnetBVObjectIdBkp(int)
Cell BACnet_BACnetDev_doBacnetBVObjectIdBkp(SedonaVM* vm, Cell* params);

// native table for kit 85
NativeMethod kitNatives85[] = 
{
  BACnet_BACnetDev_doBacnetInit,  // 85::0
  BACnet_BACnetDev_doBacnetInitStatus,  // 85::1
  BACnet_BACnetDev_doBacnetBOValueStatus,  // 85::2
  BACnet_BACnetDev_doBacnetBOPriorityStatus,  // 85::3
  BACnet_BACnetDev_doBacnetBOOverrideStatus,  // 85::4
  BACnet_BACnetDev_doBacnetBOValueUpdate,  // 85::5
  BACnet_BACnetDev_doBacnetBOOverrideInst,  // 85::6
  BACnet_BACnetDev_doBacnetAOValueStatus,  // 85::7
  BACnet_BACnetDev_doBacnetAOPriorityStatus,  // 85::8
  BACnet_BACnetDev_doBacnetAOOverrideStatus,  // 85::9
  BACnet_BACnetDev_doBacnetAOValueUpdate,  // 85::10
  BACnet_BACnetDev_doBacnetAOOverrideInst,  // 85::11
  BACnet_BACnetDev_doBacnetAVValueStatus,  // 85::12
  BACnet_BACnetDev_doBacnetAVPriorityStatus,  // 85::13
  BACnet_BACnetDev_doBacnetAVOverrideStatus,  // 85::14
  BACnet_BACnetDev_doBacnetAVValueUpdate,  // 85::15
  BACnet_BACnetDev_doBacnetAVOverrideInst,  // 85::16
  BACnet_BACnetDev_doBacnetSendPort,  // 85::17
  BACnet_BACnetDev_doBacnetSendDeviceID,  // 85::18
  BACnet_BACnetDev_doBacnetBOObjectIdUpdate,  // 85::19
  BACnet_BACnetDev_doBacnetBOObjectIdBkp,  // 85::20
  BACnet_BACnetDev_doBacnetAOObjectIdUpdate,  // 85::21
  BACnet_BACnetDev_doBacnetAOObjectIdBkp,  // 85::22
  BACnet_BACnetDev_doBacnetAVObjectIdUpdate,  // 85::23
  BACnet_BACnetDev_doBacnetAVObjectIdBkp,  // 85::24
  NULL,                           // 85::25
  NULL,                           // 85::26
  BACnet_BACnetDev_doBacnetAIValueStatus,  // 85::27
  BACnet_BACnetDev_doBacnetBIValueStatus,  // 85::28
  BACnet_BACnetDev_doBacnetBVValueStatus,  // 85::29
  BACnet_BACnetDev_doBacnetBVPriorityStatus,  // 85::30
  BACnet_BACnetDev_doBacnetBVOverrideStatus,  // 85::31
  BACnet_BACnetDev_doBacnetBVValueUpdate,  // 85::32
  BACnet_BACnetDev_doBacnetBVOverrideInst,  // 85::33
  BACnet_BACnetDev_doBacnetBVObjectIdUpdate,  // 85::34
  BACnet_BACnetDev_doBacnetBVObjectIdBkp,  // 85::35
};

////////////////////////////////////////////////////////////////
// BBBDigitalIo (kitId=97)
////////////////////////////////////////////////////////////////

// int Dio_BBB.doInit(int, int, bool)
Cell BBBDigitalIo_Dio_BBB_doInit(SedonaVM* vm, Cell* params);

// int Dio_BBB.doRead(int, int)
Cell BBBDigitalIo_Dio_BBB_doRead(SedonaVM* vm, Cell* params);

// int Dio_BBB.doWrite(int, int, bool)
Cell BBBDigitalIo_Dio_BBB_doWrite(SedonaVM* vm, Cell* params);

// native table for kit 97
NativeMethod kitNatives97[] = 
{
  BBBDigitalIo_Dio_BBB_doInit,    // 97::0
  BBBDigitalIo_Dio_BBB_doRead,    // 97::1
  BBBDigitalIo_Dio_BBB_doWrite,   // 97::2
};

////////////////////////////////////////////////////////////////
// Native Table
////////////////////////////////////////////////////////////////

NativeMethod* nativeTable[] = 
{
  kitNatives0,     // 0
  NULL,            // 1
  kitNatives2,     // 2
  NULL,            // 3
  kitNatives4,     // 4
  NULL,            // 5
  NULL,            // 6
  NULL,            // 7
  NULL,            // 8
  kitNatives9,     // 9
  NULL,            // 10
  NULL,            // 11
  NULL,            // 12
  NULL,            // 13
  NULL,            // 14
  NULL,            // 15
  NULL,            // 16
  NULL,            // 17
  NULL,            // 18
  NULL,            // 19
  NULL,            // 20
  NULL,            // 21
  NULL,            // 22
  NULL,            // 23
  NULL,            // 24
  NULL,            // 25
  NULL,            // 26
  NULL,            // 27
  NULL,            // 28
  NULL,            // 29
  NULL,            // 30
  NULL,            // 31
  NULL,            // 32
  NULL,            // 33
  NULL,            // 34
  NULL,            // 35
  NULL,            // 36
  NULL,            // 37
  NULL,            // 38
  NULL,            // 39
  NULL,            // 40
  NULL,            // 41
  NULL,            // 42
  NULL,            // 43
  NULL,            // 44
  NULL,            // 45
  NULL,            // 46
  NULL,            // 47
  NULL,            // 48
  NULL,            // 49
  NULL,            // 50
  NULL,            // 51
  NULL,            // 52
  NULL,            // 53
  NULL,            // 54
  NULL,            // 55
  NULL,            // 56
  NULL,            // 57
  NULL,            // 58
  NULL,            // 59
  NULL,            // 60
  NULL,            // 61
  NULL,            // 62
  NULL,            // 63
  NULL,            // 64
  NULL,            // 65
  NULL,            // 66
  NULL,            // 67
  NULL,            // 68
  NULL,            // 69
  NULL,            // 70
  NULL,            // 71
  NULL,            // 72
  NULL,            // 73
  NULL,            // 74
  NULL,            // 75
  NULL,            // 76
  NULL,            // 77
  NULL,            // 78
  NULL,            // 79
  NULL,            // 80
  NULL,            // 81
  NULL,            // 82
  NULL,            // 83
  NULL,            // 84
  kitNatives85,    // 85
  NULL,            // 86
  NULL,            // 87
  NULL,            // 88
  NULL,            // 89
  NULL,            // 90
  NULL,            // 91
  NULL,            // 92
  NULL,            // 93
  NULL,            // 94
  NULL,            // 95
  NULL,            // 96
  kitNatives97,    // 97
};

////////////////////////////////////////////////////////////////
// Native Id Check
////////////////////////////////////////////////////////////////

#ifdef SCODE_DEBUG
int isNativeIdValid(int kitId, int methodId)
{
  switch(kitId)
  {
    case 0:
      if (methodId >= 60) return 0;
      else return kitNatives0[methodId] != NULL;
    case 2:
      if (methodId >= 17) return 0;
      else return kitNatives2[methodId] != NULL;
    case 4:
      if (methodId >= 3) return 0;
      else return kitNatives4[methodId] != NULL;
    case 9:
      if (methodId >= 3) return 0;
      else return kitNatives9[methodId] != NULL;
    case 85:
      if (methodId >= 36) return 0;
      else return kitNatives85[methodId] != NULL;
    case 97:
      if (methodId >= 3) return 0;
      else return kitNatives97[methodId] != NULL;
    default:
       return 0;
  }
}
#endif


