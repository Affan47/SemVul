cfapi_player_quest(int *type, ...) {
    int op;
    va_list args;
    object *player;
    sstring code;

    va_start(args, type);
    op = va_arg(args, int);
    player = va_arg(args, object *);
    code = va_arg(args, sstring);

    if (player->contr == NULL) {
        LOG(llevError, "cfapi_player_quest called with non player object %s!\n", player->name);
        va_end(args);

        return;
    }

    switch(op) {
        case CFAPI_PLAYER_QUEST_START: {
            int state = va_arg(args, int);
            quest_start(player->contr, code, state);
            *type = CFAPI_NONE;
            break;
        }
        case CFAPI_PLAYER_QUEST_GET_STATE: {
            int *ret = va_arg(args, int *);
            *ret = quest_get_player_state(player->contr, code);
            *type = CFAPI_INT;
            break;
        }
        case CFAPI_PLAYER_QUEST_SET_STATE: {
            int state = va_arg(args, int);
            quest_set_player_state(player->contr, code, state);
            *type = CFAPI_NONE;
            break;
        }
        case CFAPI_PLAYER_QUEST_WAS_COMPLETED: {
            int *ret = va_arg(args, int*);
            *ret = quest_was_completed(player->contr, code);
            *type = CFAPI_INT;
            break;
        }
        default:
            LOG(llevError, "invalid quest type: %d\n", op);
            *type = CFAPI_NONE;
    }

    va_end(args);
}
