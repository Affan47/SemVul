bool getBase64Row(char* ptr, int , char* &beg, char* &end)
    {
        beg = end = ptr = skipSpaces(ptr, CV_XML_INSIDE_TAG);
        if( !ptr || !*ptr )
            return false;


        if ( *beg == '<' )
            return false;


        while( cv_isprint(*ptr) )
            ++ptr;
        if ( *ptr == '\0' )
            CV_PARSE_ERROR_CPP( "Unexpected end of line" );

        end = ptr;
        return true;
    }
