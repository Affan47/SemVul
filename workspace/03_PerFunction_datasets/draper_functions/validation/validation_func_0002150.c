makes_invisible_to(object *pl, object *mon) {
    if (!pl->invisible)
        return 0;
    if (pl->type == PLAYER) {

        if (!pl->contr->invis_race) {
            if (QUERY_FLAG(mon, FLAG_UNDEAD))
                return 0;
            return 1;
        }

        if (!strcmp(pl->contr->invis_race, "undead") && is_true_undead(mon))
            return 1;

        if (!mon->race)
            return 0;
        if (strstr(mon->race, pl->contr->invis_race))
            return 1;

        return 0;
    } else {

        return 1;
    }
}
