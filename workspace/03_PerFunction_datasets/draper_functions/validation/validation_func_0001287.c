mirror_status(struct dm_target *ti, status_type_t type,
			  unsigned status_flags, char *result, unsigned maxlen)
{
	unsigned int m, sz = 0;
	int num_feature_args = 0;
	struct mirror_set *ms = (struct mirror_set *) ti->private;
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	char buffer[ms->nr_mirrors + 1];

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%d ", ms->nr_mirrors);
		for (m = 0; m < ms->nr_mirrors; m++) {
			DMEMIT("%s ", ms->mirror[m].dev->name);
			buffer[m] = device_status_char(&(ms->mirror[m]));
		}
		buffer[m] = '\0';

		DMEMIT("%llu/%llu 1 %s ",
		      (unsigned long long)log->type->get_sync_count(log),
		      (unsigned long long)ms->nr_regions, buffer);

		sz += log->type->status(log, type, result+sz, maxlen-sz);

		break;

	case STATUSTYPE_TABLE:
		sz = log->type->status(log, type, result, maxlen);

		DMEMIT("%d", ms->nr_mirrors);
		for (m = 0; m < ms->nr_mirrors; m++)
			DMEMIT(" %s %llu", ms->mirror[m].dev->name,
			       (unsigned long long)ms->mirror[m].offset);

		num_feature_args += !!errors_handled(ms);
		num_feature_args += !!keep_log(ms);
		if (num_feature_args) {
			DMEMIT(" %d", num_feature_args);
			if (errors_handled(ms))
				DMEMIT(" handle_errors");
			if (keep_log(ms))
				DMEMIT(" keep_log");
		}

		break;
	}
}
