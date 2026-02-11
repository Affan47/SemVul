isAlphaNum(Char c) {
    return isLatin1(c) ? isAlphaNumLat1(c) :
	    get_properties(c)->category<=GENCAT_No;
}
