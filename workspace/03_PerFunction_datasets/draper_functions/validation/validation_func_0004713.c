update_event_printk(struct trace_event_call *call,
				struct trace_enum_map *map)
{
	char *ptr;
	int quote = 0;
	int len = strlen(map->enum_string);

	for (ptr = call->print_fmt; *ptr; ptr++) {
		if (*ptr == '\\') {
			ptr++;

			if (!*ptr)
				break;
			continue;
		}
		if (*ptr == '"') {
			quote ^= 1;
			continue;
		}
		if (quote)
			continue;
		if (isdigit(*ptr)) {

			do {
				ptr++;

			} while (isalnum(*ptr));
			if (!*ptr)
				break;


			continue;
		}
		if (isalpha(*ptr) || *ptr == '_') {
			if (strncmp(map->enum_string, ptr, len) == 0 &&
			    !isalnum(ptr[len]) && ptr[len] != '_') {
				ptr = enum_replace(ptr, map, len);

				if (WARN_ON_ONCE(!ptr))
					return;


				continue;
			}
		skip_more:
			do {
				ptr++;
			} while (isalnum(*ptr) || *ptr == '_');
			if (!*ptr)
				break;


			if (*ptr == '.' || (ptr[0] == '-' && ptr[1] == '>')) {
				ptr += *ptr == '.' ? 1 : 2;
				if (!*ptr)
					break;
				goto skip_more;
			}


			continue;
		}
	}
}
