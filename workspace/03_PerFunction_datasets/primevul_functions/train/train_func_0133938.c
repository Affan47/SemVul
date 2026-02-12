hfinfo_format_bytes(wmem_allocator_t *scope, const header_field_info *hfinfo,
    const guint8 *bytes, guint length)
{
	char *str = NULL;
	const guint8 *p;
	gboolean is_printable;

	if (bytes) {
		if (hfinfo->display & BASE_SHOW_ASCII_PRINTABLE) {


			is_printable = TRUE;
			for (p = bytes; p < bytes+length; p++) {
				if (!g_ascii_isprint(*p)) {

					is_printable = FALSE;
					break;
				}
			}


			if (is_printable) {
				str = wmem_strdup_printf(scope, "\"%.*s\"",
				    (int)length, bytes);
				return str;
			}
		}


		switch (FIELD_DISPLAY(hfinfo->display)) {
		case SEP_DOT:
			str = bytestring_to_str(scope, bytes, length, '.');
			break;
		case SEP_DASH:
			str = bytestring_to_str(scope, bytes, length, '-');
			break;
		case SEP_COLON:
			str = bytestring_to_str(scope, bytes, length, ':');
			break;
		case SEP_SPACE:
			str = bytestring_to_str(scope, bytes, length, ' ');
			break;
		case BASE_NONE:
		default:
			if (prefs.display_byte_fields_with_spaces) {
				str = bytestring_to_str(scope, bytes, length, ' ');
			} else {
				str = bytes_to_str(scope, bytes, length);
			}
			break;
		}
	}
	else {
		if (hfinfo->display & BASE_ALLOW_ZERO) {
			str = wmem_strdup(scope, "<none>");
		} else {
			str = wmem_strdup(scope, "<MISSING>");
		}
	}
	return str;
}
