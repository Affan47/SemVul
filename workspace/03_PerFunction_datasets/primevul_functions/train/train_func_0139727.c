parse_switches (j_compress_ptr cinfo, int argc, char **argv,
                int last_file_arg_seen, boolean for_real)


{
  int argn;
  char *arg;
  boolean force_baseline;
  boolean simple_progressive;
  char *qualityarg = NULL;
  char *qtablefile = NULL;
  char *qslotsarg = NULL;
  char *samplearg = NULL;
  char *scansarg = NULL;


  force_baseline = FALSE;
  simple_progressive = FALSE;
  is_targa = FALSE;
  icc_filename = NULL;
  outfilename = NULL;
  memdst = FALSE;
  cinfo->err->trace_level = 0;


  for (argn = 1; argn < argc; argn++) {
    arg = argv[argn];
    if (*arg != '-') {

      if (argn <= last_file_arg_seen) {
        outfilename = NULL;
        continue;
      }
      break;
    }
    arg++;

    if (keymatch(arg, "arithmetic", 1)) {

#ifdef C_ARITH_CODING_SUPPORTED
      cinfo->arith_code = TRUE;
#else
      fprintf(stderr, "%s: sorry, arithmetic coding not supported\n",
              progname);
      exit(EXIT_FAILURE);
#endif

    } else if (keymatch(arg, "baseline", 1)) {

      force_baseline = TRUE;

    } else if (keymatch(arg, "dct", 2)) {

      if (++argn >= argc)
        usage();
      if (keymatch(argv[argn], "int", 1)) {
        cinfo->dct_method = JDCT_ISLOW;
      } else if (keymatch(argv[argn], "fast", 2)) {
        cinfo->dct_method = JDCT_IFAST;
      } else if (keymatch(argv[argn], "float", 2)) {
        cinfo->dct_method = JDCT_FLOAT;
      } else
        usage();

    } else if (keymatch(arg, "debug", 1) || keymatch(arg, "verbose", 1)) {


      static boolean printed_version = FALSE;

      if (! printed_version) {
        fprintf(stderr, "%s version %s (build %s)\n",
                PACKAGE_NAME, VERSION, BUILD);
        fprintf(stderr, "%s\n\n", JCOPYRIGHT);
        fprintf(stderr, "Emulating The Independent JPEG Group's software, version %s\n\n",
                JVERSION);
        printed_version = TRUE;
      }
      cinfo->err->trace_level++;

    } else if (keymatch(arg, "version", 4)) {
      fprintf(stderr, "%s version %s (build %s)\n",
              PACKAGE_NAME, VERSION, BUILD);
      exit(EXIT_SUCCESS);

    } else if (keymatch(arg, "grayscale", 2) || keymatch(arg, "greyscale",2)) {

      jpeg_set_colorspace(cinfo, JCS_GRAYSCALE);

    } else if (keymatch(arg, "rgb", 3)) {

      jpeg_set_colorspace(cinfo, JCS_RGB);

    } else if (keymatch(arg, "icc", 1)) {

      if (++argn >= argc)
        usage();
      icc_filename = argv[argn];

    } else if (keymatch(arg, "maxmemory", 3)) {

      long lval;
      char ch = 'x';

      if (++argn >= argc)
        usage();
      if (sscanf(argv[argn], "%ld%c", &lval, &ch) < 1)
        usage();
      if (ch == 'm' || ch == 'M')
        lval *= 1000L;
      cinfo->mem->max_memory_to_use = lval * 1000L;

    } else if (keymatch(arg, "optimize", 1) || keymatch(arg, "optimise", 1)) {

#ifdef ENTROPY_OPT_SUPPORTED
      cinfo->optimize_coding = TRUE;
#else
      fprintf(stderr, "%s: sorry, entropy optimization was not compiled in\n",
              progname);
      exit(EXIT_FAILURE);
#endif

    } else if (keymatch(arg, "outfile", 4)) {

      if (++argn >= argc)
        usage();
      outfilename = argv[argn];

    } else if (keymatch(arg, "progressive", 1)) {

#ifdef C_PROGRESSIVE_SUPPORTED
      simple_progressive = TRUE;

#else
      fprintf(stderr, "%s: sorry, progressive output was not compiled in\n",
              progname);
      exit(EXIT_FAILURE);
#endif

    } else if (keymatch(arg, "memdst", 2)) {

#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
      memdst = TRUE;
#else
      fprintf(stderr, "%s: sorry, in-memory destination manager was not compiled in\n",
              progname);
      exit(EXIT_FAILURE);
#endif

    } else if (keymatch(arg, "quality", 1)) {

      if (++argn >= argc)
        usage();
      qualityarg = argv[argn];

    } else if (keymatch(arg, "qslots", 2)) {

      if (++argn >= argc)
        usage();
      qslotsarg = argv[argn];


    } else if (keymatch(arg, "qtables", 2)) {

      if (++argn >= argc)
        usage();
      qtablefile = argv[argn];


    } else if (keymatch(arg, "restart", 1)) {

      long lval;
      char ch = 'x';

      if (++argn >= argc)
        usage();
      if (sscanf(argv[argn], "%ld%c", &lval, &ch) < 1)
        usage();
      if (lval < 0 || lval > 65535L)
        usage();
      if (ch == 'b' || ch == 'B') {
        cinfo->restart_interval = (unsigned int) lval;
        cinfo->restart_in_rows = 0;
      } else {
        cinfo->restart_in_rows = (int) lval;

      }

    } else if (keymatch(arg, "sample", 2)) {

      if (++argn >= argc)
        usage();
      samplearg = argv[argn];


    } else if (keymatch(arg, "scans", 4)) {

#ifdef C_MULTISCAN_FILES_SUPPORTED
      if (++argn >= argc)
        usage();
      scansarg = argv[argn];

#else
      fprintf(stderr, "%s: sorry, multi-scan output was not compiled in\n",
              progname);
      exit(EXIT_FAILURE);
#endif

    } else if (keymatch(arg, "smooth", 2)) {

      int val;

      if (++argn >= argc)
        usage();
      if (sscanf(argv[argn], "%d", &val) != 1)
        usage();
      if (val < 0 || val > 100)
        usage();
      cinfo->smoothing_factor = val;

    } else if (keymatch(arg, "targa", 1)) {

      is_targa = TRUE;

    } else {
      usage();
    }
  }


  if (for_real) {


    if (qualityarg != NULL)
      if (! set_quality_ratings(cinfo, qualityarg, force_baseline))
        usage();

    if (qtablefile != NULL)
      if (! read_quant_tables(cinfo, qtablefile, force_baseline))
        usage();

    if (qslotsarg != NULL)
      if (! set_quant_slots(cinfo, qslotsarg))
        usage();

    if (samplearg != NULL)
      if (! set_sample_factors(cinfo, samplearg))
        usage();

#ifdef C_PROGRESSIVE_SUPPORTED
    if (simple_progressive)
      jpeg_simple_progression(cinfo);
#endif

#ifdef C_MULTISCAN_FILES_SUPPORTED
    if (scansarg != NULL)
      if (! read_scan_script(cinfo, scansarg))
        usage();
#endif
  }

  return argn;
}
