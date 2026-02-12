static bool tEXtToDataBuf(const byte* bytes,long length,DataBuf& result)
    {
        static const char* hexdigits = "0123456789ABCDEF";
        static int         value   [256] ;
        static bool        bFirst = true ;
        if ( bFirst ) {
            for ( int i = 0 ; i < 256 ; i++ )
                value[i] = 0;
            for ( int i = 0 ; i < 16 ; i++ ) {
                value[tolower(hexdigits[i])]=i+1;
                value[toupper(hexdigits[i])]=i+1;
            }
            bFirst = false;
        }


        long        count=0;

        const byte* p = bytes ;


        while ((count < 3) && (p - bytes < length)) {

            --length;
            if ( *p++ == '\n' ) {
                count++;
            }
        }
        for ( long i = 0 ; i < length ; i++ )
            if ( value[p[i]] )
                ++count;
        result.alloc((count+1)/2) ;


        count   = 0 ;
        byte* r = result.pData_;
        int   n = 0 ;
        for ( long i = 0 ; i < length ; i++ ) {
            if ( value[p[i]] ) {
                int v = value[p[i]]-1 ;
                if ( ++count % 2 ) n = v*16 ;
                else *r++ =        n + v    ;
            }
        }
        return true;
    }
