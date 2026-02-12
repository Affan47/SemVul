static void sun5i_a13_get_ahb_factors(struct factors_request *req)
{
	u32 div;


	if (req->parent_rate < req->rate)
		req->rate = req->parent_rate;


	if (req->rate < 8000)
		req->rate = 8000;
	if (req->rate > 300000000)
		req->rate = 300000000;

	div = order_base_2(DIV_ROUND_UP(req->parent_rate, req->rate));


	if (div > 3)
		div = 3;

	req->rate = req->parent_rate >> div;

	req->p = div;
}
