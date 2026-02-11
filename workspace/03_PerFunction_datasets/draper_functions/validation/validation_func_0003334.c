show_all_rnodes()
{
	struct rnode **rnode_h;
	for (rnode_h = rnode_array; NULL != *rnode_h; rnode_h++) {
		dump_rnode(*rnode_h);
	}
}
