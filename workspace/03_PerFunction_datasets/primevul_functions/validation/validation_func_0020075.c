*/
static unsigned int bfq_update_depths(struct bfq_data *bfqd,
				      struct sbitmap_queue *bt)
{
	unsigned int i, j, min_shallow = UINT_MAX;


	bfqd->word_depths[0][0] = max((1U << bt->sb.shift) >> 1, 1U);


	bfqd->word_depths[0][1] = max(((1U << bt->sb.shift) * 3) >> 2, 1U);


	bfqd->word_depths[1][0] = max(((1U << bt->sb.shift) * 3) >> 4, 1U);

	bfqd->word_depths[1][1] = max(((1U << bt->sb.shift) * 6) >> 4, 1U);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			min_shallow = min(min_shallow, bfqd->word_depths[i][j]);

	return min_shallow;
}
