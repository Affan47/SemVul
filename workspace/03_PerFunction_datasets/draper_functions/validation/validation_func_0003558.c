_init_raid_segtype(struct cmd_context *cmd,
					       const char *raid_type)
{
	struct segment_type *segtype = dm_zalloc(sizeof(*segtype));

	if (!segtype) {
		log_error("Failed to allocate memory for %s segtype",
			  raid_type);
		return NULL;
	}
	segtype->cmd = cmd;

	segtype->flags = SEG_RAID;
#ifdef DEVMAPPER_SUPPORT
#ifdef DMEVENTD
	if (_get_raid_dso_path(cmd))
		segtype->flags |= SEG_MONITORED;
#endif
#endif
	segtype->parity_devs = strstr(raid_type, "raid6") ? 2 : 1;

	segtype->ops = &_raid_ops;
	segtype->name = raid_type;

	segtype->private = NULL;

	log_very_verbose("Initialised segtype: %s", segtype->name);

	return segtype;
}
