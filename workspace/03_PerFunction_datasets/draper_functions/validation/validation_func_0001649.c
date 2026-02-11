score_wanted(bool current_ver, int rank, struct toptenentry *t1, int playerct, const char **players, int uid)
{
    int i;

    if (current_ver && (t1->ver_major != VERSION_MAJOR ||
                        t1->ver_minor != VERSION_MINOR ||
                        t1->patchlevel != PATCHLEVEL))
            return 0;

#ifdef PERS_IS_UID
    if (!playerct && t1->uid == uid)
            return 1;
#endif

    for (i = 0; i < playerct; i++)
    {
        if (players[i][0] == '-' && index("pr", players[i][1]) &&
            players[i][2] == 0 && i + 1 < playerct)
        {
            char *arg = (char *)players[i + 1];
            if ((players[i][1] == 'p' &&
                 str2role(arg) == str2role(t1->plrole)) ||
                (players[i][1] == 'r' &&
                 str2race(arg) == str2race(t1->plrace)))
                    return 1;
            i++;
        }
        else if (strcmp(players[i], "all") == 0 ||
                 strncmp(t1->name, players[i], NAMSZ) == 0 ||
                 (players[i][0] == '-' &&
                  players[i][1] == t1->plrole[0] &&
                  players[i][2] == 0) ||
                 (digit(players[i][0]) && rank <= atoi(players[i])))
                return 1;
    }
    return 0;
}
