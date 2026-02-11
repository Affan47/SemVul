dumpstring(char *string) {
	char *name;
	if (string == NULL)
		return "NULL";
	name = dictget(strings, string);
	if (name == NULL) {
		name = str("S_%F", string);
		if (strlen(name) > MAXVARNAME)
			name = str("X_%ulx", string);
		print("static const char %s[] = ", name);
		if (allprintable(string))
			print("\"%s\";\n", string);
		else {
			int c;
			char *s;
			print("{ ");
			for (s = string; (c = *(unsigned char *) s) != '\0'; s++) {
				switch (c) {
				case '\a':	print("'\\a'");		break;
				case '\b':	print("'\\b'");		break;
				case '\f':	print("'\\f'");		break;
				case '\n':	print("'\\n'");		break;
				case '\r':	print("'\\r'");		break;
				case '\t':	print("'\\t'");		break;
				case '\'':	print("'\\''");		break;
				case '\\':	print("'\\\\'");	break;
				default:	print(isprint(c) ? "'%c'" :"%d", c); break;
				}
				print(", ");
			}
			print("'\\0', };\n");
		}
		strings = dictput(strings, string, name);
	}
	return name;
}
