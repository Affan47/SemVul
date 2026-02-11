global_user_list_cb(USER * user, struct guldata *data)
{
    ASSERT(validate_user(user));
    ASSERT(data != 0);
    if(data->flags)
    {

        if(!
            (((data->flags & ON_GFLAG_ADMIN) && user->level == LEVEL_ADMIN)
            || ((data->flags & ON_GFLAG_ELITE) && user->level == LEVEL_ELITE)
            || ((data->flags & ON_GFLAG_MODERATOR)
            && user->level == LEVEL_MODERATOR)
            || ((data->flags & ON_GFLAG_USERS) && user->level == LEVEL_USER)
            || ((data->flags & ON_GFLAG_LEECH) && user->level == LEVEL_LEECH)
            || ((data->flags & ON_GFLAG_MUZZLED) && user->flags & ON_MUZZLED)
            || ((data->flags & ON_GFLAG_CLOAKED) && user->cloaked)
            || ((data->flags & ON_GFLAG_USERIP) && (user->ip & data->mask) == (data->ip & data->mask))))
            return;
    }
    if(data->server && *data->server != '*' && strcasecmp(data->server, user->server) != 0)
        return;
    send_cmd(data->con, MSG_SERVER_GLOBAL_USER_LIST, "%s %s", user->nick, my_ntoa(BSWAP32(user->ip)));
}
