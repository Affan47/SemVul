attach_label (GtkGrid *grid,
	      GtkWidget *sibling,
	      const char *initial_text,
	      gboolean right_aligned,
	      gboolean bold,
	      gboolean ellipsize_text,
	      gboolean selectable,
	      gboolean mnemonic)
{
	GtkWidget *label_field;

	if (ellipsize_text) {
		label_field = gtk_label_new (initial_text);
                gtk_label_set_ellipsize (GTK_LABEL (label_field),
                                         right_aligned ? PANGO_ELLIPSIZE_START :
                                                         PANGO_ELLIPSIZE_END);
	} else if (mnemonic) {
		label_field = gtk_label_new_with_mnemonic (initial_text);
	} else {
		label_field = gtk_label_new (initial_text);
	}

	if (selectable) {
		gtk_label_set_selectable (GTK_LABEL (label_field), TRUE);
	}

	if (bold) {
		eel_gtk_label_make_bold (GTK_LABEL (label_field));
	}
	gtk_misc_set_alignment (GTK_MISC (label_field), right_aligned ? 1 : 0, 0.5);
	gtk_widget_show (label_field);

	if (ellipsize_text) {
		gtk_widget_set_hexpand (label_field, TRUE);
	}

	if (sibling != NULL) {
		gtk_grid_attach_next_to (grid, label_field, sibling,
					 GTK_POS_RIGHT, 1, 1);
	} else {
		gtk_container_add (GTK_CONTAINER (grid), label_field);
	}

	return GTK_LABEL (label_field);
}
