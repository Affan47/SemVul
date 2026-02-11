filter_boxes( string_list_t *boxes, const char *prefix, string_list_t *patterns )
{
	string_list_t *nboxes = 0, *cpat;
	const char *ps;
	int not, fnot, pfxl;

	pfxl = prefix ? strlen( prefix ) : 0;
	for (; boxes; boxes = boxes->next) {
		if (memcmp( boxes->string, prefix, pfxl ))
			continue;
		fnot = 1;
		for (cpat = patterns; cpat; cpat = cpat->next) {
			ps = cpat->string;
			if (*ps == '!') {
				ps++;
				not = 1;
			} else
				not = 0;
			if (matches( boxes->string + pfxl, ps )) {
				fnot = not;
				break;
			}
		}
		if (!fnot)
			add_string_list( &nboxes, boxes->string + pfxl );
	}
	return nboxes;
}
