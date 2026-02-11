spi_dec_plat_mouse_check (SpiDEController *controller,
		     int *x, int *y, gboolean *moved)
{
  SpiDEControllerClass *klass;
  klass = SPI_DEVICE_EVENT_CONTROLLER_GET_CLASS (controller);
  if (klass->plat.mouse_check)
    return klass->plat.mouse_check (controller, x, y, moved);
  else
    return 0;
}
