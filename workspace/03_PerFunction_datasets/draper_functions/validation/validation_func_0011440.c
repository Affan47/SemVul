player_sync() {
    int playerno;
    player_t *player = &players[0];
    for (playerno = 0; playerno < MAXPLAYERS; playerno++, player++) {
        if (!PLAYER_USED(player))
            continue;


        int newcpu = player_get_cpu_usage(player);

        if (newcpu != player->cpu_usage) {
            player->dirtymask |= PLAYER_DIRTY_CPU;
            player->cpu_usage = newcpu;
        }

        player_to_network(player, player->dirtymask, SEND_BROADCAST);
        player->dirtymask = PLAYER_DIRTY_NONE;
    }
}
