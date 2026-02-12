AP4_SubtitleSampleEntry::InspectFields(AP4_AtomInspector& inspector)
{

    AP4_SampleEntry::InspectFields(inspector);


    inspector.AddField("namespace",       m_Namespace.GetChars());
    inspector.AddField("schema_location", m_SchemaLocation.GetChars());
    inspector.AddField("image_mime_type", m_ImageMimeType.GetChars());

    return AP4_SUCCESS;
}
