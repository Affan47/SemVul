random_rayleigh_pdf (gnm_float x, gnm_float sigma)
{
	if (x < 0)
		return 0;
	else {
		gnm_float u = x / sigma;

		return (u / sigma) * gnm_exp (-u * u / 2.0);
	}
}
