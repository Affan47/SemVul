ca_cli_callback_dhgen (int argc, char **argv)
{
	gint primebitlength = atoi (argv[1]);
	gchar *filename = argv[2];

	gchar *error = NULL;

	if (primebitlength == 0 || primebitlength % 1024) {
		dialog_error (_("The bit-length of the prime number must be whole multiple of 1024"));
		return 1;
	}

	error = export_dh_param (primebitlength, filename);

	if (error)
		dialog_error (error);
	else
		printf (_("Diffie-Hellman parameters created and saved successfully in file '%s'\n"), filename);
	return 0;
}
