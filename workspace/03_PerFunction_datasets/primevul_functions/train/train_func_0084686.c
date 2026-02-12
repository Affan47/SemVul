static bool memory_overlap(struct uc_struct *uc, uint64_t begin, size_t size)
{
    unsigned int i;
    uint64_t end = begin + size - 1;

    i = bsearch_mapped_blocks(uc, begin);


    if (i >= uc->mapped_block_count)
        return false;


    if (end >= uc->mapped_blocks[i]->addr)
        return true;


    return false;
}
