AP4_MetaData::Entry::AddToFile(AP4_File& file, AP4_Ordinal index)
{

    if (m_Value == NULL) return AP4_ERROR_INVALID_STATE;


    if (m_Key.GetNamespace() == "meta") {
        return AddToFileIlst(file, index);
    } else if (m_Key.GetNamespace() == "dcf") {
        return AddToFileDcf(file, index);
    } else {

        return AddToFileIlst(file, index);
    }
}
