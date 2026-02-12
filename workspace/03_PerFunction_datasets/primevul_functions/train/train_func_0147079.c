static bool need_debug_guardpage(void)
{

	if (!debug_pagealloc_enabled())
		return false;

	if (!debug_guardpage_minorder())
		return false;

	return true;
}
