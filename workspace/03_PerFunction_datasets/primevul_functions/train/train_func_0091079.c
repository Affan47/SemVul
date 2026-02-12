static void vp9_quantization_params(GF_BitStream *bs)
{
	gf_bs_read_int_log(bs, 8, "base_q_idx");
	vp9_delta_q(bs);
	vp9_delta_q(bs);
	vp9_delta_q(bs);
}
