/* phil.c - dining philosopher */

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

#include <arch/cpu.h>	/* irq_lock/irq_unlock */

#define FORK(x) forks[x]
#define TAKE(x) task_mutex_lock(x, TICKS_UNLIMITED)
#define GIVE(x) task_mutex_unlock(x)
#define RANDDELAY(x) myDelay(((sys_tick_get_32() * ((x) +1)) & 0x1f) + 1)

#define PRINT(x,y)	myPrint(x,y)

kmutex_t forks[] = {forkMutex0, forkMutex1, forkMutex2, forkMutex3, forkMutex4, forkMutex5};

/**
 *
 * @brief Print a philosophers state
 *
 * @param id    Philosopher ID.
 * @param str   EATING or THINKING.
 *
 * @return N/A
 */

static void myPrint(int id, char *str)
{
	PRINTF("\x1b[%d;%dHPhilosopher %d %s\n", id + 1, 1, id, str);
}

/**
 *
 * @brief Wait for a number of ticks to elapse
 *
 * @param ticks   Number of ticks to delay.
 *
 * @return N/A
 */

static void myDelay(int ticks)
{
	task_sleep(ticks);
}

/**
 *
 * @brief Entry point to a philosopher's thread
 *
 * This routine runs as a task in the microkernel environment
 *
 * @return N/A
 */

void philEntry(void)
{
	kmutex_t f1;		/* fork #1 */
	kmutex_t f2;		/* fork #2 */

	static int myId;        /* next philosopher ID */
	int pri = irq_lock();   /* interrupt lock level */
	int id = myId++;        /* current philosopher ID */

	irq_unlock(pri);

	/* always take the lowest fork first */
	if ((id+1) != N_PHILOSOPHERS) {
		f1 = FORK(id);
		f2 = FORK(id + 1);
	} else {
		f1 = FORK(0);
		f2 = FORK(id);
	}

	while (1) {
		TAKE(f1);
		TAKE(f2);

		PRINT(id, "EATING  ");
		RANDDELAY(id);

		GIVE(f2);
		GIVE(f1);

		PRINT(id, "THINKING");
		RANDDELAY(id);
	}
}
