outhexdigs(num)
register uoffset_T num;
{
    if (num >= 0x10)
    {
	outhexdigs(num / 0x10);
	num %= 0x10;
    }
    outbyte(hexdigits[(int) num]);
}
