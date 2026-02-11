teleport_player(int dis)
{
	int py = p_ptr->py;
	int px = p_ptr->px;

	int d, i, min, y, x;

	bool look = TRUE;


	y = py;
	x = px;


	min = dis / 2;


	while (look)
	{

		if (dis > 200) dis = 200;


		for (i = 0; i < 500; i++)
		{

			while (1)
			{
				y = rand_spread(py, dis);
				x = rand_spread(px, dis);
				d = distance(py, px, y, x);
				if ((d >= min) && (d <= dis)) break;
			}


			if (!in_bounds_fully(y, x)) continue;


			if (!cave_naked_bold(y, x)) continue;


			if (cave->info[y][x] & (CAVE_ICKY)) continue;


			look = FALSE;


			break;
		}


		dis = dis * 2;


		min = min / 2;
	}


	sound(MSG_TELEPORT);


	monster_swap(py, px, y, x);


	handle_stuff(p_ptr);
}
