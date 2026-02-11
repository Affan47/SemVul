check_cmoves_in_pmr(const moverecord * pmr)
{
    gint c;

    if (!pmr) {
        outputerrf(_("No moverecord stored for this move."));
        return 0;
    }

    if (pmr->mt != MOVE_NORMAL) {
        outputerrf(_("This is not a normal chequer move. " "Cannot mark."));
        return 0;
    }

    if ((c = pmr->ml.cMoves) == 0) {
        outputerrf(_("No moves to analyse"));
        return 0;
    }

    return c;
}
