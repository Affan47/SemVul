void XmpData::eraseFamily(XmpData::iterator& pos)
    {


        std::string         key(pos->key());
        Exiv2::StringVector keys;
        while ( pos != xmpMetadata_.end() ) {
            if ( pos->key().find(key)==0 ) {
                keys.push_back(pos->key());
                pos++;
            } else {
                break;
            }
        }

        for ( Exiv2::StringVector_i it = keys.begin() ; it != keys.end() ; it++ ) {
            erase(findKey(Exiv2::XmpKey(*it)));
        }
    }
