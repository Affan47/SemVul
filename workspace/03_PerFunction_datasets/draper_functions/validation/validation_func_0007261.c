report_error (BusDesktopFileParser *parser,
	      char                 *message,
	      const char           *error_name,
	      DBusError            *error)
{
  const char *section_name = NULL;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  if (parser->current_section != -1)
    section_name = parser->desktop_file->sections[parser->current_section].section_name;

  if (section_name)
    dbus_set_error (error, error_name,
                    "Error in section %s at line %d: %s\n", section_name, parser->line_num, message);
  else
    dbus_set_error (error, error_name,
                    "Error at line %d: %s\n", parser->line_num, message);
}
