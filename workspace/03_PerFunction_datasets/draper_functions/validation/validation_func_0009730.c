search_stm_hetero_directive(Block *bpt)
{
    Pe_statement *pestm;
    Statement *stm;
    Directive *dir;

    for (pestm = bpt->pre_head; pestm != NULL; pestm = pestm->next) {
        for (stm = pestm->stm_head; stm != NULL; stm = stm->next) {
            for (dir = stm->dir_pre_head; dir != NULL; dir = dir->next) {
                Directive_func *func = dir->func;
                if (func->id == MFOR_ASSIGN_ACC) {
                    return dir;
                }
            }
        }
    }
    return NULL;
}
