parse_assert(int expr, char *msg, ...)
{
	va_list l;

	if (!expr) {
		char *error_string;

		va_start(l, msg);

		error_string = irmo_vasprintf(msg, l);

		irmo_error_report("irmo_interface_new", "%s: %i: %s",
				  yyin_filename, line_num,
				  error_string);

		free(error_string);

		va_end(l);

		longjmp(parse_error_env, 1);
	}
}
