profile_activated(struct pyra_device *pyra,
		unsigned int new_profile)
{
	if (new_profile >= ARRAY_SIZE(pyra->profile_settings))
		return;
	pyra->actual_profile = new_profile;
	pyra->actual_cpi = pyra->profile_settings[pyra->actual_profile].y_cpi;
}
