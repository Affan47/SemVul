setCubicTextureName( const String& name, bool forUVW)
    {
        if (forUVW)
        {
            setCubicTextureName(&name, forUVW);
        }
        else
        {
            setContentType(CONTENT_NAMED);
            mTextureLoadFailed = false;
            String ext;
            String suffixes[6] = {"_fr", "_bk", "_lf", "_rt", "_up", "_dn"};
            String baseName;
            String fullNames[6];

            size_t pos = name.find_last_of(".");
            if( pos != String::npos )
            {
                baseName = name.substr(0, pos);
                ext = name.substr(pos);
            }
            else
                baseName = name;

            for (int i = 0; i < 6; ++i)
            {
                fullNames[i] = baseName + suffixes[i] + ext;
            }

            setCubicTextureName(fullNames, forUVW);
        }
    }
