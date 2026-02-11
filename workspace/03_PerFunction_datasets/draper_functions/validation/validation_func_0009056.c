work_queue_tune(struct work_queue *q, const char *name, double value)
{

	if(!strcmp(name, "asynchrony-multiplier")) {
		q->asynchrony_multiplier = MAX(value, 1.0);

	} else if(!strcmp(name, "asynchrony-modifier")) {
		q->asynchrony_modifier = MAX(value, 0);

	} else if(!strcmp(name, "min-transfer-timeout")) {
		wq_minimum_transfer_timeout = (int)value;

	} else if(!strcmp(name, "foreman-transfer-timeout")) {
		wq_foreman_transfer_timeout = (int)value;

	} else if(!strcmp(name, "fast-abort-multiplier")) {
		if(value >= 1) {
			q->fast_abort_multiplier = value;
		} else if(value< 0) {
			q->fast_abort_multiplier = value;
		} else {
			q->fast_abort_multiplier = -1.0;
		}
	} else if(!strcmp(name, "keepalive-interval")) {
		q->keepalive_interval = MAX(0, (int)value);

	} else if(!strcmp(name, "keepalive-timeout")) {
		q->keepalive_timeout = MAX(0, (int)value);

	} else {
		debug(D_NOTICE|D_WQ, "Warning: tuning parameter \"%s\" not recognized\n", name);
		return -1;
	}

	return 0;
}
