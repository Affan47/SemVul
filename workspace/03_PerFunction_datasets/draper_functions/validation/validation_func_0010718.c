mr_get_norms(IndexReader *ir, int field_num)
{
    uchar *bytes;

    mutex_lock(&ir->mutex);
    bytes = h_get_int(MR(ir)->norms_cache, field_num);
    if (NULL == bytes) {
        int i;
        const int mr_reader_cnt = MR(ir)->r_cnt;

        bytes = ALLOC_AND_ZERO_N(uchar, MR(ir)->max_doc);

        for (i = 0; i < mr_reader_cnt; i++) {
            int fnum = mr_get_field_num(MR(ir), i, field_num);
            if (fnum >= 0) {
                IndexReader *reader = MR(ir)->sub_readers[i];
                reader->get_norms_into(reader, fnum, bytes + MR(ir)->starts[i]);
            }
        }
        h_set_int(MR(ir)->norms_cache, field_num, bytes);
    }
    mutex_unlock(&ir->mutex);

    return bytes;
}
