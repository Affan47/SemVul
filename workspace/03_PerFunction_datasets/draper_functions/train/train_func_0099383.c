nibble(int tool)
{
	int i;
	int x[NIBBLE_TILES];
	int y[NIBBLE_TILES];

	mode(DASHBOARD_OFF);

	if(tool < 0)
		tool = (pubrand.get(20) + SDL_GetTicks()) % 5;


	for(i = 0; i < NIBBLE_TILES; ++i)
		x[i] = y[i] = -1;


	int ind = 0;
	int xx = -NIBBLE_W / 2;
	int yy = -NIBBLE_H / 2;
	for(i = 0; i < NIBBLE_TILES; ++i)
	{
		ind = pubrand.get() % NIBBLE_TILES;
		if(ind >= NIBBLE_TILES)
			ind = 0;
		while(x[ind] != -1)
			if(++ind >= NIBBLE_TILES)
				ind = 0;
		x[ind] = xx;
		y[ind] = yy;
		xx += NIBBLE_W;
		if(xx >= SCREEN_WIDTH + NIBBLE_W / 2)
		{
			xx = -NIBBLE_W / 2;
			yy += NIBBLE_H;
		}
	}


	foreground(map_rgb(0x000000));
	ind = 0;
	int last_index;
	int t = SDL_GetTicks();
	while(ind < NIBBLE_TILES)
	{
		int nt = SDL_GetTicks();
		int dt = nt - t;
		t = nt;
		last_index = ind;
		for(i = 0; i < dt * 8; ++i)
		{
			if(ind >= NIBBLE_TILES)
				break;
			switch (tool)
			{
			  case 0:
				fillrect(x[ind] + NIBBLE_W / 2,
						y[ind] + NIBBLE_H / 2,
						NIBBLE_W, NIBBLE_H);
				break;
			  default:
				sprite(x[ind] - 8 + NIBBLE_W / 2,
						y[ind] - 8 +
						NIBBLE_H / 2, B_BRUSHES,
						tool - 1);
				break;
			}
			++ind;
		}
		gengine->invalidate();
		gengine->flip();
		if(gengine->doublebuffer())
		{
			for(i = 0; i < dt * 4; ++i)
			{
				if(last_index >= NIBBLE_TILES)
					break;
				switch (tool)
				{
				  case 0:
					fillrect(x[last_index] +
							NIBBLE_W / 2,
							y[last_index] +
							NIBBLE_H / 2,
							NIBBLE_W,
							NIBBLE_H);
					break;
				  default:
					sprite(x[last_index] - 8 +
							NIBBLE_W / 2,
							y[last_index] - 8 +
							NIBBLE_H / 2,
							B_BRUSHES,
							tool - 1);
					break;
				}
				++last_index;
			}
		}
	}
	mode(DASHBOARD_BLACK);
	gengine->flip();
}
