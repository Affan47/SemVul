globus_l_next_file_exists(
    globus_l_job_manager_logfile_state_t *      state)
{
    struct tm                           next_day;
    char *                              next_log;
    globus_bool_t                       file_exists = GLOBUS_FALSE;

    next_day = state->start_timestamp;
    next_day.tm_mday++;
    globus_l_job_manager_normalize_date(&next_day);
    next_day.tm_sec = 0;
    next_day.tm_min = 0;
    next_day.tm_hour = 0;

    next_log = globus_common_create_string(
                "%s/%4d%02d%02d",
                state->log_dir,
                next_day.tm_year+1900,
                next_day.tm_mon+1,
                next_day.tm_mday);
    if (access(next_log, R_OK) == 0)
    {
        file_exists = GLOBUS_TRUE;
    }
    free(next_log);

    return file_exists;
}
