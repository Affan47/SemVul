borg_flow_vein(bool viewable, int nearness)
{
    int i, x, y;
    int b_stair = -1, j, b_j = -1;
	int cost = 0;
	int leash = borg_skill[BI_CLEVEL] * 3 + 9;

    borg_grid *ag;


    if (!track_vein_num) return (FALSE);


	if (borg_skill[BI_CLEVEL] >= 20) leash = 250;


	if (borg_gold >= 100000) return (FALSE);


    if (!borg_spell_okay_fail(2, 2, 35) &&
		borg_items[weapon_swap].tval != TV_DIGGING) return (FALSE);


    borg_temp_n = 0;


    borg_needs_searching = TRUE;


    for (i = 0; i < track_less_num; i++)
    {
        x = track_less_x[i];
        y = track_less_y[i];


        j = distance(c_y, c_x, y, x);


        if (b_j >= j) continue;


        b_j =j;
        b_stair = i;
    }


    for (i = 0; i < track_vein_num; i++)
    {

        x = track_vein_x[i];
        y = track_vein_y[i];


        ag = &borg_grids[y][x];


        if (viewable && !(ag->info & BORG_VIEW)) continue;


		borg_flow_clear();


		cost = borg_flow_cost_stair(y,x, b_stair);


		if (nearness > 5 && cost > leash && borg_skill[BI_CLEVEL] < 20) continue;


        borg_temp_x[borg_temp_n] = x;
        borg_temp_y[borg_temp_n] = y;
        borg_temp_n++;
    }


    if (!borg_temp_n) return (FALSE);


    borg_flow_clear();


    for (i = 0; i < borg_temp_n; i++)
    {

        borg_flow_enqueue_grid(borg_temp_y[i], borg_temp_x[i]);
    }


    borg_flow_spread(nearness, TRUE, !viewable, FALSE, -1, FALSE);


    if (!borg_flow_commit("vein", GOAL_TAKE)) return (FALSE);


    if (!borg_flow_old(GOAL_TAKE)) return (FALSE);


    return (TRUE);
}
