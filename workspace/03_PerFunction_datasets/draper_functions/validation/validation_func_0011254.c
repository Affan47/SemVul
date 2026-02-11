z_check_unicode (void)
{
    zword c = zargs[0];
    zword result = 0;

    if (c <= 0x1f)
    {
	if ((c == 0x08) || (c == 0x0d) || (c == 0x1b))
	    result = 2;
    }
    else if (c <= 0x7e)
	result = 3;
    else
	result = 1;

    store (result);

}
