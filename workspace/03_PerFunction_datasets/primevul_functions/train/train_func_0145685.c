static inline long do_strnlen_user(const char __user *src, unsigned long count, unsigned long max)
{
	const struct word_at_a_time constants = WORD_AT_A_TIME_CONSTANTS;
	long align, res = 0;
	unsigned long c;


	if (max > count)
		max = count;


	align = (sizeof(long) - 1) & (unsigned long)src;
	src -= align;
	max += align;

	unsafe_get_user(c, (unsigned long __user *)src, efault);
	c |= aligned_byte_mask(align);

	for (;;) {
		unsigned long data;
		if (has_zero(c, &data, &constants)) {
			data = prep_zero_mask(c, data, &constants);
			data = create_zero_mask(data);
			return res + find_zero(data) + 1 - align;
		}
		res += sizeof(unsigned long);

		if (unlikely(max <= sizeof(unsigned long)))
			break;
		max -= sizeof(unsigned long);
		unsafe_get_user(c, (unsigned long __user *)(src+res), efault);
	}
	res -= align;


	if (res >= count)
		return count+1;


efault:
	return 0;
}
