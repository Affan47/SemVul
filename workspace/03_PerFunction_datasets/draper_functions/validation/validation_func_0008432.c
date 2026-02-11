fnet_enum(struct fpga_model* model, net_idx_t last, net_idx_t* next)
{
	int i;

	RC_CHECK(model);

	for (i = last+1; i <= model->highest_used_net; i++) {
		if (model->nets[i-1].len) {
			*next = i;
			return 0;
		}
	}
	*next = NO_NET;
	return 0;
}
