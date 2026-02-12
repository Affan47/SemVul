AP4_MpegAudioSampleEntry::ToSampleDescription()
{

    AP4_EsdsAtom* esds = AP4_DYNAMIC_CAST(AP4_EsdsAtom, GetChild(AP4_ATOM_TYPE_ESDS));
    if (esds == NULL) {

        if (m_QtVersion > 0) {
            esds = AP4_DYNAMIC_CAST(AP4_EsdsAtom, FindChild("wave/esds"));
        }
    }


    return new AP4_MpegAudioSampleDescription(GetSampleRate(),
                                              GetSampleSize(),
                                              GetChannelCount(),
                                              esds);
}
