z_store (void)
{
    zword value = zargs[1];

    if (zargs[0] == 0)
	*sp = value;
    else if (zargs[0] < 16)
	*(fp - zargs[0]) = value;
    else {
	zword addr = h_globals + 2 * (zargs[0] - 16);
	SET_WORD (addr, value)
    }

}
