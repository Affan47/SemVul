AP4_MetaData::Entry::RemoveFromFile(AP4_File& file, AP4_Ordinal index)
{

    if (m_Key.GetNamespace() == "meta") {
        return RemoveFromFileIlst(file, index);
    } else if (m_Key.GetNamespace() == "dcf") {
        return RemoveFromFileDcf(file, index);
    } else {

        return RemoveFromFileIlst(file, index);
    }
}
