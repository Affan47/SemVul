string_ignore_whitespace( char *string )
{
    int i = 0;
    while ( string[i] != 0 && string[i] <= 32 ) i++;
    return string + i;
}
