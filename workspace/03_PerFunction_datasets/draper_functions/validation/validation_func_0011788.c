has_wildcards( char const * const str )
{
    return str[ strcspn( str, "[]*?" ) ] ? 1 : 0;
}
