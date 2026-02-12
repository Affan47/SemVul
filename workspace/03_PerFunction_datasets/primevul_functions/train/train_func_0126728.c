pdf_nextobject(const char *ptr, size_t len)
{
	const char *p;
	int inobject = 1;

	while(len) {
		switch(*ptr) {
			case '\n':
			case '\r':
			case '%':
				p = pdf_nextlinestart(ptr, len);
				if(p == NULL)
					return NULL;
				len -= (size_t)(p - ptr);
				ptr = p;
				inobject = 0;
				break;

			case ' ':
			case '\t':
			case '[':
			case '\v':
			case '\f':
			case '<':
				inobject = 0;
				ptr++;
				len--;
				break;
			case '/':
				return ptr;
			default:
				if(!inobject)

					return ptr;
				ptr++;
				len--;
		}
	}
	return NULL;
}
