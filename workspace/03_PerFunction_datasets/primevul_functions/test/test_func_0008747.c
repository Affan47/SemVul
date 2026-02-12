callbacks_change_layer_edit_clicked  (GtkButton *button, gpointer userData)
{
	gint index = callbacks_get_selected_row_index();
	gerbv_fileinfo_t **files = mainProject->file;
	gerbv_user_transformation_t **transforms;
	int i, j;

	if (index < 0) {
		show_no_layers_warning ();
		return;
	}


	transforms = g_new (gerbv_user_transformation_t *,
			mainProject->last_loaded +
			2  +
			1 );


	transforms[0] = &mainProject->file[index]->transform;


	j = 1;
	for (i = 0; i <= mainProject->last_loaded; i++) {
		if (files[i] && files[i]->isVisible)
			transforms[j++] = &files[i]->transform;
	}


	transforms[j] = NULL;

	interface_show_layer_edit_dialog(transforms, screen.unit);
	g_free (transforms);
	render_refresh_rendered_image_on_screen ();
	callbacks_update_layer_tree ();
}
