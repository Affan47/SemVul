main(int argc,char *argv[]) {
  char *name = NULL;
  char *src,*dest;
  int c,ret;
  int oflag = NXT_OWLINE;

  while ((c = getopt(argc,argv,":hmfn:"))!=-1) {
    switch(c) {
      case 'h':
        usage(argv[0],0);
        break;
      case 'n':
        name = strdup(optarg);
        break;
      case ':':
        fprintf(stderr,"Option -%c requires an operand\n",optopt);
        usage(argv[0],1);
        break;
      case '?':
        fprintf(stderr,"Unrecognized option: -%c\n", optopt);
        usage(argv[0],1);
        break;
    }
  }

  nxt_t *nxt = nxt_open(name);
  if (nxt==NULL) {
    fprintf(stderr,"Could not find NXT\n");
    return 1;
  }

  if (optind<argc) {
    int i;
    src = argv[optind];

    optind++;
    if (optind<argc) dest = argv[optind];
    else dest = basename(src);

    nxt_stop_program(nxt);

    nxt_wait_after_direct_command();

    oflag |= NXT_OWOVER;
    nxt_upload(nxt,src,dest,oflag);

    nxt_wait_extra_long_after_communication_command();

    ret = nxt_error(nxt);
    if (ret == 0)
      if (nxt_run_program(nxt,dest)<0) {
        fprintf(stderr,"Error: %s\n",nxt_strerror(nxt_error(nxt)));
      }
  } else {
    fprintf(stderr,"No input file\n");
    usage(argv[0],1);
  }

  ret = nxt_error(nxt);
  if (name!=NULL) free(name);
  nxt_close(nxt);

  return ret;
}
