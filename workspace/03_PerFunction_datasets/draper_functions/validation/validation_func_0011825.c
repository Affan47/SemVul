parser_get_values ( PData *pd, char *name, List   **result )
{
    PData *entry;
    *result = 0;
    if ( !parser_get_pdata( pd, name, &entry ) ) {
        sprintf( parser_sub_error, "parser_get_values:\n %s", parser_error );
        strcpy( parser_error, parser_sub_error );
        return 0;
    }
    if ( !entry->values || entry->values->count == 0 ) {
        sprintf( parser_error, "parser_get_values: %s/%s: no values", pd->name, name );
        return 0;
    }
    *result = entry->values;
    return 1;
}
