/*
 * Copyright (c) 2001,2003,2004 David H. Hovemeyer <daveho@cs.umd.edu>
 * Copyright (c) 2003,2013,2014 Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 *
 * All rights reserved.
 *
 * This code may not be resdistributed without the permission of the copyright holders.
 * Any student solutions using any of this code base constitute derviced work and may
 * not be redistributed in any form.  This includes (but is not limited to) posting on
 * public forums or web sites, providing copies to (past, present, or future) students
 * enrolled in similar operating systems courses the University of Maryland's CMSC412 course.
 */

#include <conio.h>
#include <process.h>

#define MAXSIZE 20

int main(int argc __attribute__ ((unused)), char **argv
         __attribute__ ((unused))) {
	struct Process_Info process[MAXSIZE] = { 0 };

	int p_count = PS(process, MAXSIZE);

	if (p_count == 0) {
		Print("Failed: Not enough memory\n");
		Exit(-7);
	}
	else if (p_count < 0) {
		Print("Failed\n");
		Exit(-1);
	}

	Print("PID PPID PRIO STAT AFF TIME COMMAND\n");

	for (int i = 0; i < p_count; i++) {
		Print("%3d %4d %4d ", process[i].pid, process[i].parent_pid, process[i].priority);

		if (process[i].status == STATUS_RUNNABLE)
			Print("%2d%2c ", process[i].currCore, 'R');
		else if (process[i].status == STATUS_BLOCKED)
			Print("%4c ", 'B');
		else if (process[i].status == STATUS_ZOMBIE)
			Print("%4c ", 'Z');

		if (process[i].affinity == -1)
			Print("%3c %4d %s\n", 'A', process[i].totalTime, process[i].name);
		else
			Print("%3d %4d %s\n", process[i].affinity, process[i].totalTime, process[i].name);
	}

	return 0;
}