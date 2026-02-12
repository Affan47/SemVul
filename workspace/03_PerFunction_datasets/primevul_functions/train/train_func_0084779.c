reconstructLineOffsets (OPENEXR_IMF_INTERNAL_NAMESPACE::IStream &is,
                        LineOrder lineOrder,
                        vector<uint64_t> &lineOffsets)
{
    uint64_t position = is.tellg();

    try
    {
        for (unsigned int i = 0; i < lineOffsets.size(); i++)
        {
            uint64_t lineOffset = is.tellg();

            int y;
            OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (is, y);

            uint64_t packed_offset;
            uint64_t packed_sample;
            OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (is, packed_offset);
            OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (is, packed_sample);


            if (packed_offset < 0 ||
                packed_sample < 0 ||
                (INT64_MAX-packed_offset < packed_sample ) ||
                (INT64_MAX-(packed_offset+packed_sample) < 8 ) )
            {
                 throw IEX_NAMESPACE::IoExc("Invalid chunk size");
            }


            Xdr::skip <StreamIO> (is, static_cast<int>(packed_offset+packed_sample+8));

            if (lineOrder == INCREASING_Y)
                lineOffsets[i] = lineOffset;
            else
                lineOffsets[lineOffsets.size() - i - 1] = lineOffset;
        }
    }
    catch (...)
    {


    }

    is.clear();
    is.seekg (position);
}
