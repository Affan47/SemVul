peak_usb_get_ts_tv(struct peak_time_ref *time_ref, u32 ts,
			struct timeval *tv)
{

	if (time_ref->tv_host.tv_sec > 0) {
		u64 delta_us;

		delta_us = ts - time_ref->ts_dev_2;
		if (ts < time_ref->ts_dev_2)
			delta_us &= (1 << time_ref->adapter->ts_used_bits) - 1;

		delta_us += time_ref->ts_total;

		delta_us *= time_ref->adapter->us_per_ts_scale;
		delta_us >>= time_ref->adapter->us_per_ts_shift;

		*tv = time_ref->tv_host_0;
		peak_usb_add_us(tv, (u32)delta_us);
	} else {
		*tv = ktime_to_timeval(ktime_get());
	}
}
