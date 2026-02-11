output_queue(size_t line, ssize_t max)
{
	ssize_t i, j;
	struct task *tasks = global.tasks;
	struct task *filtered_tasks = calloc(global.n, sizeof(*filtered_tasks));
	OOM_CHECK(filtered_tasks);
	for (i=0,j=0;i<global.n;i++) {
		if (detail_selected == -1 || detail_is_selected(tasks[i].clamd_no-1)) {
			filtered_tasks[j++] = tasks[i];
		}
	}

	wattron(stats_window, COLOR_PAIR(queue_header_color));
	mvwprintw(stats_window, line++, 0, "%s", queue_header);
	wattroff(stats_window, COLOR_PAIR(queue_header_color));
	if (max >= j)
		max = j;
	else
		--max;
	if (max < 0) max = 0;
	for(i=0;i<max;i++) {
		char *cmde;
		assert(tasks);
		cmde = strchr(filtered_tasks[i].line, ' ');
		if(cmde) {
			char cmd[16];
			const char *filstart = strchr(cmde + 1, ' ');
			strncpy(cmd, filtered_tasks[i].line, sizeof(cmd)-1);
			cmd[15]='\0';
			if (filtered_tasks[i].line+15 > cmde)
				cmd[cmde - filtered_tasks[i].line] = '\0';
			if(filstart) {
				++filstart;
				if (detail_selected == -1 && global.num_clamd > 1)
					mvwprintw(stats_window, line + i, 0, "%2u %s", filtered_tasks[i].clamd_no, cmd + 1);
				else
					mvwprintw(stats_window, line + i, 0, " %s", cmd + 1);
				mvwprintw(stats_window, line + i, 15, "%10.03fs", filtered_tasks[i].tim);
				mvwprintw(stats_window, line + i, 30, "%s",filstart);
			}
		}
	}
	if (max < j) {

		wattron(stats_window, A_DIM | COLOR_PAIR(header_color));
		mvwprintw(stats_window, line+i, 0, "*** %u more task(s) not shown ***", (unsigned)(j - max));
		wattroff(stats_window, A_DIM | COLOR_PAIR(header_color));
	}
	free(filtered_tasks);
}
