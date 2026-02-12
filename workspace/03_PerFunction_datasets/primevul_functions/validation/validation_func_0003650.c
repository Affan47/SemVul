DEFINE_TEST(test_read_format_rar5_block_size_is_too_small)
{
	char buf[4096];
	PROLOGUE("test_read_format_rar5_block_size_is_too_small.rar");


	assertA(archive_read_next_header(a, &ae) != ARCHIVE_OK);
	assertA(archive_read_data(a, buf, sizeof(buf)) <= 0);

	EPILOGUE();
}
