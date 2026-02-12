DEFINE_TEST(test_read_format_rar5_different_winsize_on_merge)
{
	char buf[4096];
	PROLOGUE("test_read_format_rar5_different_winsize_on_merge.rar");


	(void) archive_read_next_header(a, &ae);
	while(0 < archive_read_data(a, buf, sizeof(buf))) {}

	EPILOGUE();
}
