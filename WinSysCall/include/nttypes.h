/*
 * Copyright 2013 Cheolmin Jo (webos21@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _NTTYPES_H_
#define _NTTYPES_H_

//////////////////////////////////////////
// ntstatus.h
//////////////////////////////////////////

#ifdef _WINNT_
#pragma warning(push)
#pragma warning(disable:4005)
#include <ntstatus.h>
#pragma warning(pop)
#else  // !_WINNT_
#include <ntstatus.h>
#endif // _WINNT_

#ifdef _WINDOWS_
#pragma warning(push)
#pragma warning(disable:4142)
typedef int                NTSTATUS;
#pragma warning(pop)
#else  // !_WINDOWS_
typedef int                NTSTATUS;
#endif // _WINDOWS_

#define NT_SUCCESS(Status)     (((NTSTATUS)(Status)) >= 0)


//////////////////////////////////////////
// the Specification Strings
//////////////////////////////////////////

#ifndef __ATTR_SAL
#define __allowed(p)                       __$allowed_##p
#define __$allowed_as_global_decl            /* empty */
#define __$allowed_on_function_or_typedecl   /* empty */
#define __$allowed_on_typedecl               /* empty */
#define __$allowed_on_return                 /* empty */
#define __$allowed_on_parameter              /* empty */
#define __$allowed_on_function               /* empty */
#define __$allowed_on_struct                 /* empty */
#define __$allowed_on_field                  /* empty */
#define __$allowed_on_parameter_or_return    /* empty */
#define __$allowed_on_global_or_field        /* empty */

#define __in                               __allowed(on_parameter)
#define __in_opt                           __allowed(on_parameter)

#define __out                              __allowed(on_parameter)
#define __out_opt                          __allowed(on_parameter)

#define __inout                            __allowed(on_parameter)

#define __field_bcount_part(size,init)     __allowed(on_field)
#endif // __ATTR_SAL


//////////////////////////////////////////
// Definition for Declaring Functions
//////////////////////////////////////////

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif //no-NULL

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef CONST
#define CONST const
#endif

// NTSYSAPI(dllimport) is not required!!
//#define NTSYSAPI
#define NTSYSAPI_N

#ifndef NTAPI
#ifdef _MSC_VER
#define NTAPI           __stdcall
#else
#define NTAPI           __attribute__((__stdcall__))
#endif
#endif //NTAPI

#define INVALID_HANDLE_VALUE                     ((HANDLE)(LONG_PTR)-1)
#define INVALID_FILE_SIZE                        ((DWORD)0xFFFFFFFF)
#define INVALID_SET_FILE_POINTER                 ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES                  ((DWORD)-1)

#define HANDLE_FLAG_INHERIT                      0x00000001
#define HANDLE_FLAG_PROTECT_FROM_CLOSE           0x00000002


//////////////////////////////////////////
// NT Types
//////////////////////////////////////////

//////////////
// _W64
//////////////
#if !defined(_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#define _W64 __w64
#else  // __midi/X86...
#define _W64
#endif // !__midi/X86...
#endif // !_W64

//////////////
// RESTRICTED_POINTER
//////////////
#if defined(_M_MRX000) && !(defined(MIDL_PASS) || defined(RC_INVOKED)) && defined(ENABLE_RESTRICTED)
#define RESTRICTED_POINTER __restrict
#else  // !_M_MRX000...
#define RESTRICTED_POINTER
#endif // _M_MRX000...

//////////////
// VOID : VOID,CHAR,SHORT,LONG,INT
//////////////
#ifndef VOID
#define VOID               void
typedef char               CHAR;
typedef short              SHORT;
typedef long               LONG;
#if !defined(MIDL_PASS)
typedef int                INT;
#endif // !MIDL_PASS
#endif // !VOID

//////////////
// BASE : ULONG,PULONG,USHORT,PUSHORT,UCHAR,PUCHAR,PSZ
//////////////
#ifndef BASETYPES
#define BASETYPES
typedef unsigned long      ULONG;
typedef ULONG             *PULONG;
typedef unsigned short     USHORT;
typedef USHORT            *PUSHORT;
typedef unsigned char      UCHAR;
typedef UCHAR             *PUCHAR;
typedef char              *PSZ;
#endif  // !BASETYPES

//////////////
// PTR : INT_PTR,PINT_PTR,UINT_PTR,PUINT_PTR
//////////////
#ifdef _WIN64
typedef long long           INT_PTR, *PINT_PTR;
typedef unsigned long long  UINT_PTR, *PUINT_PTR;

typedef long long           LONG_PTR, *PLONG_PTR;
typedef unsigned long long  ULONG_PTR, *PULONG_PTR;

#define __int3264           __int64

#else // !_WIN64

typedef _W64 int            INT_PTR, *PINT_PTR;
typedef _W64 unsigned int   UINT_PTR, *PUINT_PTR;

typedef _W64 long           LONG_PTR, *PLONG_PTR;
typedef _W64 unsigned long  ULONG_PTR, *PULONG_PTR;

#define __int3264           __int32

#endif // _WIN64

//////////////
// ETC : extensions
//////////////

typedef int                BOOL;

typedef long long          LONGLONG;
typedef unsigned long long ULONGLONG;

