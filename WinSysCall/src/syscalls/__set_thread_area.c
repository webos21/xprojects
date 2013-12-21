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

#include <sys/types.h>
#include <linux/unistd.h>
#include <asm/ldt.h>

// sets an entry in the current thread's thread-local storage (TLS) array
// ref {
//   http://linux.die.net/man/2/set_thread_area
// }
// int __set_thread_area(struct user_desc *u_info); 
int __set_thread_area(struct user_desc *u_info) {
	ntsc_t *ntfp = ntdll_getFP();
	ntfp->FP_DbgPrint("__set_thread_area() is called, but it is not implemented!!!\n");
	errno = 0;
	return 0;
}
