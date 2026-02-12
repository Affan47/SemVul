static int olaps_cmp(const void *a, const void *b)
{
	struct fastrpc_buf_overlap *pa = (struct fastrpc_buf_overlap *)a;
	struct fastrpc_buf_overlap *pb = (struct fastrpc_buf_overlap *)b;

	int st = CMP(pa->start, pb->start);

	int ed = CMP(pb->end, pa->end);

	return st == 0 ? ed : st;
}
