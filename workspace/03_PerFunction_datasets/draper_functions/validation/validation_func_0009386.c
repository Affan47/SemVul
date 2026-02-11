keccak_init(sph_keccak_context *kc, unsigned out_size)
{
	int i;

#if SPH_KECCAK_64
	for (i = 0; i < 25; i ++)
		kc->u.wide[i] = 0;


	kc->u.wide[ 1] = SPH_C64(0xFFFFFFFFFFFFFFFF);
	kc->u.wide[ 2] = SPH_C64(0xFFFFFFFFFFFFFFFF);
	kc->u.wide[ 8] = SPH_C64(0xFFFFFFFFFFFFFFFF);
	kc->u.wide[12] = SPH_C64(0xFFFFFFFFFFFFFFFF);
	kc->u.wide[17] = SPH_C64(0xFFFFFFFFFFFFFFFF);
	kc->u.wide[20] = SPH_C64(0xFFFFFFFFFFFFFFFF);
#else

	for (i = 0; i < 50; i ++)
		kc->u.narrow[i] = 0;


	kc->u.narrow[ 2] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[ 3] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[ 4] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[ 5] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[16] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[17] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[24] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[25] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[34] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[35] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[40] = SPH_C32(0xFFFFFFFF);
	kc->u.narrow[41] = SPH_C32(0xFFFFFFFF);
#endif
	kc->ptr = 0;
	kc->lim = 200 - (out_size >> 2);
}
