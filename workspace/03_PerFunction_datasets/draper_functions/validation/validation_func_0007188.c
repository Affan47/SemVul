_parse(const char * in, struct uuid &uuid) const
{
    UT_sint32   i;
    const char  *cp;
    char        buf[3];

    UT_return_val_if_fail(in, false);


    if(strlen(in) != 36)
        return false;

    for(i=0, cp = in; i <= 36; i++,cp++)
	{
        if ((i == 8) || (i == 13) || (i == 18) || (i == 23))
		{
            if (*cp == '-')
                continue;
            else
                return false;
        }

        if(i== 36)
            if(*cp == 0)
                continue;

        if(!isxdigit(*cp))
            return false;
    }


    uuid.time_low = strtoul(in, NULL, 16);
    uuid.time_mid = (UT_uint16)strtoul(in+9, NULL, 16);
    uuid.time_high_and_version = (UT_uint16)strtoul(in+14, NULL, 16);
    uuid.clock_seq = (UT_uint16)strtoul(in+19, NULL, 16);

	cp = in+24;
    buf[2] = 0;
    for (i=0; i < 6; i++)
	{
        buf[0] = *cp++;
        buf[1] = *cp++;
        uuid.node[i] = (unsigned char)strtoul(buf, NULL, 16);
    }

	return true;
}
