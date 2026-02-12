AP4_SampleEntry::Write(AP4_ByteStream& stream)
{
    AP4_Result result;


    result = WriteHeader(stream);
    if (AP4_FAILED(result)) return result;


    result = WriteFields(stream);
    if (AP4_FAILED(result)) return result;


    return m_Children.Apply(AP4_AtomListWriter(stream));
}
