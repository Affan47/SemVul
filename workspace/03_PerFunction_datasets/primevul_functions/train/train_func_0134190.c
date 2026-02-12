void proto_report_dissector_bug(const char *format, ...)
{
	va_list args;

	if (wireshark_abort_on_dissector_bug) {


		va_start(args, format);
		ws_vadd_crash_info(format, args);
		va_end(args);


		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
		putc('\n', stderr);


		abort();
	} else {
		va_start(args, format);
		VTHROW_FORMATTED(DissectorError, format, args);
		va_end(args);
	}
}
