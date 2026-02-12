static bool signed_add32_overflows(s32 a, s32 b)
{

	s32 res = (s32)((u32)a + (u32)b);

	if (b < 0)
		return res > a;
	return res < a;
}
