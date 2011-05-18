/** @file     reparselib.h
 *  @brief    A header file of a library for working
 *            with NTFS Reparse Points
 *  @author   amdf
 *  @version  0.1
 *  @date     May 2011
 */

#ifdef REPARSELIB_EXPORTS
#define REPARSELIB_API extern "C" __declspec(dllexport)
#else
#define REPARSELIB_API extern "C" __declspec(dllimport)
#endif

#ifndef REPARSE_DATA_BUFFER

#define SYMLINK_FLAG_RELATIVE   1

typedef struct _REPARSE_DATA_BUFFER {
    ULONG  ReparseTag;
    USHORT ReparseDataLength;
    USHORT Reserved;
    union {
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            ULONG Flags;
            WCHAR PathBuffer[1];
        } SymbolicLinkReparseBuffer;
        struct {
            USHORT SubstituteNameOffset;
            USHORT SubstituteNameLength;
            USHORT PrintNameOffset;
            USHORT PrintNameLength;
            WCHAR PathBuffer[1];
        } MountPointReparseBuffer;
        struct {
            UCHAR  DataBuffer[1];
        } GenericReparseBuffer;
    } DUMMYUNIONNAME;
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;

#endif

REPARSELIB_API BOOL ReparsePointExists(IN LPCWSTR sFileName);
REPARSELIB_API BOOL GetReparseGUID(IN LPCWSTR sFileName, GUID* pGuid);
REPARSELIB_API BOOL GetReparseTag(IN LPCWSTR sFileName, DWORD* pTag);
REPARSELIB_API BOOL DeleteReparsePoint(IN LPCWSTR sFileName);
REPARSELIB_API BOOL CreateCustomReparsePoint
(
  IN LPCWSTR  sFileName,
  IN PVOID    pBuffer,
  IN UINT     uBufSize,
  IN GUID     uGuid,
  IN ULONG    uReparseTag
);