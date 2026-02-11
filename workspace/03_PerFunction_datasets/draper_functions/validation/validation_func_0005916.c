ranf(struct value *init)
{
    long k, z;
    static int firsttime = 1;
    static long seed1, seed2;
    static const long Xm1 = 2147483563L;
    static const long Xm2 = 2147483399L;
    static const long Xa1 = 40014L;
    static const long Xa2 = 40692L;


    if (real(init) != 0.0 || imag(init) != 0.0) {


	long seed1cvrt = real(init);
	long seed2cvrt = imag(init);
	if ( real(init) != (double)seed1cvrt ||
	     imag(init) != (double)seed2cvrt ||
	     seed1cvrt > 017777777777L ||
	     seed2cvrt > 017777777777L ||
	     (seed1cvrt <= 0 && seed2cvrt != 0) ||
	     seed2cvrt < 0 )
	    int_error(NO_CARET,"Illegal seed value");
	else if (seed1cvrt < 0)
	    firsttime = 1;
	else {
	    seed1 = seed1cvrt;
	    seed2 = (seed2cvrt) ? seed2cvrt : seed1cvrt;
	    firsttime = 0;
	}
    }


    if (firsttime) {
	firsttime = 0;
	seed1 = 1234567890L;
	seed2 = 1234567890L;
    }

    FPRINTF((stderr,"ranf: seed = %lo %lo        %ld %ld\n", seed1, seed2));


    k = seed1 / 53668L;
    seed1 = Xa1 * (seed1 - k * 53668L) - k * 12211;
    if (seed1 < 0)
	seed1 += Xm1;
    k = seed2 / 52774L;
    seed2 = Xa2 * (seed2 - k * 52774L) - k * 3791;
    if (seed2 < 0)
	seed2 += Xm2;
    z = seed1 - seed2;
    if (z < 1)
	z += (Xm1 - 1);


    return (double) 4.656613057E-10 *z;
}
