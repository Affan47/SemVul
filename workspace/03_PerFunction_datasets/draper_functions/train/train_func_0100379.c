restart_main_window()
{
	LOG(LOG_DEBUG, "IN : restart_main_window()");


	calculate_font_size();
	create_text_buffer();

	gtk_text_view_set_buffer(GTK_TEXT_VIEW(main_view), text_buffer);

#if 0

	gdk_window_get_root_origin(main_window->window, &window_x, &window_y);
	window_width = main_window->allocation.width;
	window_height = main_window->allocation.height;

	tree_width = note_tree->allocation.width;
	tree_height = note_tree->allocation.height;


	gtk_widget_destroy(note_tree);
	gtk_widget_destroy(main_window);

	create_main_window();
#endif

	if(current_result != NULL){
		show_result_tree();
		show_result(current_result, FALSE, TRUE);
	} else {

	}

	show_multi();

	LOG(LOG_DEBUG, "OUT: restart_main_window()");
}
