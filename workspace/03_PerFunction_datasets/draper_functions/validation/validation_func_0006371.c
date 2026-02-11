next_rand_32 (guint32 num)
{
	int i;
	guint32 ret;
	guint8 *p = (guint8 *)&ret;

	for (i = 0; i < 4; i++)  {
		num = next_rand_15 (num);
		p[i] = (num & 0xff00) >> 8;
	}
	return ret;
}
