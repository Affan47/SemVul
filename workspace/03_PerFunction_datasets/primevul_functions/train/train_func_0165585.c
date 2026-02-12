static void ext4_write_super_lockfs(struct super_block *sb)
{
	sb->s_dirt = 0;

	if (!(sb->s_flags & MS_RDONLY)) {
		journal_t *journal = EXT4_SB(sb)->s_journal;

		if (journal) {

			jbd2_journal_lock_updates(journal);


			if (jbd2_journal_flush(journal) < 0)
				return;
		}


		EXT4_CLEAR_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_RECOVER);
		ext4_commit_super(sb, EXT4_SB(sb)->s_es, 1);
	}
}
