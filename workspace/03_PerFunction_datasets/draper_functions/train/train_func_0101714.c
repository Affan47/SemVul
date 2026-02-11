scale_value_changed (GtkAdjustment *adjustment,
		     gpointer       user_data)
{
	ScaleData *scale_data = user_data;
	double     num;
	char      *value;
	char      *markup;

	num = gtk_adjustment_get_value (adjustment);
	value = g_strdup_printf (scale_data->format, num);
	if ((num == 0.0) && ((value[0] == '-') || (value[0] == '+')))
		value[0] = ' ';
	markup = g_strdup_printf ("<small>%s</small>", value);
	gtk_label_set_markup (GTK_LABEL (scale_data->value_label), markup);

	g_free (markup);
	g_free (value);
}
