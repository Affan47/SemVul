ausb11_extend(ausb_dev_handle *ah){
  int rv;
  libusb_device *dev;
  ausb11_extra *xh;

  xh=malloc(sizeof *xh);
  if (xh==0) {
    DEBUGP(ah, "memory full\n");
    return -1;
  }
  memset(xh, 0, sizeof(*xh));


  dev=ausb_libusb1_get_usbdev(&(ah->device));
  if (dev==NULL) {
    DEBUGP(ah, "libusb device not found");
    free(xh);
    return -1;
  }


  rv=libusb_open(dev, &(xh->uh));
  if (rv || !xh->uh) {
    DEBUGP(ah, "libusb_open() failed: rv\n");
    free(xh);
    return -1;
  }


  ah->extraData=xh;
  ah->closeFn=ausb11_close;
  ah->startInterruptFn=ausb11_start_interrupt;
  ah->stopInterruptFn=ausb11_stop_interrupt;
  ah->bulkWriteFn=ausb11_bulk_write;
  ah->bulkReadFn=ausb11_bulk_read;

  ah->claimInterfaceFn=ausb11_claim_interface;
  ah->releaseInterfaceFn=ausb11_release_interface;
  ah->setConfigurationFn=ausb11_set_configuration;

  ah->resetFn=ausb11_reset;
  ah->resetEndpointFn=ausb11_reset_endpoint;
  ah->clearHaltFn=ausb11_clear_halt;
  ah->resetPipeFn=ausb11_reset_pipe;

  ah->getKernelDriverNameFn=ausb11_get_kernel_driver_name;
  ah->detachKernelDriverFn=ausb11_detach_kernel_driver;
  ah->reattachKernelDriverFn=ausb11_reattach_kernel_driver;

  return 0;
}
