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

#include <windows.h>

#include <ntdll.h>

//#pragma comment(lib, "kernel32.lib")

/*
#define PAGE_NOACCESS          0x01     
#define PAGE_READONLY          0x02     
#define PAGE_READWRITE         0x04     
#define PAGE_WRITECOPY         0x08     
#define PAGE_EXECUTE           0x10     
#define PAGE_EXECUTE_READ      0x20     
#define PAGE_EXECUTE_READWRITE 0x40     
#define PAGE_EXECUTE_WRITECOPY 0x80     
#define PAGE_GUARD            0x100     
#define PAGE_NOCACHE          0x200     
#define PAGE_WRITECOMBINE     0x400     


#define SECTION_QUERY                0x0001
#define SECTION_MAP_WRITE            0x0002
#define SECTION_MAP_READ             0x0004
#define SECTION_MAP_EXECUTE          0x0008
#define SECTION_EXTEND_SIZE          0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT 0x0020 // not included in SECTION_ALL_ACCESS

#define FILE_MAP_COPY       SECTION_QUERY
#define FILE_MAP_WRITE      SECTION_MAP_WRITE
#define FILE_MAP_READ       SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS SECTION_ALL_ACCESS
#define FILE_MAP_EXECUTE    SECTION_MAP_EXECUTE_EXPLICIT    // not included in FILE_MAP_ALL_ACCESS

typedef WCHAR *LPCTSTR;

extern HANDLE CreateFileMappingA(
	__in      HANDLE hFile,
	__in_opt  LPSECURITY_ATTRIBUTES lpAttributes,
	__in      DWORD flProtect,
	__in      DWORD dwMaximumSizeHigh,
	__in      DWORD dwMaximumSizeLow,
	__in_opt  LPCTSTR lpName
	);

extern LPVOID MapViewOfFile(
	__in  HANDLE hFileMappingObject,
	__in  DWORD dwDesiredAccess,
	__in  DWORD dwFileOffsetHigh,
	__in  DWORD dwFileOffsetLow,
	__in  SIZE_T dwNumberOfBytesToMap
	);

extern BOOL CloseHandle(
	__in  HANDLE hObject
	);


extern int printf(const char *format, ...);
extern char *strcpy(char *strDestination, const char *strSource);

extern VOID Sleep(DWORD dwMilliseconds);
extern DWORD GetLastError(void);
extern HANDLE GetCurrentProcess(void);
extern DWORD GetCurrentProcessId(void);

*/

int main(int argc, char *argv[]) {
	NTSTATUS status;
	RTL_USER_PROCESS_INFORMATION  *pi;
	char sbuf[1024];

	ntsc_t *ntfp = ntdll_getFP();

	//ntfp->FP_RtlExitUserProcess(3);


	SECURITY_ATTRIBUTES sa;
	HANDLE maph = NULL;
	char *map = NULL;
	PROCESS_BASIC_INFORMATION pbi;

	sa.nLength = sizeof sa;
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	pi = ntfp->FP_RtlAllocateHeap(DRtlGetProcessHeap(ntfp), 0, 4096);
	ntfp->FP_RtlZeroMemory(pi, 4096);
	//pi->Size = sizeof(RTL_USER_PROCESS_INFORMATION);

	maph = CreateFileMappingA(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, 4096, NULL);
	if (!maph) {
		ntfp->FP_DbgPrint("CreateFileMapping failed, err %lu\n", GetLastError());
		//printf ("CreateFileMapping failed, err %lu\n", GetLastError());
	} else {
		map = (char *) MapViewOfFile(maph, FILE_MAP_WRITE, 0, 0, 4096);
		//map = NULL;
		if (!map) {
			ntfp->FP_DbgPrint("MapViewOfFile failed, err %lu\n", GetLastError());
			//printf ("MapViewOfFile failed, err %lu\n", GetLastError());
		}
	}

	if (map) {
		ntfp->FP_DbgPrint("map at %p\n", map);
		//printf ("map at %p\n", map);
		//strcpy (map, "Alle meine Entchen");
		ntfp->FP_RtlCopyMemory(map, "Alle meine Entchen", 18);
	}

	//pi.Size = sizeof(RTL_USER_PROCESS_INFORMATION);
	status = ntfp->FP_RtlCloneUserProcess (RTL_CLONE_PROCESS_FLAGS_INHERIT_HANDLES
		| RTL_CLONE_PROCESS_FLAGS_NO_SYNCHRONIZE,
		NULL, NULL, NULL, pi);
	switch (status)	{
	case STATUS_SUCCESS:
		ntfp->FP_DbgPrint("RtlCloneUserProcess in parent %lu, child pid  = %lu\n",
			GetCurrentProcessId (), pi->ClientId.UniqueProcess);
		//printf ("RtlCloneUserProcess in parent %lu, child pid  = %lu\n",
		//	GetCurrentProcessId (), pi.ClientId.UniqueProcess);
		if (map) {
			ntfp->FP_DbgPrint("parent map: <%s>\n", map);
			//printf ("parent map: <%s>\n", map);
			Sleep (1000L);
			strcpy (map, "schwimmen auf dem See");
			Sleep (2000L);
			ntfp->FP_DbgPrint("parent map: <%s>\n", map);
			//printf ("parent map: <%s>\n", map);
		}
		break;
	case STATUS_PROCESS_CLONED:
		ZeroMemory(sbuf, sizeof(sbuf));
		status = ntfp->FP_NtQueryInformationProcess(GetCurrentProcess(),
			ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
		if (!NT_SUCCESS(status)) {
			sprintf (sbuf, "NtQueryInformationProcess failed, status 0x%08lx / RtlCloneUserProcess in child  %lu",
				status, GetCurrentProcessId ());
		} else {
			sprintf (sbuf, "RtlCloneUserProcess in child  %lu, parent pid = %lu",
				GetCurrentProcessId (), pbi.InheritedFromUniqueProcessId);
		}
		if (map) {
			ntfp->FP_DbgPrint("child map: <%s>\n", map);
			//printf ("child map: <%s>\n", map);
			Sleep (2000L);
			ntfp->FP_DbgPrint("child map: <%s>\n", map);
			//printf ("child map: <%s>\n", map);
			strcpy (map, sbuf);
		}
		ntfp->FP_DbgPrint("child exits\n");
		//printf ("child exits\n");
		break;
	default:
		ntfp->FP_DbgPrint("RtlCloneUserProcess failed, status 0x%08lx\n", status);
		//printf("RtlCloneUserProcess failed, status 0x%08lx\n", status);
		break;
	}

	ntfp->FP_RtlFreeHeap(DRtlGetProcessHeap(ntfp), 0, pi);
	//ntfp->FP_RtlExitUserProcess(0x0);

	return 0;
}
