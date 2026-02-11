main(int argc, char** argv) {
    DB_RESULT result;
    char clause[256];
    int retval, n, nerr;

    for(int c = 1; c < argc; c++) {
        std::string option(argv[c]);
        if(option == "-h" || option == "--help") {
            usage(argv[0]);
            exit(0);
        } else if(option == "-v" || option == "--version") {
            printf("%s\n", SVN_VERSION);
            exit(0);
        } else if (option == "--repair") {
            repair = true;
        } else {
            fprintf(stderr, "unknown command line argument: %s\n\n", argv[c]);
            usage(argv[0]);
            exit(1);
        }
    }

    retval = config.parse_file();
    if (retval) exit(1);

    retval = boinc_db.open(
        config.db_name, config.db_host, config.db_user, config.db_passwd
    );
    if (retval) {
        printf("boinc_db.open: %s\n", boincerror(retval));
        exit(1);
    }

    n = nerr = 0;
    printf("Unsent results:\n");
    sprintf(clause, "where server_state=%d", RESULT_SERVER_STATE_UNSENT);
    while (!result.enumerate(clause)) {
        retval = handle_result(result);
        n++;
        if (retval) nerr++;
    }
    printf("%d out of %d errors\n", nerr, n);
    n = nerr = 0;
    printf("In progress results:\n");
    sprintf(clause, "where server_state=%d", RESULT_SERVER_STATE_IN_PROGRESS);
    while (!result.enumerate(clause)) {
        retval = handle_result(result);
        n++;
        if (retval) nerr++;
    }
    printf("%d out of %d errors\n", nerr, n);
}
