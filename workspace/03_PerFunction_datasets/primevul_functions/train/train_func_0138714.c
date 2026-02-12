MONGO_EXPORT int mongo_validate_ns( mongo *conn, const char *ns ) {
    char *last = NULL;
    char *current = NULL;
    const char *db_name = ns;
    char *collection_name = NULL;
    char errmsg[64];
    int ns_len = 0;


    if( *ns == '.' ) {
        __mongo_set_error( conn, MONGO_NS_INVALID, "ns cannot start with a '.'.", 0 );
        return MONGO_ERROR;
    }


    for( current = (char *)ns; *current != '\0'; current++ ) {
        if( *current == '.' ) {
            current++;
            break;
        }
    }


    if( *current == '.' ) {
        __mongo_set_error( conn, MONGO_NS_INVALID, "ns cannot start with a '.'.", 0 );
        return MONGO_ERROR;
    }


    if( *current == '\0' ) {
        __mongo_set_error( conn, MONGO_NS_INVALID, "Collection name missing.", 0 );
        return MONGO_ERROR;
    }


    collection_name = current;


    if( collection_name - 1 == db_name ) {
        __mongo_set_error( conn, MONGO_NS_INVALID, "Database name missing.", 0 );
        return MONGO_ERROR;
    }


    for( current = (char *)db_name; *current != '.'; current++ ) {
        switch( *current ) {
        case ' ':
        case '$':
        case '/':
        case '\\':
            __mongo_set_error( conn, MONGO_NS_INVALID,
                               "Database name may not contain ' ', '$', '/', or '\\'", 0 );
            return MONGO_ERROR;
        default:
            break;
        }

        ns_len++;
    }


    ns_len++;


    for( current = collection_name; *current != '\0'; current++ ) {


        if( last && *last == '.' && *current == '.' ) {
            __mongo_set_error( conn, MONGO_NS_INVALID,
                               "Collection may not contain two consecutive '.'", 0 );
            return MONGO_ERROR;
        }


        if( *current == '$' ) {
            __mongo_set_error( conn, MONGO_NS_INVALID,
                               "Collection may not contain '$'", 0 );
            return MONGO_ERROR;
        }

        last = current;
        ns_len++;
    }

    if( ns_len > 128 ) {
        bson_sprintf( errmsg, "Namespace too long; has %d but must <= 128.",
                      ns_len );
        __mongo_set_error( conn, MONGO_NS_INVALID, errmsg, 0 );
        return MONGO_ERROR;
    }


    if( *(current - 1) == '.' ) {
        __mongo_set_error( conn, MONGO_NS_INVALID,
                           "Collection may not end with '.'", 0 );
        return MONGO_ERROR;
    }

    return MONGO_OK;
}
