AP4_UnknownSampleEntry::WriteFields(AP4_ByteStream& stream)
{
    AP4_Result result;


    result = AP4_SampleEntry::WriteFields(stream);
    if (AP4_FAILED(result)) return result;


    return stream.Write(m_Payload.GetData(), m_Payload.GetDataSize());
}
