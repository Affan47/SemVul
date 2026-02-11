main(int argc, char **argv)
{
char opt_errors_encountered=0;
char *vname=NULL;
int c;

WAVE_LOCALE_FIX

while (1)
        {
#ifdef __linux__
        int option_index = 0;

        static struct option long_options[] =
                {
		{"filename", 1, 0, 'f'},
                {"help", 0, 0, 'h'},
                {0, 0, 0, 0}
                };

        c = getopt_long (argc, argv, "f:h", long_options, &option_index);
#else
        c = getopt      (argc, argv, "f:h");
#endif

        if (c == -1) break;

        switch (c)
                {
		case 'f':
			if(vname) free(vname);
                        vname = malloc(strlen(optarg)+1);
                        strcpy(vname, optarg);
			break;

                case 'h':
			print_help(argv[0]);
                        break;

                case '?':
                        opt_errors_encountered=1;
                        break;

                default:

                        break;
                }
        }

if(opt_errors_encountered)
        {
        print_help(argv[0]);
        }

if (optind < argc)
        {
        while (optind < argc)
                {
                if(!vname)
                        {
                        vname = malloc(strlen(argv[optind])+1);
                        strcpy(vname, argv[optind++]);
                        }
			else
			{
			break;
			}
                }
        }

if(!vname)
        {
        print_help(argv[0]);
        }

evcd_main(vname);

free(vname);

return(0);
}
