find_line(const char *ptr, const char * const *lines, size_t line_count) {
	const char * const *orig = lines;
	const char * const *orig_e = lines+line_count;

	while (line_count > 1) {
		size_t middle = line_count>>1;
		if (ptr < lines[middle])
			line_count = middle;
		else {
			lines += middle;
			line_count -= middle;
		}
	}


	while (lines+1 < orig_e && lines[0]==lines[1])
		lines++;


	return lines - orig;
}
