static void dec_lock_count (void)
{
	if (lock_count > 0) {
		lock_count--;
		if (lock_count == 0) {


			if (nscd_need_reload) {
				nscd_flush_cache ("passwd");
				nscd_flush_cache ("group");
				nscd_need_reload = false;
			}
#ifdef HAVE_LCKPWDF
			ulckpwdf ();
#endif
		}
	}
}
