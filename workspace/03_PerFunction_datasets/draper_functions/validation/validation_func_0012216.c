dicod_init_command_tab()
{
    struct dicod_command *p;

    for (p = command_tab; p->keyword; p++)
	dicod_add_command(p);
}
