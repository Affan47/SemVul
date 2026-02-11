unlink_unused_bblocks (MonoCompile *cfg)
{
	int i, j;
	MonoBasicBlock *bb;

	g_assert (cfg->comp_done & MONO_COMP_REACHABILITY);

	if (G_UNLIKELY (cfg->verbose_level > 1))
		printf ("\nUNLINK UNUSED BBLOCKS:\n");

	for (bb = cfg->bb_entry; bb && bb->next_bb;) {
		if (!(bb->next_bb->flags & BB_REACHABLE)) {
			bb->next_bb = bb->next_bb->next_bb;
		} else
			bb = bb->next_bb;
	}

	for (i = 1; i < cfg->num_bblocks; i++) {
		bb = cfg->bblocks [i];

		if (!(bb->flags & BB_REACHABLE)) {
			for (j = 0; j < bb->in_count; j++) {
				unlink_target (bb->in_bb [j], bb);
			}
			for (j = 0; j < bb->out_count; j++) {
				unlink_target (bb, bb->out_bb [j]);
			}
			if (G_UNLIKELY (cfg->verbose_level > 1))
				printf ("\tUnlinked BB%d\n", bb->block_num);
		}

	}
}
