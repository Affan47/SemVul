AP4_SampleEntry::WriteFields(AP4_ByteStream& stream)
{
    AP4_Result result;


    result = stream.Write(m_Reserved1, sizeof(m_Reserved1));
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI16(m_DataReferenceIndex);
    if (AP4_FAILED(result)) return result;

    return result;
}
