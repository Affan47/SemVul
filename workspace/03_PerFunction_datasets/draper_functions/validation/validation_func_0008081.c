btt_freelist_init(struct arena_info *arena)
{
	int old, new, ret;
	u32 i, map_entry;
	struct log_entry log_new, log_old;

	arena->freelist = kcalloc(arena->nfree, sizeof(struct free_entry),
					GFP_KERNEL);
	if (!arena->freelist)
		return -ENOMEM;

	for (i = 0; i < arena->nfree; i++) {
		old = btt_log_read(arena, i, &log_old, LOG_OLD_ENT);
		if (old < 0)
			return old;

		new = btt_log_read(arena, i, &log_new, LOG_NEW_ENT);
		if (new < 0)
			return new;


		arena->freelist[i].sub = 1 - new;
		arena->freelist[i].seq = nd_inc_seq(le32_to_cpu(log_new.seq));
		arena->freelist[i].block = le32_to_cpu(log_new.old_map);


		if (log_new.old_map == log_new.new_map)
			continue;


		ret = btt_map_read(arena, le32_to_cpu(log_new.lba), &map_entry,
				NULL, NULL);
		if (ret)
			return ret;
		if ((le32_to_cpu(log_new.new_map) != map_entry) &&
				(le32_to_cpu(log_new.old_map) == map_entry)) {


			ret = btt_map_write(arena, le32_to_cpu(log_new.lba),
					le32_to_cpu(log_new.new_map), 0, 0);
			if (ret)
				return ret;
		}

	}

	return 0;
}
