remove_handler_in_list(struct host_if_drv *handler)
{
	int i;

	for (i = 1; i < ARRAY_SIZE(wfidrv_list); i++) {
		if (wfidrv_list[i] == handler) {
			wfidrv_list[i] = NULL;
			return 0;
		}
	}

	return -EINVAL;
}
