check_WDC_drive()
{
  static __u8 atabuffer[4+512];
  int i;

  if (verbose) {
    printf("Checking if Drive is a Western Digital Drive\n");
  }

  memset(atabuffer, 0, sizeof(atabuffer));
  atabuffer[0] = ATA_OP_IDENTIFY;
  atabuffer[3] = 1;
  if (do_drive_cmd(fd, atabuffer)) {
    perror(" HDIO_DRIVE_CMD(identify) failed");
    return errno;
  }

  if (!force) {

    if ( (atabuffer[4+(27*2)+1] != 'W')
      || (atabuffer[4+(27*2)] != 'D')
      || (atabuffer[4+(28*2)+1] != 'C')) {
      fprintf(stderr, "The drive %s does not seem to be a Western Digital Drive ",device);
      fprintf(stderr, "but a ");
      for (i=27; i<47; i++) {
        if(atabuffer[4+(i*2)+1]==0)break;
        putchar(atabuffer[4+(i*2)+1]);
        if(atabuffer[4+(i*2)+0]==0)break;
        putchar(atabuffer[4+(i*2)+0]);
      }
      printf("\n");

      fprintf(stderr, "Use the --force option if you know what you're doing\n");
      return 1;
    }
  }

  return 0;
}
