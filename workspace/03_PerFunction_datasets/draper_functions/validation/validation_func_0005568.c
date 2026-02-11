getToken(toktype expected) {
	token *ret = tokenPeek();
	peektok = NULL;
	if (expected != ANYTOKEN && ret->type != expected)
		throw parseException("unexpected token");
	return ret;
}
