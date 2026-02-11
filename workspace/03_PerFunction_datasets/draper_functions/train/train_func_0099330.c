prt_real_bits(real, precision, pinteger, pfraction)
    double      real;
    int		precision;
    int		*pinteger;
    int		*pfraction;
{
    int     i;
    int     integer;
    float   fraction;

    integer = (int)real;
    fraction = (float)(real - integer);
    if (real < (double)integer)
	fraction = -fraction;
    for (i = 0; i < precision; i++)
	fraction *= 10.0;

    *pinteger = integer;
    *pfraction = (int)(fraction + 0.5);
}
