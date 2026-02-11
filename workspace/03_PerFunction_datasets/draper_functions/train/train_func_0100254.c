command_abil(object *op, const char *params) {
    char thing[20], thing2[20];
    int iii;
    player *pl;

    iii = 0;
    thing[0] = '\0';
    thing2[0] = '\0';
    if (*params == '\0'
    || sscanf(params, "%s %s %d", thing, thing2, &iii) != 3
    || thing[0] == '\0') {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                      "Who?");
        return;
    }

    if (thing2[0] == '\0') {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                      "You can't change that.");
        return;
    }

    if (iii < MIN_STAT || iii > settings.max_stat) {
        draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                      "Illegal range of stat.\n");
        return;
    }

    for (pl = first_player; pl != NULL; pl = pl->next) {
        if (!strcmp(pl->ob->name, thing)) {
            if (settings.real_wiz == FALSE)
                SET_FLAG(pl->ob, FLAG_WAS_WIZ);
            if (!strcmp("str", thing2))
                pl->ob->stats.Str = iii, pl->orig_stats.Str = iii;
            if (!strcmp("dex", thing2))
                pl->ob->stats.Dex = iii, pl->orig_stats.Dex = iii;
            if (!strcmp("con", thing2))
                pl->ob->stats.Con = iii, pl->orig_stats.Con = iii;
            if (!strcmp("wis", thing2))
                pl->ob->stats.Wis = iii, pl->orig_stats.Wis = iii;
            if (!strcmp("cha", thing2))
                pl->ob->stats.Cha = iii, pl->orig_stats.Cha = iii;
            if (!strcmp("int", thing2))
                pl->ob->stats.Int = iii, pl->orig_stats.Int = iii;
            if (!strcmp("pow", thing2))
                pl->ob->stats.Pow = iii, pl->orig_stats.Pow = iii;
            draw_ext_info_format(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_DM,
                                 "%s has been altered.",
                                 pl->ob->name);
            fix_object(pl->ob);
            return;
        }
    }

    draw_ext_info(NDI_UNIQUE, 0, op, MSG_TYPE_COMMAND, MSG_TYPE_COMMAND_ERROR,
                  "No such player.");
}
