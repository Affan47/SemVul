generate_noisy_sine(void)
{
	FILE *f;
	FLAC__byte wav[] = {
		'R', 'I', 'F', 'F',  76,   0,   0,   0,
		'W', 'A', 'V', 'E', 'f', 'm', 't', ' ',
		 16,   0,   0,   0,   1,   0,   1,   0,
		0x44,0xAC,  0,   0,0x88,0x58,0x01,   0,
		  2,   0,  16,   0, 'd', 'a', 't', 'a',
		0xa8,   0xba,   0x6,   0
	};
	int32_t randstate = 0x1243456;
	double sample, last_val = 0.0;
	int k;

	if(0 == (f = flac_fopen("noisy-sine.wav", "wb")))
		return false;
	if(fwrite(wav, 1, sizeof (wav), f) < sizeof (wav))
		goto foo;

	for (k = 0 ; k < 5 * 44100 ; k++) {

		randstate = 11117 * randstate + 211231;
		randstate = 11117 * randstate + 211231;
		randstate = 11117 * randstate + 211231;

		sample = randstate / (0x7fffffff * 1.000001);
		sample = 0.2 * sample - 0.9 * last_val;

		last_val = sample;

		sample += sin (2.0 * k * M_PI * 1.0 / 32.0);
		sample *= 0.4;
#if !defined _MSC_VER
		write_little_endian_int16(f, lrintf(sample * 32700.0));
#else
		write_little_endian_int16(f, (FLAC__int16)(sample * 32700.0));
#endif
	};

	fclose(f);

	return true;
foo:
	fclose(f);
	return false;
}
