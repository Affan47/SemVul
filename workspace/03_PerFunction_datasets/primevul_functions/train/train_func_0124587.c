TORRENT_TEST(int_overflow)
{
	char b[] = "i18446744073709551615e";
	bdecode_node e;
	error_code ec;
	int ret = bdecode(b, b + sizeof(b)-1, e, ec);
	TEST_EQUAL(ret, 0);
	printf("%s\n", print_entry(e).c_str());


	TEST_EQUAL(e.int_value(), 0);
}
