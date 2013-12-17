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

#include <errno.h>
#include <ntdll.h>

// int execve(const char *filename, char *const argv[], char *const envp[]); 
int execve(const char *filename, char *const argv[], char *const envp[]) {

	UNICODE_STRING imgname;
	RTL_USER_PROCESS_PARAMETERS pparam;
	RTL_USER_PROCESS_INFORMATION pinfo;

	ntsc_t *ntfp = ntdll_getFP();

	ntfp->FP_RtlCreateUserProcess(&imgname, 0, &pparam, NULL, NULL, NULL, FALSE, NULL, NULL, &pinfo);

// 	NTSYSAPI_N NTSTATUS (NTAPI *FP_RtlCreateUserProcess) (
// 		__in PUNICODE_STRING  ImageFileName,
// 		__in ULONG  Attributes,
// 		__inout PRTL_USER_PROCESS_PARAMETERS  ProcessParameters,
// 		__in_opt PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
// 		__in_opt PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
// 		__in_opt HANDLE ParentProcess,
// 		__in BOOLEAN  InheritHandles,
// 		__in_opt HANDLE DebugPort,
// 		__in_opt HANDLE ExceptionPort,
// 		__out PRTL_USER_PROCESS_INFORMATION  ProcessInfo
// 		);

}
