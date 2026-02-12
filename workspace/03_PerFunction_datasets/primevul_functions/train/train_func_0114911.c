int XmpParser::encode(      std::string& ,
                          const XmpData&     xmpData,
                                uint16_t     ,
                                uint32_t     )
    {
        if (!xmpData.empty()) {
#ifndef SUPPRESS_WARNINGS
            EXV_WARNING << "XMP toolkit support not compiled in.\n";
#endif
        }
        return 1;
    }
