copy_callbacks(void)
{
	gint i;
	for (i=0; glspi_geany_callbacks[i].signal_name; i++) {
		CB_COPY(signal_name);
		CB_COPY(callback);
		CB_COPY(after);
		CB_COPY(user_data);
	}
}
