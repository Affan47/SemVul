AP4_DataAtom::LoadString(AP4_String*& string)
{
    if (m_Source == NULL) {
        string = new AP4_String();
        return AP4_SUCCESS;
    } else {

        AP4_LargeSize size = 0;
        m_Source->GetSize(size);
        if (size > AP4_DATA_ATOM_MAX_SIZE) return AP4_ERROR_OUT_OF_RANGE;
        string = new AP4_String((AP4_Size)size);


        m_Source->Seek(0);
        AP4_Result result = m_Source->Read(string->UseChars(), (AP4_Size)size);
        if (AP4_FAILED(result)) {
            delete string;
            string = NULL;
        }

        return result;
    }
}
