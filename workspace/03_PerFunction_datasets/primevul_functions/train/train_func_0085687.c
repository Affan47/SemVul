AP4_AtomFactory::CreateAtomFromStream(AP4_ByteStream& stream,
                                      AP4_LargeSize&  bytes_available,
                                      AP4_Atom*&      atom)
{
    AP4_Result result;


    atom = NULL;


    if (bytes_available < 8) return AP4_ERROR_EOS;


    AP4_Position start;
    stream.Tell(start);


    AP4_UI32 size_32;
    result = stream.ReadUI32(size_32);
    if (AP4_FAILED(result)) {
        stream.Seek(start);
        return result;
    }
    AP4_UI64 size = size_32;


    AP4_Atom::Type type;
    result = stream.ReadUI32(type);
    if (AP4_FAILED(result)) {
        stream.Seek(start);
        return result;
    }


    bool atom_is_large = false;
    bool force_64      = false;
    if (size == 0) {

        AP4_LargeSize stream_size = 0;
        stream.GetSize(stream_size);
        if (stream_size >= start) {
            size = stream_size - start;
        }
    } else if (size == 1) {

        atom_is_large = true;
        if (bytes_available < 16) {
            stream.Seek(start);
            return AP4_ERROR_INVALID_FORMAT;
        }
        stream.ReadUI64(size);
        if (size <= 0xFFFFFFFF) {
            force_64 = true;
        }
    }


    if ((size > 0 && size < 8) || size > bytes_available) {
        stream.Seek(start);
        return AP4_ERROR_INVALID_FORMAT;
    }


    result = CreateAtomFromStream(stream, type, size_32, size, atom);
    if (AP4_FAILED(result)) return result;


    if (atom == NULL) {
        unsigned int payload_offset = 8;
        if (atom_is_large) payload_offset += 8;
        stream.Seek(start+payload_offset);
        atom = new AP4_UnknownAtom(type, size, stream);
    }


    if (force_64) {
        atom->SetSize32(1);
        atom->SetSize64(size);
    }


    bytes_available -= size;


    result = stream.Seek(start+size);
    if (AP4_FAILED(result)) {
        delete atom;
        atom = NULL;
        return result;
    }

    return AP4_SUCCESS;
}
