AP4_MetaData::Entry::RemoveFromFileIlst(AP4_File& file, AP4_Ordinal index)
{

    AP4_Movie* movie = file.GetMovie();
    if (movie == NULL) return AP4_ERROR_INVALID_FORMAT;
    AP4_MoovAtom* moov = movie->GetMoovAtom();
    if (moov == NULL) return AP4_ERROR_INVALID_FORMAT;


    AP4_ContainerAtom* ilst = AP4_DYNAMIC_CAST(AP4_ContainerAtom, moov->FindChild("udta/meta/ilst"));
    if (ilst == NULL) return AP4_ERROR_NO_SUCH_ITEM;


    AP4_ContainerAtom* existing = FindInIlst(ilst);
    if (existing == NULL) return AP4_ERROR_NO_SUCH_ITEM;


    AP4_Result result = existing->DeleteChild(AP4_ATOM_TYPE_DATA, index);
    if (AP4_FAILED(result)) return result;


    if (existing->GetType() == AP4_ATOM_TYPE_dddd) {

        if (existing->GetChild(AP4_ATOM_TYPE_DATA) == NULL) {
            ilst->RemoveChild(existing);
            delete existing;
        }
    } else {

        if (existing->GetChildren().ItemCount() == 0) {
            ilst->RemoveChild(existing);
            delete existing;
        }
    }

    return AP4_SUCCESS;
}
