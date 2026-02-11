main( int argc, char* argv[] )
{

  #ifndef __NO_X
    signal( SIGUSR1, catch_usr1 );
  #endif

  #ifdef __IN2P3
    signal( SIGUSR1, catch_usr1 );
    signal( SIGXCPU, catch_xcpu );
  #endif


  #ifdef DEBUG
    printf( "aevol is being run in DEBUG mode\n" );
  #endif


  bool use_text_files   = false;
  bool pause_on_startup = false;
  bool verbose          = false;

  int32_t num_gener = 0;
  int32_t nb_gener  = 1000;

  #ifndef __NO_X
    bool show_display_on_startup = true;
  #endif


  const char * options_list = "hn:r:tvVwx";
  static struct option long_options_list[] = {
    { "help",     no_argument,        NULL, 'h' },
    { "nbgener",  required_argument,  NULL, 'n' },
    { "resume",   required_argument,  NULL, 'r' },
    { "text",     no_argument,        NULL, 't' },
    { "verbose",  no_argument,        NULL, 'v' },
    { "version",  no_argument,        NULL, 'V' },
    { "wait",     no_argument,        NULL, 'w' },
    { "noX",      no_argument,        NULL, 'x' },
    { 0, 0, 0, 0 }
  };


  int option;
  while ( ( option = getopt_long(argc, argv, options_list, long_options_list, NULL) ) != -1 )
  {
    switch ( option )
    {
      case 'h' :
      {
        print_help( argv[0] );
        exit( EXIT_SUCCESS );
      }
      case 'V' :
      {
        print_version();
        exit( EXIT_SUCCESS );
      }
      case 'n' :
      {
        if ( strcmp( optarg, "" ) == 0 )
        {
          printf( "%s: error: Option -n or --nbgener : missing argument.\n", argv[0] );
          exit( EXIT_FAILURE );
        }

        nb_gener = atoi( optarg );

        break;
      }
      case 'r' :
      {
        if ( strcmp( optarg, "" ) == 0 )
        {
          printf( "%s: error: Option -r or --resume : missing argument.\n", argv[0] );
          exit( EXIT_FAILURE );
        }

        num_gener = atol( optarg );

        break;
      }
      case 't' :
      {
        use_text_files = true;
        printf( "%s: error: Option -t or --text not yet implemented.\n", argv[0] );
        exit( EXIT_FAILURE );

        break;
      }
      case 'v' :
      {
        verbose = true;

        break;
      }
      case 'w' :
      {
        pause_on_startup = true;

        break;
      }
      case 'x' :
      {
        #ifdef __NO_X
          printf( "%s: error: Program was compiled with __NO_X option, no visualisation available.\n", argv[0] );
          exit( EXIT_FAILURE );
        #else
          show_display_on_startup = false;
        #endif

        break;
      }
      default :
      {

        exit( EXIT_FAILURE );
      }
    }
  }


  #ifndef __NO_X
    ae_exp_manager* exp_manager = new ae_exp_manager_X11();
  #else
    ae_exp_manager* exp_manager = new ae_exp_manager();
  #endif

  exp_manager->load( num_gener, false, verbose );
  exp_manager->set_nb_gener( nb_gener );


  #ifndef __NO_X
    if ( show_display_on_startup )
    {
      ((ae_exp_manager_X11*) exp_manager)->toggle_display_on_off();
    }
  #endif


  exp_manager->run_evolution();


  delete exp_manager;

}
