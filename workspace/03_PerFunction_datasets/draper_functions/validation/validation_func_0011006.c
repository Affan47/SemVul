gui_mch_set_shellsize(int width, int height,
		      int min_width UNUSED,  int min_height UNUSED,
		      int base_width UNUSED, int base_height UNUSED,
		      int direction UNUSED)
{

    gui_mch_update();


    if (gtk_socket_id == 0)
	update_window_manager_hints(0, 0);


    width  += get_menu_tool_width();
    height += get_menu_tool_height();

    if (gtk_socket_id == 0)
	gtk_window_resize(GTK_WINDOW(gui.mainwin), width, height);
    else
	update_window_manager_hints(width, height);

# if 0
    if (!resize_idle_installed)
    {
	g_idle_add_full(GDK_PRIORITY_EVENTS + 10,
			&force_shell_resize_idle, NULL, NULL);
	resize_idle_installed = TRUE;
    }
# endif


    gui_mch_update();
}
