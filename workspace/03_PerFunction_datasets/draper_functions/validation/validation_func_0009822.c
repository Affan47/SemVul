initialize_savefile_support()
{
    CYG_REPORT_FUNCNAME("CdlToplevel::initialize_savefile_support");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();


    savefile_commands_initialized = true;


    add_savefile_command("cdl_savefile_version", 0, &savefile_handle_version);
    add_savefile_command("cdl_savefile_command", 0, &savefile_handle_command);

    CYG_REPORT_RETURN();
}
