more(VMG_ uint argc)
{

    check_argc(vmg_ argc, 0);


    if (G_console->is_reading_script())
        return;


    G_console->flush_all(vmg_ VM_NL_NONE);


    G_console->show_more_prompt(vmg0_);
}
