static inline void set_fs(mm_segment_t fs)
{
	current->thread.addr_limit = fs;

	set_thread_flag(TIF_FSCHECK);
}
