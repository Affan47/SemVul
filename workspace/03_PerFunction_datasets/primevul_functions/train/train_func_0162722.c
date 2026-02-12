static void sun4i_get_pll1_factors(struct factors_request *req)
{
	u8 div;


	div = req->rate / 6000000;
	req->rate = 6000000 * div;


	req->m = 0;


	if (req->rate >= 768000000 || req->rate == 42000000 ||
			req->rate == 54000000)
		req->k = 1;
	else
		req->k = 0;


	if (div < 10)
		req->p = 3;


	else if (div < 20 || (div < 32 && (div & 1)))
		req->p = 2;


	else if (div < 40 || (div < 64 && (div & 2)))
		req->p = 1;


	else
		req->p = 0;


	div <<= req->p;
	div /= (req->k + 1);
	req->n = div / 4;
}