typedef VOID              *PVOID;
typedef VOID              *LPVOID;

typedef unsigned short     WCHAR;
typedef WCHAR             *PWCHAR,*LPWCH,*PWCH;

typedef UCHAR              BOOLEAN;    // winnt
typedef BOOLEAN           *PBOOLEAN;   // winnt

typedef ULONG              LOGICAL;
typedef ULONG             *PLOGICAL;

typedef unsigned char      BYTE;

typedef unsigned short     WORD;
typedef unsigned long      DWORD;

typedef WORD              *LPWORD;
typedef DWORD             *LPDWORD;

typedef void              *HANDLE;
typedef HANDLE            *PHANDLE;

typedef DWORD              ACCESS_MASK;
typedef ACCESS_MASK       *PACCESS_MASK;

typedef ULONG_PTR          DWORD_PTR, *PDWORD_PTR;
typedef ULONG_PTR          SIZE_T, *PSIZE_T;

typedef CHAR              *NPSTR, *LPSTR, *PSTR;
typedef CONST char        *PCSZ;
typedef CONST WCHAR       *LPCWSTR, *PCWSTR;
typedef CHAR              *PCHAR, *LPCH, *PCH;
typedef CONST CHAR        *LPCSTR, *PCSTR;


//////////////////////////////////////////
// Structured Types
//////////////////////////////////////////

//////////////
// ANSI_STRING
//////////////
typedef struct _ANSI_STRING {
	USHORT  Length;
	USHORT  MaximumLength;
	PSTR    Buffer;
} ANSI_STRING, STRING, *PSTRING;
typedef ANSI_STRING *PANSI_STRING;
typedef const ANSI_STRING *PCANSI_STRING;

//////////////
// UNICODE_STRING
//////////////
typedef struct _UNICODE_STRING {
	USHORT   Length;
	USHORT   MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
#else // MIDL_PASS
	__field_bcount_part(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING, *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
#define UNICODE_NULL ((WCHAR)0) // winnt

//////////////
// WINNT : LIST_ENTRY, RTL_CRITICAL_SECTION, RTL_SRWLOCK, LARGE_INTEGER, ULARGE_INTEGER
//////////////
#ifndef _WINNT_

typedef struct _LIST_ENTRY {
	struct _LIST_ENTRY       *Flink;
	struct _LIST_ENTRY       *Blink;
} LIST_ENTRY, *PLIST_ENTRY, *RESTRICTED_POINTER PRLIST_ENTRY;

typedef struct _RTL_CRITICAL_SECTION_DEBUG {
	WORD                      Type;
	WORD                      CreatorBackTraceIndex;
	struct _RTL_CRITICAL_SECTION *CriticalSection;
	LIST_ENTRY                ProcessLocksList;
	DWORD                     EntryCount;
	DWORD                     ContentionCount;
	DWORD                     Flags;
	WORD                      CreatorBackTraceIndexHigh;
	WORD                      SpareWORD;
} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, *PRTL_RESOURCE_DEBUG;

#pragma pack(push, 8)
typedef struct _RTL_CRITICAL_SECTION {
	PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
	//  The following three fields control entering and exiting the critical
	//  section for the resource
	LONG                      LockCount;
	LONG                      RecursionCount;
	HANDLE                    OwningThread;     // from the thread's ClientId->UniqueThread
	HANDLE                    LockSemaphore;
	ULONG_PTR                 SpinCount;        // force size on 64-bit systems when packed
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;
#pragma pack(pop)

typedef struct _RTL_SRWLOCK {
	PVOID                     Ptr;
} RTL_SRWLOCK, *PRTL_SRWLOCK;
#define RTL_SRWLOCK_INIT {0}

typedef struct _RTL_CONDITION_VARIABLE {
	PVOID                     Ptr;
} RTL_CONDITION_VARIABLE, *PRTL_CONDITION_VARIABLE;
#define RTL_CONDITION_VARIABLE_INIT {0}
#define RTL_CONDITION_VARIABLE_LOCKMODE_SHARED  0x1

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
#endif //MIDL_PASS
	LONGLONG QuadPart;
} LARGE_INTEGER;
typedef LARGE_INTEGER *PLARGE_INTEGER;

#if defined(MIDL_PASS)
typedef struct _ULARGE_INTEGER {
#else // MIDL_PASS
typedef union _ULARGE_INTEGER {
	struct {
		DWORD LowPart;
		DWORD HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		DWORD LowPart;
		DWORD HighPart;
	} u;
#endif //MIDL_PASS
	ULONGLONG QuadPart;
} ULARGE_INTEGER;

typedef ULARGE_INTEGER *PULARGE_INTEGER;

#endif // _WINNT_

//////////////
// WINBASE : SECURITY_ATTRIBUTES
//////////////
#ifndef _WINBASE_
typedef struct _SECURITY_ATTRIBUTES {
	DWORD                     nLength;
	LPVOID                    lpSecurityDescriptor;
	BOOL                      bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
#endif //_WINBASE_

//////////////
// WINDEF : HKEY
//////////////
#ifndef _WINDEF_
typedef struct _HKEY {
	int                       unused;
} HKEY, *PHKEY;
#endif


#endif // _NTTYPES_H_
