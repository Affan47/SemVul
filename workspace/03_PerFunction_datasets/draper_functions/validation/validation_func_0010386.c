mtde_next(TermDocEnum *tde)
{
    MultiTermDocEnum *mtde = MTDE(tde);
    if (NULL != mtde->curr_tde && mtde->curr_tde->next(mtde->curr_tde)) {
        return true;
    }
    else if (mtde_next_tde(mtde)) {
        return mtde_next(tde);
    }
    else {
        return false;
    }
}
