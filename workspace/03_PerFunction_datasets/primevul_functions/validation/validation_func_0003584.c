DEFINE_TEST(test_read_format_rar5_leftshift2)
{
	uint8_t buf[16];

	PROLOGUE("test_read_format_rar5_leftshift2.rar");


	(void) archive_read_next_header(a, &ae);
	(void) archive_read_data(a, buf, sizeof(buf));
	(void) archive_read_next_header(a, &ae);

	EPILOGUE();
}
