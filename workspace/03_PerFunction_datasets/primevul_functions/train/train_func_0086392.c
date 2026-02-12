AP4_VisualSampleEntry::InspectFields(AP4_AtomInspector& inspector)
{

    AP4_SampleEntry::InspectFields(inspector);


    inspector.AddField("width", m_Width);
    inspector.AddField("height", m_Height);
    inspector.AddField("compressor", m_CompressorName.GetChars());

    return AP4_SUCCESS;
}
