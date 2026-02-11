fdev_print_required_pins(struct fpga_model* model, int y, int x,
	int type, int type_idx)
{
	struct fpga_device* dev;
	int i;

	dev = fdev_p(model, y, x, type, type_idx);
	if (!dev) { HERE(); return; }


	printf("y%i x%i %s %i inpin", y, x, fdev_type2str(type), type_idx);
	if (!dev->pinw_req_in)
		printf(" -\n");
	else {
		for (i = 0; i < dev->pinw_req_in; i++)
			printf(" %s", fdev_pinw_idx2str(type, dev->pinw_req_for_cfg[i]));
		printf("\n");
	}

	printf("y%i x%i %s %i outpin", y, x, fdev_type2str(type), type_idx);
	if (dev->pinw_req_total <= dev->pinw_req_in)
		printf(" -\n");
	else {
		for (i = dev->pinw_req_in; i < dev->pinw_req_total; i++)
			printf(" %s", fdev_pinw_idx2str(type, dev->pinw_req_for_cfg[i]));
		printf("\n");
	}
}
