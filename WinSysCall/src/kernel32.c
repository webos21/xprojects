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

#include <kernel32.h>
#include <dlfcn.h>

static void *_g_k32dll = NULL;
static k32sc_t _g_k32fp;

k32sc_t *k32_getFP() {
	if (NULL == _g_k32dll) {
		// load the [kernel32.dll]
		_g_k32dll = dlopen("kernel32.dll", 0);
		if (NULL == _g_k32dll) {
			printf("cannot load [kernel32.dll]");
			return NULL;
		}

		// mapping the [kernel32.dll] APIs
		//_g_k32fp.FP_GetExitCodeProcess = dlsym(_g_k32dll, "GetExitCodeProcess");

	}
	return &_g_k32fp;
}
