static bool imap_is_valid_tag(const char *tag)
{
	for (; *tag != '\0'; tag++) {
		switch (*tag) {
		case '+':

		case '(':
		case ')':
		case '{':
		case '/':
		case ' ':

		case '%':
		case '*':

		case '"':
		case '\\':
			return FALSE;
		default:
			if (*tag < ' ')
				return FALSE;
			break;
		}
	}
	return TRUE;
}
}
