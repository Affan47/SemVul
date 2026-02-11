check_log_file_size(struct auditd_consumer_data *data)
{
	struct daemon_conf *config = data->config;


	off_t sz = log_size / MEGABYTE;

	if (sz >= config->max_log_size && (config->daemonize == D_BACKGROUND)) {
		switch (config->max_log_size_action)
		{
			case SZ_IGNORE:
				break;
			case SZ_SYSLOG:
				audit_msg(LOG_ERR,
			    "Audit daemon log file is larger than max size");
				break;
			case SZ_SUSPEND:
				audit_msg(LOG_ERR,
		    "Audit daemon is suspending logging due to logfile size.");
				logging_suspended = 1;
				break;
			case SZ_ROTATE:
				if (data->config->num_logs > 1) {
					audit_msg(LOG_NOTICE,
					    "Audit daemon rotating log files");
						rotate_logs(data, 0);
				}
				break;
			case SZ_KEEP_LOGS:
				audit_msg(LOG_NOTICE,
			    "Audit daemon rotating log files with keep option");
					shift_logs(data);
				break;
			default:
				audit_msg(LOG_ALERT,
  "Audit daemon log file is larger than max size and unknown action requested");
				break;
		}
	}
}
