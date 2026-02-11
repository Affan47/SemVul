IsVowel(metastring *s, int pos)
{
    char c;
    if((pos < 0) || (pos >= s->length))
	    return 0;
    c = *(s->str + pos);
    if ((c == 'A') || (c == 'E') || (c == 'I') || (c =='O') ||
            (c =='U')  || (c == 'Y'))
	    return 1;
    return 0;
}
