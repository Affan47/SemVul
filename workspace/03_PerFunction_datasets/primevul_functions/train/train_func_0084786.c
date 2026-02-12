readLineOffsets (OPENEXR_IMF_INTERNAL_NAMESPACE::IStream &is,
                 LineOrder lineOrder,
                 vector<uint64_t> &lineOffsets,
                 bool &complete)
{
    for (unsigned int i = 0; i < lineOffsets.size(); i++)
    {
        OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (is, lineOffsets[i]);
    }

    complete = true;

    for (unsigned int i = 0; i < lineOffsets.size(); i++)
    {
        if (lineOffsets[i] <= 0)
        {


            complete = false;
            reconstructLineOffsets (is, lineOrder, lineOffsets);
            break;
        }
    }
}
