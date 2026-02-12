AP4_StszAtom::WriteFields(AP4_ByteStream& stream)
{
    AP4_Result result;


    result = stream.WriteUI32(m_SampleSize);
    if (AP4_FAILED(result)) return result;


    result = stream.WriteUI32(m_SampleCount);
    if (AP4_FAILED(result)) return result;


    if (m_SampleSize == 0) {
        for (AP4_UI32 i=0; i<m_SampleCount; i++) {
            result = stream.WriteUI32(m_Entries[i]);
            if (AP4_FAILED(result)) return result;
        }
    }

    return result;
}
