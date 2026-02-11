LongNumShiftLeftMany(Byte * a, int shifts, int length)
{
	int i = 0;
	NumCarry carryFlag = 0;

	for (i = 0; i < shifts; i++)
		LongNumShiftLeft(a, &carryFlag, length);
}
