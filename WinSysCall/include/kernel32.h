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

#ifndef __KERNEL32_H__
#define __KERNEL32_H__

#include "nttypes.h"


//////////////////////////////////////////
// KERNEL32 MACRO
//////////////////////////////////////////


//////////////////////////////////////////
// KERNEL32 Structures
//////////////////////////////////////////


//////////////////////////////////////////
// Structure for KERNEL32 APIs
//////////////////////////////////////////

typedef struct _st_k32sc {
	int unused;
} k32sc_t;


//////////////////////////////////////////
// Macro for KERNEL32 APIs
//////////////////////////////////////////


//////////////////////////////////////////
// Function for getting structure-pointer
//////////////////////////////////////////
k32sc_t *k32_getFP();


#endif // __KERNEL32_H__
