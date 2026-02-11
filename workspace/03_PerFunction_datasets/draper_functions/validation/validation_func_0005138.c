gnome_canvas_unrealize (GtkWidget *widget)
{
	GnomeCanvas *canvas;

	g_return_if_fail (GNOME_IS_CANVAS (widget));

	canvas = GNOME_CANVAS (widget);

	shutdown_transients (canvas);


	(* GNOME_CANVAS_ITEM_GET_CLASS (canvas->root)->unrealize) (canvas->root);

	GTK_WIDGET_CLASS (gnome_canvas_parent_class)->unrealize (widget);
}
