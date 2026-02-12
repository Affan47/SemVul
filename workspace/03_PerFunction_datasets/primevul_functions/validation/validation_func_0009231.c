static bool signed_add32_overflows(s64 a, s64 b)
{

	s32 res = (s32)((u32)a + (u32)b);

	if (b < 0)
		return res > a;
	return res < a;
}
