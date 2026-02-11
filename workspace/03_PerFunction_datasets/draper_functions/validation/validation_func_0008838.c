readFromFile(FILE* rf)
    {
        char chunk[8];
        bool result = true;
        uint32 chunkSize = 0;
        uint32 count =0;
        triangles.clear();
        vertices.clear();
        delete iLiquid;
        iLiquid = 0;

        if (result && fread(&iBound, sizeof(G3D::AABox), 1, rf) != 1) { result = false; }
        if (result && fread(&iMogpFlags, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (result && fread(&iGroupWMOID, sizeof(uint32), 1, rf) != 1) { result = false; }


        if (result && !readChunk(rf, chunk, "VERT", 4)) { result = false; }
        if (result && fread(&chunkSize, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (result && fread(&count, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (!count)
            { return result; }
        if (result) { vertices.resize(count); }
        if (result && fread(&vertices[0], sizeof(Vector3), count, rf) != count) { result = false; }


        if (result && !readChunk(rf, chunk, "TRIM", 4)) { result = false; }
        if (result && fread(&chunkSize, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (result && fread(&count, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (count)
        {
            if (result) { triangles.resize(count); }
            if (result && fread(&triangles[0], sizeof(MeshTriangle), count, rf) != count) { result = false; }
        }


        if (result && !readChunk(rf, chunk, "MBIH", 4)) { result = false; }
        if (result) { result = meshTree.readFromFile(rf); }


        if (result && !readChunk(rf, chunk, "LIQU", 4)) { result = false; }
        if (result && fread(&chunkSize, sizeof(uint32), 1, rf) != 1) { result = false; }
        if (result && chunkSize > 0)
            { result = WmoLiquid::readFromFile(rf, iLiquid); }
        return result;
    }
