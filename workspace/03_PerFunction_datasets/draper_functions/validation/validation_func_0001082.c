translate_string( po_file_t po, string_t *str, int *found )
{
    string_t *new;
    const char *transl;
    int res;
    char *buffer, *msgid, *context;

    if (!str->size || !(buffer = convert_msgid_ascii( str, 0 )))
        return convert_string( str, str_unicode, 1252 );

    msgid = buffer;
    context = get_message_context( &msgid );
    transl = get_msgstr( po, msgid, context, found );

    new = xmalloc( sizeof(*new) );
    new->type = str_unicode;
    new->size = wine_utf8_mbstowcs( 0, transl, strlen(transl), NULL, 0 );
    new->str.wstr = xmalloc( (new->size+1) * sizeof(WCHAR) );
    res = wine_utf8_mbstowcs( MB_ERR_INVALID_CHARS, transl, strlen(transl), new->str.wstr, new->size );
    if (res == -2)
        error( "Invalid utf-8 character in string '%s'\n", transl );
    new->str.wstr[new->size] = 0;
    free( buffer );
    return new;
}
