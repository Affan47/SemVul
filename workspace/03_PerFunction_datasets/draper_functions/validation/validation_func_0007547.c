fill_inverse_linear_polynomials(comedi_calibration_t *calibration)
{
	unsigned i;
	for(i = 0; i < calibration->num_settings; ++i)
	{
		if(calibration->settings[i].soft_calibration.to_phys)
		{
			if(calibration->settings[i].soft_calibration.from_phys == NULL)
			{
				calibration->settings[i].soft_calibration.from_phys =
					alloc_inverse_linear_polynomial(calibration->settings[i].soft_calibration.to_phys);
			}
		}else if(calibration->settings[i].soft_calibration.from_phys)
		{
			calibration->settings[i].soft_calibration.to_phys =
				alloc_inverse_linear_polynomial(calibration->settings[i].soft_calibration.from_phys);
		}
	}
}
