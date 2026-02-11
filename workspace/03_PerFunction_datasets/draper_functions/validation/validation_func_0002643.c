gl_template_designer_construct (glTemplateDesigner *dialog)
{
        lglUnits    units;
        gchar      *logo_filename;
	GdkPixbuf  *logo;

	gl_debug (DEBUG_TEMPLATE, "START");

	g_return_if_fail (dialog && GL_IS_TEMPLATE_DESIGNER (dialog));
	g_return_if_fail (dialog->priv != NULL);


        units = gl_prefs_model_get_units (gl_prefs);
	dialog->priv->units_string    = lgl_units_get_name (units);
        dialog->priv->units_per_point = lgl_units_get_units_per_point (units);
        dialog->priv->climb_rate      = gl_units_util_get_step_size (units);
        dialog->priv->digits          = gl_units_util_get_precision (units);

	gtk_window_set_title (GTK_WINDOW(dialog), _("New gLabels Template"));

        logo_filename = g_build_filename (GLABELS_DATA_DIR, "pixmaps", "template-designer.png", NULL);
	logo = gdk_pixbuf_new_from_file (logo_filename, NULL);
        g_free (logo_filename);


	construct_start_page (dialog, logo);
	construct_name_page (dialog, logo);
	construct_pg_size_page (dialog, logo);
	construct_shape_page (dialog, logo);
	construct_rect_size_page (dialog, logo);
	construct_ellipse_size_page (dialog, logo);
	construct_round_size_page (dialog, logo);
	construct_cd_size_page (dialog, logo);
	construct_nlayouts_page (dialog, logo);
	construct_layout_page (dialog, logo);
	construct_finish_page (dialog, logo);

        gtk_assistant_set_forward_page_func (GTK_ASSISTANT (dialog),
                                             forward_page_function,
                                             dialog,
                                             NULL);


	g_signal_connect_swapped (G_OBJECT(dialog), "cancel",
				  G_CALLBACK(cancel_cb), dialog);
	g_signal_connect_swapped (G_OBJECT(dialog), "apply",
				  G_CALLBACK(apply_cb), dialog);
	g_signal_connect_swapped (G_OBJECT(dialog), "close",
				  G_CALLBACK(close_cb), dialog);
	g_signal_connect (G_OBJECT(dialog), "prepare",
                          G_CALLBACK(prepare_cb), NULL);

        gtk_widget_show_all (GTK_WIDGET(dialog));

	gl_debug (DEBUG_TEMPLATE, "END");
}
