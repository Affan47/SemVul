adjust_array_slot_dim_next(Block       *block_head,
                           int         entry,
                           Operand     *slot_no,
                           SemTree **offsets)
{
    Block       *bpt;

    bpt = block_head;
    while (bpt != NULL) {
        adjust_array_slot_dim(bpt, entry, slot_no, offsets);
        bpt = bpt->next;
    }
}
