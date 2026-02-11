set_assigned_blk(Block *block, Stasche_lm_dt *sld, List *head)
{
    int ***assigned_blk = sld->assigned_blk;
    int amax;
    int i;
    List *li;

    if (block->tlg_tag == -1
        || assigned_blk[block->tlg_tag][block->loop_order] != NULL) {
        return ;
    }

    amax = get_max_array_entry(block->module->array_head);
    assigned_blk[block->tlg_tag][block->loop_order]
        = zcalloc(amax + 1, sizeof(int));
    for (i = 0; i <= amax; i++) {
        assigned_blk[block->tlg_tag][block->loop_order][i] = -1;
    }
    for (li = head; li != NULL; li = li->next) {
        Aa *aa = li->data;
        int entry = aa->entry;

        assigned_blk[block->tlg_tag][block->loop_order][entry] = aa->slot->no;
    }
}
