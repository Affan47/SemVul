get_left_neighbor_position(struct tree_balance *tb, int h)
{
	int Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	RFALSE(PATH_H_PPARENT(tb->tb_path, h) == NULL || tb->FL[h] == NULL,
	       "vs-12325: FL[%d](%p) or F[%d](%p) does not exist",
	       h, tb->FL[h], h, PATH_H_PPARENT(tb->tb_path, h));

	if (Sh_position == 0)
		return B_NR_ITEMS(tb->FL[h]);
	else
		return Sh_position - 1;
}
