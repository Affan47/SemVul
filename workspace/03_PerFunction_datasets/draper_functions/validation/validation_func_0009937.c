check_valid(u32 addr, u32 size)
{
	u32 t1, t2;

	if(size > MMU.MMU_MASK[1][(addr >> 20) & 0xff]) return 0;

	t1 = addr;
	t2 = (addr + size);
	t1 &= MMU.MMU_MASK[1][(addr >> 20) & 0xff];
	t2 &= MMU.MMU_MASK[1][(addr >> 20) & 0xff];

	if(t2 < t1) return 0;

	return 1;
}
