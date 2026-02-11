GetAt(metastring * s, int pos)
{
    if ((pos < 0) || (pos >= s->length))
	return '\0';

    return ((char) *(s->str + pos));
}
