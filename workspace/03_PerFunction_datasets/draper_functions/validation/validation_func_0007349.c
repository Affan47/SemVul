fs_rid_vector_truncate(fs_rid_vector *rv, int32_t length)
{
    if (!rv) return;

    if (rv->length < length) return;

    rv->length = length;
}
