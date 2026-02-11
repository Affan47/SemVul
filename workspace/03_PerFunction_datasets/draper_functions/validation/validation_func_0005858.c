readSubMeshNameTable(DataStreamPtr& stream, Mesh* pMesh)
    {

        map<unsigned short, String>::type subMeshNames;
        unsigned short streamID, subMeshIndex;


        if (!stream->eof())
        {
            pushInnerChunk(stream);
            streamID = readChunk(stream);
            while(!stream->eof() && (streamID == M_SUBMESH_NAME_TABLE_ELEMENT ))
            {

                readShorts(stream, &subMeshIndex, 1);

                subMeshNames[subMeshIndex] = readString(stream);


                if (!stream->eof())
                    streamID = readChunk(stream);
            }
            if (!stream->eof())
            {

                backpedalChunkHeader(stream);
            }
            popInnerChunk(stream);
        }


        map<unsigned short, String>::type::const_iterator it = subMeshNames.begin();

        while(it != subMeshNames.end())
        {

            pMesh->nameSubMesh(it->second, it->first);
            ++it;
        }


    }
