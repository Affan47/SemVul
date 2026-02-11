set_time_window(struct powercap_zone *power_zone, int id,
								u64 window)
{
	struct rapl_domain *rd;
	int ret = 0;

	get_online_cpus();
	rd = power_zone_to_rapl_domain(power_zone);
	switch (rd->rpl[id].prim_id) {
	case PL1_ENABLE:
		rapl_write_data_raw(rd, TIME_WINDOW1, window);
		break;
	case PL2_ENABLE:
		rapl_write_data_raw(rd, TIME_WINDOW2, window);
		break;
	default:
		ret = -EINVAL;
	}
	put_online_cpus();
	return ret;
}
