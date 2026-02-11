utf32_is_decomposed_char(uint32 uc, bool nfkd)
{
	if (UNICODE_IS_ASCII(uc)) {
		return TRUE;
	} else if (UNICODE_IS_HANGUL(uc)) {
		return FALSE;
	} else {
		return NULL == utf32_decompose_lookup(uc, nfkd);
	}
}
