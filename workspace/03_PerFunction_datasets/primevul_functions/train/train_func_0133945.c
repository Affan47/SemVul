hfinfo_char_value_format(const header_field_info *hfinfo, char buf[32], guint32 value)
{

	int display = FIELD_DISPLAY(hfinfo->display);

	return hfinfo_char_value_format_display(display, buf, value);
}
