z_intcuberoot(unsigned long n)
{
    unsigned long newg, g;
    unsigned long oldg = n;

    if (n < 8)
    {
       if (n == 0) return 0;
       return 1;
    }

	g = (unsigned long) ceil(pow(n, 0.333333333));

    do
	{
		newg = 2L*g + n/(g*g);
		newg = newg/3L;

        if (g == newg || newg == oldg) break;

        oldg = g;
		g = newg;
	} while (1);

    if (newg*newg*newg > n) return newg - 1;
    else return newg;
}
