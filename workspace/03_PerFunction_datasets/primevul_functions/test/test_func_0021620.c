getCharacters(FileInfo *file, CharsString *characters) {

	CharsString token;
	if (!getToken(file, &token, "characters")) return 0;
	return parseChars(file, characters, &token);
}
