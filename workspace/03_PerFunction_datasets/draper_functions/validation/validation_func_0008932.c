ANTIC_GetDLByte(UWORD *paddr)
{
	int addr = *paddr;
	UBYTE result;
	if (ANTIC_xe_ptr != NULL && addr < 0x8000 && addr >= 0x4000)
		result = ANTIC_xe_ptr[addr - 0x4000];
	else
		result = MEMORY_GetByte((UWORD) addr);
	addr++;
	if ((addr & 0x3FF) == 0)
		addr -= 0x400;
	*paddr = (UWORD) addr;
	return result;
}
