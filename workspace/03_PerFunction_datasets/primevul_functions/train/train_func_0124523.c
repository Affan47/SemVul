TORRENT_TEST(string_prefix1)
{

	std::string test;
	test.resize(1000000 + 8);
	memcpy(&test[0], "1000000:", 8);

	bdecode_node e;
	error_code ec;
	int ret = bdecode(test.c_str(), test.c_str() + test.size(), e, ec);
	TEST_CHECK(ret == 0);
	printf("%d bytes string\n", e.string_length());
	std::pair<const char*, int> section = e.data_section();
	TEST_CHECK(std::memcmp(test.c_str(), section.first, section.second) == 0);
	TEST_EQUAL(section.second, int(test.size()));
	TEST_EQUAL(e.type(), bdecode_node::string_t);
	TEST_EQUAL(e.string_length(), 1000000);
	TEST_EQUAL(e.string_ptr(), test.c_str() + 8);
}
