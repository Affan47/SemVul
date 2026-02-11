slurmdb_report_set_start_end_time(time_t *start, time_t *end)
{
	time_t my_time = time(NULL);
	time_t temp_time;
	struct tm start_tm;
	struct tm end_tm;
	int sent_start = (*start), sent_end = (*end);


	if(!sent_end) {
		if(!localtime_r(&my_time, &end_tm)) {
			error("Couldn't get localtime from end %ld",
			      (long)my_time);
			return SLURM_ERROR;
		}
		end_tm.tm_hour = 0;

	} else {
		temp_time = sent_end;
		if(!localtime_r(&temp_time, &end_tm)) {
			error("Couldn't get localtime from user end %ld",
			      (long)my_time);
			return SLURM_ERROR;
		}
		if(end_tm.tm_sec >= 30)
			end_tm.tm_min++;
		if(end_tm.tm_min >= 30)
			end_tm.tm_hour++;
	}

	end_tm.tm_sec = 0;
	end_tm.tm_min = 0;
	end_tm.tm_isdst = -1;
	(*end) = mktime(&end_tm);

	if(!sent_start) {
		if(!localtime_r(&my_time, &start_tm)) {
			error("Couldn't get localtime from start %ld",
			      (long)my_time);
			return SLURM_ERROR;
		}
		start_tm.tm_hour = 0;
		start_tm.tm_mday--;

	} else {
		temp_time = sent_start;
		if(!localtime_r(&temp_time, &start_tm)) {
			error("Couldn't get localtime from user start %ld",
			      (long)my_time);
			return SLURM_ERROR;
		}
		if(start_tm.tm_sec >= 30)
			start_tm.tm_min++;
		if(start_tm.tm_min >= 30)
			start_tm.tm_hour++;
	}
	start_tm.tm_sec = 0;
	start_tm.tm_min = 0;
	start_tm.tm_isdst = -1;
	(*start) = mktime(&start_tm);

	if((*end)-(*start) < 3600)
		(*end) = (*start) + 3600;


	return SLURM_SUCCESS;
}
