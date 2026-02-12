uint32_t lrad_rand(void)
{
	uint32_t num;


	if (lrad_rand_index < 0) {
		lrad_rand_seed(NULL, 0);
	}


	num = lrad_rand_pool.randrsl[lrad_rand_index & 0xff];
	lrad_rand_index++;
	lrad_rand_index &= 0xff;


	if (((int) (num & 0xff)) == lrad_rand_index) {
		lrad_isaac(&lrad_rand_pool);
	}

	return num;
}
