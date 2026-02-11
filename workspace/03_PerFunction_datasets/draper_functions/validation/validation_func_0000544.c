EscapeFromObstacle(float *posX, float *posY, int posZ, colldet_filter * filter)
{
	int start_x, end_x, start_y, end_y;
	int x, y, i, obst_index;
	Level ThisLevel;

	start_x = (int)(*posX) - 2;
	start_y = (int)(*posY) - 2;
	end_x = start_x + 4;
	end_y = start_y + 4;

	ThisLevel = curShip.AllLevels[posZ];

	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (end_x >= ThisLevel->xlen)
		end_x = ThisLevel->xlen - 1;
	if (end_y >= ThisLevel->ylen)
		end_y = ThisLevel->ylen - 1;

	for (y = start_y; y < end_y; ++y) {
		for (x = start_x; x < end_x; ++x) {
			for (i = 0; i < ThisLevel->map[y][x].glued_obstacles.size; i++) {
				int *glued_obstacles = ThisLevel->map[y][x].glued_obstacles.arr;

				obst_index = glued_obstacles[i];

				obstacle *our_obs = &(ThisLevel->obstacle_list[obst_index]);

				if (filter && filter->callback(filter, our_obs, obst_index))
					continue;


				obstacle_spec *obstacle_spec = get_obstacle_spec(our_obs->type);
				if (obstacle_spec->block_area_type == COLLISION_TYPE_NONE)
					continue;


				if ((*posX > our_obs->pos.x + obstacle_spec->left_border) &&
				    (*posX < our_obs->pos.x + obstacle_spec->right_border) &&
				    (*posY > our_obs->pos.y + obstacle_spec->upper_border) &&
				    (*posY < our_obs->pos.y + obstacle_spec->lower_border)) {

					return MoveOutOfObstacle(posX, posY, posZ, our_obs, filter);
				}
			}
		}
	}

	return FALSE;
}
