AP4_SubtitleSampleEntry::ToSampleDescription()
{

    return new AP4_SubtitleSampleDescription(m_Type,
                                             m_Namespace.GetChars(),
                                             m_SchemaLocation.GetChars(),
                                             m_ImageMimeType.GetChars());
}
