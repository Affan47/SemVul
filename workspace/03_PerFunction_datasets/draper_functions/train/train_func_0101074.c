delete_inner_hmdf_table_for_blocks(Block *head)
{
    Block *bpt;

    for (bpt = head; bpt != NULL; bpt = bpt->next) {
        if (bpt->hmdf != NULL
            && is_inner_of_acc_block(bpt)) {
#ifdef DEBUG_HETERO_HMDF
            fprintf(stderr,
                    "HMDF Table is deleted.(Module:%s Block:%d MTG_ID:%d)\n",
                    bpt->module->name, bpt->no, bpt->hmdf->mtg_id);
#endif
            delete_inner_hmdf_table_for_one_block(bpt);
        }
        if (bpt->inner) {
            delete_inner_hmdf_table_for_blocks(bpt->inner);
        }
    }
}
