Radix4First(int *buf, int num)
{
    int r0, r1, r2, r3;
	int r4, r5, r6, r7;

	for (; num != 0; num--)
	{
		r0 = buf[0] + buf[2];
		r1 = buf[1] + buf[3];
		r2 = buf[0] - buf[2];
		r3 = buf[1] - buf[3];
		r4 = buf[4] + buf[6];
		r5 = buf[5] + buf[7];
		r6 = buf[4] - buf[6];
		r7 = buf[5] - buf[7];

		buf[0] = r0 + r4;
		buf[1] = r1 + r5;
		buf[4] = r0 - r4;
		buf[5] = r1 - r5;
		buf[2] = r2 + r7;
		buf[3] = r3 - r6;
		buf[6] = r2 - r7;
		buf[7] = r3 + r6;

		buf += 8;
	}
}
