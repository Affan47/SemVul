static inline void native_tss_invalidate_io_bitmap(void)
{


	this_cpu_write(cpu_tss_rw.x86_tss.io_bitmap_base,
		       IO_BITMAP_OFFSET_INVALID);
}
