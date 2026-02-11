main(int argc, char *argv[])
{
    int32       infile, aid, ret;
    char       *filename;
    char        datafilename[DF_MAXFNLEN];

    uint16      tag;
    uint16      ref;
    int32       offset, fileoffset;
    int32       length;
    int16       special;


    progname = *argv++;
    argc--;


    while (argc > 0 && **argv == '-')
      {
          switch ((*argv)[1])
            {
                case 'd':
                    argc--;
                    argv++;
                    if (argc > 0)
                      {
                          strcpy(datafilename, *argv++);
                          argc--;
                      }
                    else
                      {
                          usage();
                          exit(1);
                      }
                    break;
                default:
                    usage();
                    exit(1);
            }
      }

    if (argc == 1)
      {
          filename = *argv++;
          argc--;
      }
    else
      {
          usage();
          exit(1);
      }

    if (datafilename[0] == '\0')
        strcpy(datafilename, DefaultDatafile);


    ret = (int) Hishdf(filename);
    if (ret == FALSE)
      {
          error("given file is not an HDF file\n");
      }


    {
        struct stat buf;
        if (stat(datafilename, &buf) == 0)
          {
              printf("External file %s already exists.  Using append mode.\n", datafilename);
              fileoffset = (int32)buf.st_size;
          }
        else
            fileoffset = 0;
    }


    infile = Hopen(filename, DFACC_RDWR, 0);
    if (infile == FAIL)
      {
          error("Can't open the HDF file\n");
      }


    ret = aid = Hstartread(infile, DFTAG_SD, DFREF_WILDCARD);
    while (ret != FAIL)
      {


          ret = Hinquire(aid, NULL, &tag, &ref, &length, &offset, NULL, NULL, &special);


          if (tag == DFTAG_SD)
            {
                printf("moving Scientific Data (%d,%d) to %s\n", tag, ref, datafilename);
                ret = HXcreate(infile, tag, ref, datafilename, fileoffset, length);
                fileoffset += length;
            }


          ret = Hnextread(aid, DFTAG_SD, DFREF_WILDCARD, DF_CURRENT);
      }


    ret = Hendaccess(aid);
    if (ret == FAIL)
        hdferror();


    Hclose(infile);
    return (0);
}
