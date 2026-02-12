static bool calc_nx_huge_pages_recovery_period(uint *period)
{


	bool enabled = READ_ONCE(nx_huge_pages);
	uint ratio = READ_ONCE(nx_huge_pages_recovery_ratio);

	if (!enabled || !ratio)
		return false;

	*period = READ_ONCE(nx_huge_pages_recovery_period_ms);
	if (!*period) {

		ratio = min(ratio, 3600u);
		*period = 60 * 60 * 1000 / ratio;
	}
	return true;
}
