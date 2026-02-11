write_tag_block(journal_t *j, journal_block_tag_t *tag,
				   unsigned long long block)
{
	tag->t_blocknr = cpu_to_be32(block & (u32)~0);
	if (jbd2_has_feature_64bit(j))
		tag->t_blocknr_high = cpu_to_be32((block >> 31) >> 1);
}
