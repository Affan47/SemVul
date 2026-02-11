utolower(wchar_t c) {
    if (c == L'\0')
	return c;
#ifdef HAS_TOWLOWER
    return towlower(c);
#else
    if (c >= 'A' && c <= 'Z')
	c += 'a'-'A';
    return c;
#endif
}
