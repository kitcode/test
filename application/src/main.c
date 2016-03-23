/* main.c - dining philosophers */

/*
 * Copyright (c) 2015-2016 Wind River Systems, Inc.
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


/*
 * Microkernel version of the classic Dining Philosopher problem shows how to
 * implement a multi-threaded application.
 */

#include <zephyr.h>
#include "phil.h"

#define DEMO_DESCRIPTION  \
	"\x1b[2J\x1b[15;1H"   \
	"Demo Description\n"  \
	"----------------\n"  \
	"An implementation of a solution to the Dining Philosophers problem\n"  \
	"(a classic multi-thread synchronization problem).  This particular\n"  \
	"implementation demonstrates the usage of multiple (6) %s\n"            \
	"of differing priorities and the %s semaphores and timers."

/**
 *
 * @brief Routine to start dining philosopher demo
 *
 * @return does not return
 */

void main(void)
{
	PRINTF(DEMO_DESCRIPTION, "tasks", "microkernel");

	task_group_start(PHI);

	/* wait forever */
	while (1) {
		task_sleep(10000);
	}
}

