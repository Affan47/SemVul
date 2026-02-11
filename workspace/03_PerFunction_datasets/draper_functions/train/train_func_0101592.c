Blowfish_Decrypt(BLOWFISH_CTX *ctx, uint32_t *xl, uint32_t *xr){
	uint32_t  Xl;
	uint32_t  Xr;
	uint32_t  temp;
	int       i;

	Xl = *xl;
	Xr = *xr;

#ifdef TRACE
	printf("Dec 1: Xl = %08lX\tXr = %08lX\n", Xl, Xr);
#endif

	for (i = N + 1; i > 1; --i)
	{
		Xl = Xl ^ ctx->P[i];
		Xr = F(ctx, Xl) ^ Xr;


		temp = Xl;
		Xl = Xr;
		Xr = temp;

#ifdef TRACE
		printf("Dec 2: Xl = %08lX\tXr = %08lX\n", Xl, Xr);
#endif
	}


	temp = Xl;
	Xl = Xr;
	Xr = temp;

#ifdef TRACE
	printf("Dec 3: Xl = %08lX\tXr = %08lX\n", Xl, Xr);
#endif

	Xr = Xr ^ ctx->P[1];
	Xl = Xl ^ ctx->P[0];

	*xl = Xl;
	*xr = Xr;

#ifdef TRACE
	printf("Dec 4: *xl = %08lX\t*xr = %08lX\n", *xl, *xr);
#endif


	Xl = 0;
	Xr = 0;
	temp = 0;
	i = 0;
}
