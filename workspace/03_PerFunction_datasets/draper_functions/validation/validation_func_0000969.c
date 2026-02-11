unquantize_i4r4(long row,
            INT32BIT *input,
            long ntodo,
            double scale,
            double zero,
            int nullcheck,


            INT32BIT tnull,
            float nullval,
            char *nullarray,
            int  *anynull,
            float *output,
            int *status)


{
    long ii;
    int nextrand, iseed;

    if (fits_rand_value == 0)
       if (fits_init_randoms()) return(MEMORY_ALLOCATION);


    iseed = (int) ((row - 1) % N_RANDOM);
    nextrand = (int) (fits_rand_value[iseed] * 500);

    if (nullcheck == 0)
    {
            for (ii = 0; ii < ntodo; ii++)
            {
                output[ii] = (float) (((double) input[ii] - fits_rand_value[nextrand] + 0.5) * scale + zero);

                nextrand++;
		if (nextrand == N_RANDOM) {
                    iseed++;
		    if (iseed == N_RANDOM) iseed = 0;
	            nextrand = (int) (fits_rand_value[iseed] * 500);
                }
            }
    }
    else
    {
            for (ii = 0; ii < ntodo; ii++)
            {
                if (input[ii] == tnull)
                {
                    *anynull = 1;
                    if (nullcheck == 1)
                        output[ii] = nullval;
                    else
                        nullarray[ii] = 1;
                }
                else
                {
                    output[ii] = (float) (((double) input[ii] - fits_rand_value[nextrand] + 0.5) * scale + zero);
                }

                nextrand++;
		if (nextrand == N_RANDOM) {
                    iseed++;
		    if (iseed == N_RANDOM) iseed = 0;
	            nextrand = (int) (fits_rand_value[iseed] * 500);
                }

            }
    }
    return(*status);
}
