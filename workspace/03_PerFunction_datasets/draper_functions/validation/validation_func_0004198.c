localCodec()
{
	static s8 local_codec[32];
	if (!local_codec[0]) {


		setlocale(LC_CTYPE, "");

		s8 *locale = setlocale(LC_CTYPE, "");
		if (!locale || !strcmp(locale, "C")) {
			strcpy(local_codec, "UTF-8");
		} else {
			strncpy(local_codec, nl_langinfo(CODESET), sizeof(local_codec) - 1);
		}
	}

	return local_codec;
}
