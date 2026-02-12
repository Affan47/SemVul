AP4_MetaData::Entry::AddToFileIlst(AP4_File& file, AP4_Ordinal index)
{

    if (m_Value == NULL) return AP4_ERROR_INVALID_STATE;


    AP4_Atom* atom;
    AP4_Result result = ToAtom(atom);
    if (AP4_FAILED(result)) return result;
    AP4_ContainerAtom* entry_atom = AP4_DYNAMIC_CAST(AP4_ContainerAtom, atom);
    if (entry_atom == NULL) {
        return AP4_ERROR_INVALID_FORMAT;
    }


    AP4_Movie* movie = file.GetMovie();
    if (movie == NULL) return AP4_ERROR_INVALID_FORMAT;
    AP4_MoovAtom* moov = movie->GetMoovAtom();
    if (moov == NULL) return AP4_ERROR_INVALID_FORMAT;


    AP4_ContainerAtom* udta = AP4_DYNAMIC_CAST(AP4_ContainerAtom, moov->FindChild("udta", true));
    if (udta == NULL) return AP4_ERROR_INTERNAL;


    AP4_ContainerAtom* meta = AP4_DYNAMIC_CAST(AP4_ContainerAtom, udta->FindChild("meta", true, true));
    if (meta == NULL) return AP4_ERROR_INTERNAL;


    AP4_HdlrAtom* hdlr = AP4_DYNAMIC_CAST(AP4_HdlrAtom, meta->FindChild("hdlr"));
    if (hdlr == NULL) {
        hdlr = new AP4_HdlrAtom(AP4_HANDLER_TYPE_MDIR, "");
        meta->AddChild(hdlr);
    } else {
        if (hdlr->GetHandlerType() != AP4_HANDLER_TYPE_MDIR) {
            return AP4_ERROR_INVALID_FORMAT;
        }
    }


    AP4_ContainerAtom* ilst = AP4_DYNAMIC_CAST(AP4_ContainerAtom, meta->FindChild("ilst", true));
    if (ilst == NULL) return AP4_ERROR_INTERNAL;


    AP4_ContainerAtom* existing = FindInIlst(ilst);
    if (existing == NULL) {

        ilst->AddChild(entry_atom);
    } else {

        AP4_DataAtom* data_atom = AP4_DYNAMIC_CAST(AP4_DataAtom, entry_atom->GetChild(AP4_ATOM_TYPE_DATA));
        if (data_atom == NULL) return AP4_ERROR_INTERNAL;
        entry_atom->RemoveChild(data_atom);
        existing->AddChild(data_atom, index);
        delete entry_atom;
    }

    return AP4_SUCCESS;
}
