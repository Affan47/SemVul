lang_for_code2( const char *code )
{
    char code_string[4];
    iso639_lang_t * lang;

    code_string[0] = tolower( code[0] );
    code_string[1] = tolower( code[1] );
    code_string[2] = tolower( code[2] );
    code_string[3] = 0;

    for( lang = (iso639_lang_t*) languages; lang->eng_name; lang++ )
    {
        if( !strcmp( lang->iso639_2, code_string ) )
        {
            return lang;
        }
        if( lang->iso639_2b && !strcmp( lang->iso639_2b, code_string ) )
        {
            return lang;
        }
    }

    return (iso639_lang_t*) languages;
}
