u32 parse_senc_param(char *arg_val, u32 opt)
{
	switch (opt) {
	case 0:
		smenc_opts.flags |= GF_SM_ENCODE_RAP_INBAND;
		smenc_opts.rap_freq = atoi(arg_val);
		break;
	case 1:
		smenc_opts.flags &= ~GF_SM_ENCODE_RAP_INBAND;
		smenc_opts.flags |= GF_SM_ENCODE_RAP_SHADOW;
		smenc_opts.rap_freq = atoi(arg_val);
		break;
	case 2:
		smenc_opts.flags &= ~(GF_SM_ENCODE_RAP_INBAND | GF_SM_ENCODE_RAP_SHADOW);
		smenc_opts.rap_freq = atoi(arg_val);
		break;
	case 3:
		smenc_opts.resolution = atoi(arg_val);
		smenc_opts.auto_quant = 1;
		break;
	case 4:
		smenc_opts.resolution = atoi(arg_val);
		smenc_opts.auto_quant = 2;
		break;
	case 5:
		chunk_mode = GF_TRUE;
		input_ctx = arg_val;
	}
	return 0;
}
