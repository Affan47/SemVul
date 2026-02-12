static BOOL update_read_synchronize(rdpUpdate* update, wStream* s)
{
	WINPR_UNUSED(update);
	return Stream_SafeSeek(s, 2);


}
