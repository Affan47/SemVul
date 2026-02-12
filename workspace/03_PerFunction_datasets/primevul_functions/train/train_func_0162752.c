static void sun6i_ahb1_recalc(struct factors_request *req)
{
	req->rate = req->parent_rate;


	if (req->parent_index == SUN6I_AHB1_PARENT_PLL6)
		req->rate /= req->m + 1;


	req->rate >>= req->p;
}
