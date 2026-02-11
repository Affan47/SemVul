savefile_configuration_command(CdlInterpreter interp, int argc, const char* argv[])
{
    CYG_REPORT_FUNCNAMETYPE("CdlConfiguration::savefile_configuration_command", "result %d");
    CYG_PRECONDITION_CLASSC(interp);

    int result = TCL_OK;
    CdlToplevel toplevel = interp->get_toplevel();
    CYG_ASSERT_CLASSC(toplevel);
    CdlConfiguration config = dynamic_cast<CdlConfiguration>(toplevel);
    CYG_ASSERT_CLASSC(config);

    std::vector<CdlInterpreterCommandEntry> subcommands;
    std::vector<CdlInterpreterCommandEntry>* toplevel_commands = 0;

    try {
        std::vector<std::pair<std::string,std::string> > options;
        int data_index = CdlParse::parse_options(interp, "cdl_configuration command", 0, argc, argv, 1, options);


        if (data_index != (argc - 2)) {
            CdlParse::report_error(interp, "", "Invalid cdl_configuration command in savefile, expecting two arguments.");
        } else {
            config->set_name(argv[1]);
            config->get_savefile_subcommands("cdl_configuration", subcommands);
            toplevel_commands = interp->push_commands(subcommands);

            std::string tcl_result;
            result = interp->eval(argv[2], tcl_result);

            interp->pop_commands(toplevel_commands);
            toplevel_commands = 0;
        }

    } catch(...) {
        if (0 != toplevel_commands) {
            interp->pop_commands(toplevel_commands);
        }
        throw;
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
