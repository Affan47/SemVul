AP4_VisualSampleEntry::WriteFields(AP4_ByteStream& stream)
{
    AP4_Result result;


    result = AP4_SampleEntry::WriteFields(stream);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_Predefined1);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_Reserved2);
    if (AP4_FAILED(result)) return result;


    result = stream.Write(m_Predefined2, sizeof(m_Predefined2));
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_Width);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_Height);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI32(m_HorizResolution);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI32(m_VertResolution);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI32(m_Reserved3);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_FrameCount);
    if (AP4_FAILED(result)) return result;


    unsigned char compressor_name[32];
    unsigned int name_length = m_CompressorName.GetLength();
    if (name_length > 31) name_length = 31;
    compressor_name[0] = (unsigned char)name_length;
    for (unsigned int i=0; i<name_length; i++) {
        compressor_name[i+1] = m_CompressorName[i];
    }
    for (unsigned int i=name_length+1; i<32; i++) {
        compressor_name[i] = 0;
    }
    result = stream.Write(compressor_name, 32);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_Depth);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_Predefined3);
    if (AP4_FAILED(result)) return result;

    return result;
}
