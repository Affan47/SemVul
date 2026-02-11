my_atoi(int32_t val, uint8_t **out_str)
{

	int sign = val < 0? 1: 0;
    uint8_t i = 0;


    if (val == 0)
    {
        *(*out_str + i++) = '0';
    }
    else if (val < 0)
    {
        *(*out_str + i++) = '-';
        val = -val;
    }
	while (val > 0) {
    	*(*out_str + i++) = '0' + val % 10;
    	val /= 10;
	}


	reverse(*out_str + sign, i - sign);
    *out_str = (*out_str + i);
    return i;
}
