test_core_zstream__big_data(void)
{
	git_buf in = GIT_BUF_INIT;
	size_t scan, target;

	for (target = 1024; target <= 1024 * 1024 * 4; target *= 8) {


		git_buf_clear(&in);
		while (in.size < target)
			cl_git_pass(
				git_buf_put(&in, BIG_STRING_PART, strlen(BIG_STRING_PART)));

		compress_input_various_ways(&in);


		srand(0xabad1dea);
		for (scan = 0; scan < in.size; ++scan)
			in.ptr[scan] = (char)rand();

		compress_input_various_ways(&in);
	}

	git_buf_free(&in);
}
