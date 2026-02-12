AP4_MetaData::Entry::AddToFileDcf(AP4_File& file, AP4_Ordinal index)
{

    if (m_Value == NULL) return AP4_ERROR_INVALID_STATE;


    AP4_ContainerAtom* odhe = AP4_DYNAMIC_CAST(AP4_ContainerAtom, file.FindChild("odrm/odhe"));
    if (odhe == NULL) return AP4_ERROR_NO_SUCH_ITEM;


    AP4_ContainerAtom* udta = AP4_DYNAMIC_CAST(AP4_ContainerAtom, odhe->FindChild("udta", true));
    if (udta == NULL) return AP4_ERROR_INTERNAL;


    AP4_Atom* data_atom;
    AP4_Result result = ToAtom(data_atom);
    if (AP4_FAILED(result)) return result;


    return udta->AddChild(data_atom, index);
}
