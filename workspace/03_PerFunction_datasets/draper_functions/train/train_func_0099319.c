main(int argc, char* argv[])
{
    int c;

    appName = argv[0];
    while ((c = Sys::getopt(argc, argv, "r:l:w:U123")) != -1)
	switch (c) {
	case '1':
	    dataFormat &= ~GROUP3OPT_2DENCODING;
	    break;
	case '2':
	    dataFormat |= GROUP3OPT_2DENCODING;
	    break;
	case '3':
	    useMMR = 1;
	    break;
	case 'U':
	    useUnlimitedLength = true;
	    break;
	case 'l':
	    pageLength = (uint32) strtoul(optarg, NULL, 0);
	    break;
	case 'r':
	    vres = strtoul(optarg, NULL, 0);
	    break;
	case 'w':
	    pageWidth = (uint32) strtoul(optarg, NULL, 0);
	    break;
	case '?':
	    usage();

	}
    if (argc - optind != 1)
	usage();
    int status;
    fxStr emsg;
    TIFF* tif = TIFFOpen(argv[optind], "r");


    TIFFSetWarningHandler(NULL);

    if (tif) {
	status = OK;
	do {
	    status |= checkPageFormat(tif, emsg);
	} while ((status & REJECT) == 0 && TIFFReadDirectory(tif));
	TIFFClose(tif);
    } else {
	struct stat sb;
	if (Sys::stat(argv[optind], sb) < 0)
	    emsg = _("Document file is unreadable or does not exist");
	else
	    emsg = _("Document is not valid TIFF (unspecified format error)");
	status = REJECT;
    }
    if (status != OK) {
	const char* sep = "";
	if (status & REJECT)
	    printf("%sREJECT", sep), sep = "+";
	if (status & REFORMAT)
	    printf("%sREFORMAT", sep), sep = "+";
	if (status & RESIZE)
	    printf("%sRESIZE", sep), sep = "+";
	if (status & REVRES)
	    printf("%sREVRES", sep), sep = "+";
	if (status & REIMAGE)
	    printf("%sREIMAGE", sep), sep = "+";
	printf("\n%s", (const char*) emsg);
    } else
	printf("OK\n");
    return (0);
}
