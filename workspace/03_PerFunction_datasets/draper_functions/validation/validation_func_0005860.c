ausb_libusb1_init(void){
  if (ausb_libusb1_context==NULL) {
    int rv;

    rv=libusb_init(ausb_libusb1_context);
    if (rv) {
      fprintf(stderr, "RSCT: Error on libusb_init(): %d\n", rv);
      ausb_libusb1_context=NULL;
      return -1;
    }
  }

  return 0;
}
