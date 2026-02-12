static inline void clear_bss_descriptor(struct bss_descriptor *bss)
{

	memset(bss, 0, offsetof(struct bss_descriptor, list));
}
