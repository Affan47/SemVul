has_other_array_access_in_cmp_block(Block *cmp_block, Statement *stm,
                                    int e1, int e2)
{
    if (has_other_array_access_in_block(cmp_block, stm, e1, e2)) return TRUE;
    if (cmp_block->inner != NULL
        && has_other_array_access_in_blocks(cmp_block->inner, stm, e1, e2)) {
        return TRUE;
    }
    return FALSE;
}
