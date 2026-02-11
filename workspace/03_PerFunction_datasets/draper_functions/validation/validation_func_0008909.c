get_word()
{
    int ch;


    for (wtext[wcnt] = lptr; (ch = *lptr) != EOS && !spacep(ch); )
	*lptr++ = (isupper(ch) ? tolower(ch) : ch);
    if (*lptr != EOS) *lptr++ = EOS;


    if (words[wcnt] = findword(wtext[wcnt]))
	return (words[wcnt]);
    else {
	trm_str("I don't know the word \"");
	trm_str(wtext[wcnt]);
	trm_str("\".\n");
	return (NIL);
    }
}
