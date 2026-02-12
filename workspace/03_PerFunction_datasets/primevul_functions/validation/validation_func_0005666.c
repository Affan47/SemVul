bool test_r_str_trim(void) {

	const char* one = r_str_trim_head_ro ("  hello  ");
	mu_assert_streq (one, "hello  ", "one");

	char* two = strdup ("  hello  ");
	r_str_trim_head (two);
	mu_assert_streq (two, "hello  ", "two");
	r_str_trim (two);

	mu_assert_streq (two, "hello", "three");
	free (two);
	mu_end;
}
