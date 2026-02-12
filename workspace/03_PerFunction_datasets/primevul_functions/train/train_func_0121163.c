void print_read_error(int error_code)
{
	switch (error_code) {

		case END_OF_DATA_UNEXPECTED:

			fprintf(stderr, _("End of data collecting unexpected\n"));
			break;

		default:

			fprintf(stderr, _("Inconsistent input data\n"));
			break;
	}
	exit(3);
}
