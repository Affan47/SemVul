static bool check_buffer_count(size_t count)
{
	const size_t sz = eb_element_size();


	return !(count < 1 || count > INT_MAX || count > SIZE_MAX / sz - 1);
}
