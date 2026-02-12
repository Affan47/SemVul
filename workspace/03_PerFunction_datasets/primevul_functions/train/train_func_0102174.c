static int sanitary_path_copy(char *dst, const char *src)
{
	char *dst0 = dst;

	if (*src == '/') {
		*dst++ = '/';
		while (*src == '/')
			src++;
	}

	for (;;) {
		char c = *src;


		if (c == '.') {
			switch (src[1]) {
			case '\0':

				src++;
				break;
			case '/':

				src += 2;
				while (*src == '/')
					src++;
				continue;
			case '.':
				switch (src[2]) {
				case '\0':

					src += 2;
					goto up_one;
				case '/':

					src += 3;
					while (*src == '/')
						src++;
					goto up_one;
				}
			}
		}


		while ((c = *src++) != '\0' && c != '/')
			*dst++ = c;
		if (c == '/') {
			*dst++ = c;
			while (c == '/')
				c = *src++;
			src--;
		} else if (!c)
			break;
		continue;

	up_one:


		dst -= 2;
		if (dst < dst0)
			return -1;
		while (1) {
			if (dst <= dst0)
				break;
			c = *dst--;
			if (c == '/') {
				dst += 2;
				break;
			}
		}
	}
	*dst = '\0';
	return 0;
}
