int app_main( int argc, char** argv )
{
    g_argc = argc;
    g_argv = (const char **)argv;
    TimingHarness::timing[0][TimingHarness::TS_MAIN]
        = TimingHarness::get_time_us(true);
    size_t thread_mem_limit =
#ifdef HIGH_MEMORY
        64 * 1024 * 1024
#else
        3 * 1024 * 1024
#endif
        ;
    size_t mem_limit =
#ifdef HIGH_MEMORY
        1024 * 1024 * 1024 - thread_mem_limit * (MAX_NUM_THREADS - 1)
#else
        176 * 1024 * 1024 - thread_mem_limit * (MAX_NUM_THREADS - 1)
#endif
        ;
    bool needs_huge_pages = false;
    for (int i = 1; i < argc; ++i) {
        bool avx2upgrade = false;
        compute_thread_mem(argv[i],
                           &mem_limit,
                           &thread_mem_limit,
                           &needs_huge_pages,
                           &avx2upgrade);
#ifndef __AVX2__
#ifndef __clang__
#ifndef _ARCH_PPC
#ifndef _WIN32
        if (avx2upgrade &&
            __builtin_cpu_supports("avx2")
) {
            for (int j = i + 1; j < argc; ++j) {
                argv[j - 1] = argv[j];
            }
            --argc;
            argv[argc] = NULL;
            size_t command_len = strlen(argv[0]);
            size_t postfix_len = strlen("-avx") + 1;
            char * command = (char*)malloc(postfix_len + command_len);
            memcpy(command, argv[0], command_len);
            memcpy(command + command_len, "-avx", postfix_len);
            char * old_command = argv[0];
            argv[0] = command;
            execvp(command, argv);
            argv[0] = old_command;
        }
#endif
#endif
#endif
#endif
    }


    UncompressedComponents::max_number_of_blocks = ( mem_limit / 4 ) * 3;
    if (mem_limit > 48 * 1024 * 1024) {
        UncompressedComponents::max_number_of_blocks = mem_limit - 36 * 1024 * 1024;
    }
    UncompressedComponents::max_number_of_blocks /= (sizeof(uint16_t) * 64);
    int n_threads = MAX_NUM_THREADS;
#ifndef __linux__
    n_threads += 4;
#endif
#if !defined(_WIN32) && !defined(EMSCRIPTEN)
    Sirikata::memmgr_init(mem_limit,
                          thread_mem_limit,
                          n_threads,
                          256,
                          needs_huge_pages);
#endif
    clock_t begin = 0, end = 1;

    int error_cnt = 0;
    int warn_cnt  = 0;

    int acc_jpgsize = 0;
    int acc_ujgsize = 0;

    int speed, bpms;
    float cr;

    errorlevel.store(0);


    int max_file_size = initialize_options( argc, argv );
    if (action != forkserve && action != socketserve) {

        fprintf( msgout,  "%s v%i.0-%s\n",
                 appname, ujgversion, GIT_REVISION );
    }

    if ((file_cnt == 0 && action != forkserve && action != socketserve)
        || ((!developer) && ((action != lepton_concatenate && action != comp && action != forkserve && action != socketserve)))) {
        show_help();
        return -1;
    }


    reset_buffers();


    begin = clock();
    if (file_cnt > 2 && action != lepton_concatenate) {
        show_help();
        custom_exit(ExitCode::FILE_NOT_FOUND);
    }
    if (action == forkserve) {
#ifdef _WIN32
        abort();
#else
        fork_serve();
#endif
    } else if (action == socketserve) {
#ifdef _WIN32
        abort();
#else
        socket_serve(&process_file, max_file_size, g_socketserve_info);
#endif
    } else {
        process_file(nullptr, nullptr, max_file_size, g_force_zlib0_out);
    }
    if (errorlevel.load() >= err_tresh) error_cnt++;
    if (errorlevel.load() == 1 ) warn_cnt++;
    if ( errorlevel.load() < err_tresh ) {
        acc_jpgsize += jpgfilesize;
        acc_ujgsize += ujgfilesize;
    }
    if (!g_use_seccomp) {
        end = clock();
    }
    if (action != socketserve && action != forkserve) {

        fprintf(msgout,  "\n\n-> %i file(s) processed, %i error(s), %i warning(s)\n",
                file_cnt, error_cnt, warn_cnt);
    }
    if ( ( file_cnt > error_cnt ) && ( verbosity > 0 ) )
    if ( action == comp ) {
        speed = (int) ( (double) (( end - begin ) * 1000) / CLOCKS_PER_SEC );
        bpms  = ( speed > 0 ) ? ( acc_jpgsize / speed ) : acc_jpgsize;
        cr    = ( acc_jpgsize > 0 ) ? ( 100.0 * acc_ujgsize / acc_jpgsize ) : 0;

        fprintf( msgout,  " --------------------------------- \n" );
        fprintf( msgout,  " time taken        : %8i msec\n", speed );
        fprintf( msgout,  " avrg. byte per ms : %8i byte\n", bpms );
        fprintf( msgout,  " avrg. comp. ratio : %8.2f %%\n", cr );
        fprintf( msgout,  " --------------------------------- \n" );
    }


    return error_cnt == 0 ? 0 : 1;
}
