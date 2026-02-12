AP4_StszAtom::SetSampleSize(AP4_Ordinal sample, AP4_Size sample_size)
{

    if (sample > m_SampleCount || sample == 0) {
        return AP4_ERROR_OUT_OF_RANGE;
    } else {
        if (m_Entries.ItemCount() == 0) {

            if (sample_size != m_SampleSize) {

                if (sample == 1) {

                    m_SampleSize = sample_size;
                    return AP4_SUCCESS;
                } else {

                    return AP4_ERROR_INVALID_PARAMETERS;
                }
            }
        } else {

            m_Entries[sample - 1] = sample_size;
        }

        return AP4_SUCCESS;
    }
}
