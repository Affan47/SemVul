inner_block_has_strip_mining_block(Block *block)
{
    extern Boolean opt_lad_sm;

    if (!opt_lad_sm || block == NULL) return FALSE;
    if (is_strip_mining_block(block)) return TRUE;
    if (inner_blocks_has_strip_mining_block(block->inner)) return TRUE;
    return FALSE;
}
