debug_print(debug_level::flag level, const std::string& domain, const char* format, ...)
{
	std::va_list ap;
	va_start(ap, format);

	std::string s = hz::string_vsprintf(format, ap);

	va_end(ap);
	debug_out(level, domain) << s;
}
