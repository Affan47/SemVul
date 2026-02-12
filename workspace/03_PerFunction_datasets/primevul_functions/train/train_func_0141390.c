std::string binaryToString(const byte* buff, size_t size, size_t start )
    {
        std::string result = "";
        size += start;

        while (start < size) {
            int   c             = (int) buff[start++] ;
            bool  bTrailingNull = c == 0 && start == size;
            if ( !bTrailingNull ) {
                if (c < ' ' || c >= 127) c = '.' ;
                result +=  (char) c ;
            }
        }
        return result;
    }
