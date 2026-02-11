pcl3_close_device(gx_device *device)
{
  pcl3_Device *dev = (pcl3_Device *)device;


  if (dev->configured && dev->file != NULL) {
    pcl3_end_file(dev->file, &dev->file_data);
    dev->configured = false;
  }

  return eprn_close_device(device);
}
