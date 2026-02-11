evt_size_changed(GObject *obj, gpointer user)
{
	CmdCfg		*cmc = user;
	CField		*fld;
	gpointer	instance;

	get_object_data(obj, &fld, &instance);

	if((cmc != NULL) && (fld != NULL) && (instance != NULL))
	{
		gchar		buf[32];
		gsize		value = GTK_ADJUSTMENT(obj)->value;
		GtkWidget	*label = g_object_get_data(obj, "label");

		value *= fld->field.size.step;
		if(fld->field.size.step >= 512)
			sze_put_offset(buf, sizeof buf, value, SZE_KB, 0, ',');
		else
			sze_put_offset(buf, sizeof buf, value, SZE_BYTES, 0, ',');
		gtk_label_set_text(GTK_LABEL(label), buf);

		*(gsize *) ((gchar *) instance + fld->offset) = value;
		set_modified(cmc, instance, TRUE);
	}

	return TRUE;
}
