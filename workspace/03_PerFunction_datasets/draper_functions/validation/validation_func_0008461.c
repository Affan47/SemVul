A_SkullRodStorm(mobj_t * actor)
{
    fixed_t x;
    fixed_t y;
    mobj_t *mo;
    int playerNum;
    player_t *player;

    if (actor->health-- == 0)
    {
        P_SetMobjState(actor, S_NULL);
        playerNum = netgame ? actor->special2.i : 0;
        if (!playeringame[playerNum])
        {
            return;
        }
        player = &players[playerNum];
        if (player->health <= 0)
        {
            return;
        }
        if (player->rain1 == actor)
        {
            player->rain1 = NULL;
        }
        else if (player->rain2 == actor)
        {
            player->rain2 = NULL;
        }
        return;
    }
    if (P_Random() < 25)
    {
        return;
    }
    x = actor->x + ((P_Random() & 127) - 64) * FRACUNIT;
    y = actor->y + ((P_Random() & 127) - 64) * FRACUNIT;
    mo = P_SpawnMobj(x, y, ONCEILINGZ, MT_RAINPLR1 + actor->special2.i);
    mo->target = actor->target;
    mo->momx = 1;
    mo->momz = -mo->info->speed;
    mo->special2.i = actor->special2.i;
    P_CheckMissileSpawn(mo);
    if (!(actor->special1.i & 31))
    {
        S_StartSound(actor, sfx_ramrain);
    }
    actor->special1.i++;
}
