main(int argc, char **argv) {
    string rc_filename;
    set<string> style_filenames;
    int i = 1;
    bool check = 0;
    pid_t fb_pid = 0;

    FbTk::NLSInit("fluxbox.cat");
    _FB_USES_NLS;

    for (; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-rc") {


            if ((++i) >= argc) {
                cerr<<_FB_CONSOLETEXT(main, RCRequiresArg,
                              "error: '-rc' requires an argument", "the -rc option requires a file argument")<<endl;
                exit(1);
            }

            rc_filename = argv[i];
        } else if (arg == "-pid") {
            if ((++i) >= argc) {

                cerr<<"the -pid option requires a numeric argument"<<endl;
            } else
                fb_pid = atoi(argv[i]);
        } else if (arg == "-check") {
            check = true;
        } else if (arg == "-help" || arg == "-h") {

            cout << "  -rc <string>\t\t\tuse alternate resource file.\n"
                 << "  -pid <int>\t\t\ttell fluxbox to reload configuration.\n"
                 << "  -check\t\t\tcheck version of this tool and the fluxbox config.\n"
                 << "  -help\t\t\t\tdisplay this help text and exit.\n\n"
                 << endl;
            exit(0);
        }
    }

    if (rc_filename.empty())
        rc_filename = FbTk::StringUtil::expandFilename("~/.fluxbox/init");

    FbTk::ResourceManager resource_manager(rc_filename.c_str(),false);
    if (!resource_manager.load(rc_filename.c_str())) {

        cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFile, "Failed to load database", "Failed trying to read rc file")<<":"<<rc_filename<<endl;
        cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFileTrying, "Retrying with", "Retrying rc file loading with (the following file)")<<": "<<DEFAULT_INITFILE<<endl;


        if (!resource_manager.load(DEFAULT_INITFILE)) {
            cerr<<_FB_CONSOLETEXT(Fluxbox, CantLoadRCFile, "Failed to load database", "")<<": "<<DEFAULT_INITFILE<<endl;
            exit(1);
        }
    }


    FbTk::Resource<int> config_version(resource_manager, 0,
            "session.configVersion", "Session.ConfigVersion");

    if (check) {
        cout << rc_filename << ": " << *config_version << endl
            << "fluxbox-update_configs: " << UPDATES[sizeof(UPDATES)/sizeof(Update) - 1].version << endl;
        exit(0);
    }


    int old_version = *config_version;
    int new_version = run_updates(old_version, resource_manager);
    if (new_version > old_version) {

        config_version = new_version;
        resource_manager.save(rc_filename.c_str(), rc_filename.c_str());
        save_all_files();

#if defined(HAVE_SIGNAL_H) && !defined(_WIN32)

        if (fb_pid > 0)
            kill(fb_pid, SIGUSR2);
#endif

    }

    return 0;
}
