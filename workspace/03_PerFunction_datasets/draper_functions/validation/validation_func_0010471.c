freeinv_core(struct obj *obj)
{
    if (obj->oclass == COIN_CLASS) {
        u.ugold -= obj->quan;
        obj->in_use = false;
        flags.botl = 1;
        return;
    } else if (obj->otyp == AMULET_OF_YENDOR) {
        if (!u.uhave.amulet) impossible("don't have amulet?");
        u.uhave.amulet = 0;
    } else if (obj->otyp == CANDELABRUM_OF_INVOCATION) {
        if (!u.uhave.menorah) impossible("don't have candelabrum?");
        u.uhave.menorah = 0;
    } else if (obj->otyp == BELL_OF_OPENING) {
        if (!u.uhave.bell) impossible("don't have silver bell?");
        u.uhave.bell = 0;
    } else if (obj->otyp == SPE_BOOK_OF_THE_DEAD) {
        if (!u.uhave.book) impossible("don't have the book?");
        u.uhave.book = 0;
    } else if (obj->oartifact) {
        if (is_quest_artifact(obj)) {
            if (!u.uhave.questart)
                    impossible("don't have quest artifact?");
            u.uhave.questart = 0;
        }
        set_artifact_intrinsic(obj, 0, W_ART);
    }

    if (obj->otyp == LOADSTONE) {
        curse(obj);
    } else if (confers_luck(obj)) {
        set_moreluck();
        flags.botl = 1;
    } else if (obj->otyp == FIGURINE && obj->timed) {
        stop_timer(FIG_TRANSFORM, (void *) obj);
    }
}
