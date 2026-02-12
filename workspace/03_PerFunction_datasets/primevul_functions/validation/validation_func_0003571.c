DEFINE_TEST(test_read_format_rar5_invalid_dict_reference)
{
	uint8_t buf[16];

	PROLOGUE("test_read_format_rar5_invalid_dict_reference.rar");


	assertA(archive_read_next_header(a, &ae) != ARCHIVE_OK);


	assertA(archive_read_data(a, buf, sizeof(buf)) <= 0);


	assertA(ARCHIVE_OK != archive_read_next_header(a, &ae));

	EPILOGUE();
}
