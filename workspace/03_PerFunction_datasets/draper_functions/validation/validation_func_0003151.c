main(int argc,char* argv[]) {

    std::ios_base::sync_with_stdio(false);


    try {
        try_main(argc,argv);

    } catch (const blt_exception& e) {
        log_os << "FATAL_ERROR: EXCEPTION: " << e.what() << "\n"
               << "...caught in main()\n";
        dump_cl(argc,argv,log_os);
        exit(EXIT_FAILURE);
    } catch (const illumina::common::ExceptionData& e) {
        log_os << "FATAL_ERROR: EXCEPTION: "
               << e.getContext() << ": " << e.getMessage() << "\n"
               << "...caught in main()\n";
        dump_cl(argc,argv,log_os);
        exit (EXIT_FAILURE);
    } catch (const std::exception& e) {
        log_os << "FATAL_ERROR: EXCEPTION: " << e.what() << "\n"
               << "...caught in main()\n";
        dump_cl(argc,argv,log_os);
        exit(EXIT_FAILURE);
    } catch (...) {
        log_os << "FATAL_ERROR: UNKNOWN EXCEPTION\n"
               << "...caught in main()\n";
        dump_cl(argc,argv,log_os);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
