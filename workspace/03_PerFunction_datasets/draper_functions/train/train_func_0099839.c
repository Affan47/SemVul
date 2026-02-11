gl843_init_regs_for_warmup (Genesys_Device * dev,
			    Genesys_Register_Set * reg,
			    int *channels, int *total_size)
{
  int num_pixels;
  SANE_Status status = SANE_STATUS_GOOD;
  int dpihw;
  int resolution;
  int factor;

  DBGSTART;
  if (dev == NULL || reg == NULL || channels == NULL || total_size == NULL)
    return SANE_STATUS_INVAL;


  *channels=3;
  resolution=600;
  dpihw=sanei_genesys_compute_dpihw(dev, resolution);
  factor=dev->sensor.optical_res/dpihw;
  num_pixels=dev->sensor.sensor_pixels/(factor*2);
  *total_size = num_pixels * 3 * 1;

  memcpy (reg, dev->reg, (GENESYS_GL843_MAX_REGS + 1) * sizeof (Genesys_Register_Set));
  status = gl843_init_scan_regs (dev,
				 reg,
				 resolution,
				 resolution,
				 num_pixels/2,
				 0,
				 num_pixels,
				 1,
				 8,
				 *channels,
                                 SCAN_MODE_COLOR,
				 dev->settings.color_filter,
				 SCAN_FLAG_DISABLE_SHADING |
				 SCAN_FLAG_DISABLE_GAMMA |
				 SCAN_FLAG_SINGLE_LINE |
				 SCAN_FLAG_IGNORE_LINE_DISTANCE);

  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error, "%s: failed to setup scan: %s\n", __FUNCTION__, sane_strstatus (status));
      return status;
    }

  gl843_set_motor_power (reg, SANE_FALSE);
  RIE (gl843_bulk_write_register (dev, reg, GENESYS_GL843_MAX_REGS));

  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}
