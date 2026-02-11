keep_alive(GncGWENGui *gui)
{
    g_return_val_if_fail(gui, FALSE);

    ENTER("gui=%p", gui);


    while (g_main_context_iteration(NULL, FALSE));

    LEAVE("alive=%d", gui->keep_alive);
    return gui->keep_alive;
}
