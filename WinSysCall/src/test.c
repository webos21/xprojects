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

int test_fork() {
	int npid = __fork();
	if (npid == 0) {
		printf("Parent Process!!!\n");
		return 0;
	} else if (npid > 0) {
		printf("Child Process!!! (pid=%d)\n", npid);
		return npid;
	} else {
		printf("error!!!!!!!!!\n");
		return npid;
	}
	return -1;
}

int main(int argc, char *argv[]) {
	test_fork();

	return 0;
}
