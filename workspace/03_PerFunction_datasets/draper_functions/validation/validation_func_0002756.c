search_stasche_block_and_append_assign_acc(Block *block, IntSet id_set)
{
    List *list;
    List *lpt;
    Block *target;
    Directive *new_dir;

    list = search_outer_block_for_stasche(block);
    for (lpt = list; lpt != NULL; lpt = lpt->next) {
        target = (Block *)(lpt->data);
        new_dir = make_assign_acc_dir(id_set);
        append_new_dir_to_block(target, new_dir);
    }
}
