mr_doc_freq(IndexReader *ir, int field_num, const char *t)
{
    int total = 0;
    int i = MR(ir)->r_cnt;
    for (i = MR(ir)->r_cnt - 1; i >= 0; i--) {
        int fnum = mr_get_field_num(MR(ir), i, field_num);
        if (fnum >= 0) {
            IndexReader *reader = MR(ir)->sub_readers[i];
            total += reader->doc_freq(reader, fnum, t);
        }
    }
    return total;
}
