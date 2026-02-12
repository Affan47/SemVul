MultiPartInputFile::initialize()
{
    readMagicNumberAndVersionField(*_data->is, _data->version);

    bool multipart = isMultiPart(_data->version);
    bool tiled = isTiled(_data->version);


    if (tiled && multipart)
        throw IEX_NAMESPACE::InputExc ("Multipart files cannot have the tiled bit set");


    int pos = 0;
    while (true)
    {
        Header header;
        header.readFrom(*_data->is, _data->version);


        if (header.readsNothing())
        {
            pos++;
            break;
        }

        _data->_headers.push_back(header);

        if(multipart == false)
          break;
    }


    for (size_t i = 0; i < _data->_headers.size(); i++)
    {


        if( _data->_headers[i].hasType() == false )
        {
            if(multipart)

                throw IEX_NAMESPACE::ArgExc ("Every header in a multipart file should have a type");

            _data->_headers[i].setType(tiled ? TILEDIMAGE : SCANLINEIMAGE);
        }
        else
        {


            if(!multipart && !isNonImage(_data->version))
            {
                _data->_headers[i].setType(tiled ? TILEDIMAGE : SCANLINEIMAGE);
            }
        }


        if( _data->_headers[i].hasName() == false )
        {
            if(multipart)
                throw IEX_NAMESPACE::ArgExc ("Every header in a multipart file should have a name");
        }

        if (isTiled(_data->_headers[i].type()))
            _data->_headers[i].sanityCheck(true, multipart);
        else
            _data->_headers[i].sanityCheck(false, multipart);
    }


    if (multipart)
    {
        set<string> names;
        for (size_t i = 0; i < _data->_headers.size(); i++)
        {

            if (names.find(_data->_headers[i].name()) != names.end())
            {
                throw IEX_NAMESPACE::InputExc ("Header name " + _data->_headers[i].name() +
                                   " is not a unique name.");
            }
            names.insert(_data->_headers[i].name());
        }
    }


    if (multipart && strictSharedAttribute)
    {
        for (size_t i = 1; i < _data->_headers.size(); i++)
        {
            vector <string> attrs;
            if (_data->checkSharedAttributesValues (_data->_headers[0], _data->_headers[i], attrs))
            {
                string attrNames;
                for (size_t j=0; j<attrs.size(); j++)
                    attrNames += " " + attrs[j];
                throw IEX_NAMESPACE::InputExc ("Header name " + _data->_headers[i].name() +
                                     " has non-conforming shared attributes: "+
                                     attrNames);
            }
        }
    }


    for (size_t i = 0; i < _data->_headers.size(); i++)
        _data->parts.push_back(
                new InputPartData(_data, _data->_headers[i], i, _data->numThreads, _data->version));

    _data->readChunkOffsetTables(_data->reconstructChunkOffsetTable);
}
