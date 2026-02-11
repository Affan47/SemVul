index_of(char ch) {
	if(ch==' ') return STRING_NOT_FOUND;
	return alphabet.pos(ch);
}
