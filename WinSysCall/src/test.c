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

#include "test.h"

void tsleep(int msec) {
	LARGE_INTEGER x;
	ntsc_t *ntfp = ntdll_getFP();
	x.QuadPart = msec * -10000;
	ntfp->FP_NtDelayExecution(FALSE, &x);
}

int test_fork() {
	int cret = 0;
	int npid = __fork();
	if (npid > 0) {
		printf("Parent Process!!! (child pid=%d)\n", npid);
		wait4(npid, &cret, 0, NULL);
		printf("result of child process = %d\n", cret);
		return 0;
	} else if (npid == 0) {
		printf("Child Process!!!\n");
		tsleep(3000);
		W_exit(-3); // test : process return -3
		return 0;   // for compiler's happyness
	} else {
		printf("error!!!!!!!!!\n");
		return npid;
	}
}

int test_exit_with_stack_teardown() {
	int status = 0x3;
	_exit_with_stack_teardown(NULL, 0, &status);
	return 0;
}

static void *test_pthread(void *args) {
	int x = (int) args;
	printf("PThread - %d\n", x);
	return NULL;
}

static int test_bthread(void *args) {
	int x = (int) args;
	printf("BThread - %d\n", x);
	return x;
}

void __bionic_clone_entry( int (*fn)(void *), void *arg ) {
	int ret = (*fn)(arg);
	_exit_thread(ret);
}

int test__pthread_clone() {
	int x = 333;
	__pthread_clone(&test_pthread, NULL, 0, (void*)x);
	return 0;
}

int test__bionic_clone() {
	int x = 333;
	__bionic_clone(0, NULL, NULL, NULL, NULL, &test_bthread, (void*)x);
	return 0;
}

int main(int argc, char *argv[]) {
	int i = 0;
	int x = 0;

	test_fork();
	//test__pthread_clone();
	//test__bionic_clone();
	//Sleep(1000);

	return 0;
}
