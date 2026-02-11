get_resize_decor_gravities_one_axis(
	frame_decor_gravities_type *ret_grav, direction_t title_dir,
	frame_move_resize_mode axis_mode, direction_t neg_dir,
	direction_t pos_dir, int is_moving)
{

	int title_grav;
	int neg_grav;
	int pos_grav;

	title_grav = gravity_dir_to_grav(title_dir);
	neg_grav = gravity_dir_to_grav(neg_dir);
	pos_grav = gravity_dir_to_grav(pos_dir);
	if (title_dir != DIR_NONE)
	{
		ret_grav->decor_grav = title_grav;
		ret_grav->lbutton_grav = title_grav;
		ret_grav->title_grav = title_grav;
		ret_grav->rbutton_grav = title_grav;
	}
	else
	{
		ret_grav->decor_grav = neg_grav;
		ret_grav->lbutton_grav = neg_grav;
		ret_grav->title_grav = neg_grav;
		ret_grav->rbutton_grav = pos_grav;
	}
	switch (axis_mode)
	{
	case FRAME_MR_SCROLL:
		ret_grav->client_grav = (is_moving) ? neg_grav : pos_grav;
		break;
	case FRAME_MR_SHRINK:
		ret_grav->client_grav = (is_moving) ? pos_grav : neg_grav;
		break;
	case FRAME_MR_OPAQUE:
	case FRAME_MR_FORCE_SETUP:
	case FRAME_MR_FORCE_SETUP_NO_W:
	case FRAME_MR_SETUP:
	case FRAME_MR_SETUP_BY_APP:
		ret_grav->client_grav = neg_grav;
		break;
	case FRAME_MR_DONT_DRAW:

		break;
	}
	ret_grav->parent_grav = ret_grav->client_grav;

	return;
}
