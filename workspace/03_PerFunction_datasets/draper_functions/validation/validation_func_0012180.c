kv_get_sleep_divider_id_from_clock(struct amdgpu_device *adev,
					     u32 sclk, u32 min_sclk_in_sr)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 i;
	u32 temp;
	u32 min = (min_sclk_in_sr > KV_MINIMUM_ENGINE_CLOCK) ?
		min_sclk_in_sr : KV_MINIMUM_ENGINE_CLOCK;

	if (sclk < min)
		return 0;

	if (!pi->caps_sclk_ds)
		return 0;

	for (i = KV_MAX_DEEPSLEEP_DIVIDER_ID; i > 0; i--) {
		temp = sclk / sumo_get_sleep_divider_from_id(i);
		if (temp >= min)
			break;
	}

	return (u8)i;
}
