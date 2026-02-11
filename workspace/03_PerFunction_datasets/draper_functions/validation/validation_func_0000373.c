ste_set_field(TermEnum *te, int field_num)
{
    SegmentTermIndex *sti = h_get_int(STE(te)->sfi->field_dict, field_num);
    ste_reset(te);
    te->field_num = field_num;
    if (sti) {
        STE(te)->size = sti->size;
        is_seek(STE(te)->is, sti->ptr);
    }
    else {
        STE(te)->size = 0;
    }
    return te;
}
