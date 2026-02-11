inputisterminal(void)
{
	return ((depth <= 0) || ((cip->i_str == NULL) && (cip->i_fp == NULL)));
}
