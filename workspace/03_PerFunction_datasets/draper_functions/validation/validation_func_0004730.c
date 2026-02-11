hud_lock_on_subsys_ok()
{
	ship_subsys		*subsys;
	vec3d			subobj_pos;
	object			*target_objp;
	int				in_sight=0;

	Assert(Player_ai->target_objnum >= 0);
	target_objp	= &Objects[Player_ai->target_objnum];

	subsys = Player_ai->targeted_subsys;
	if ( !subsys ) {
		return 0;
	}

	vm_vec_unrotate(&subobj_pos, &subsys->system_info->pnt, &target_objp->orient);
	vm_vec_add2(&subobj_pos, &target_objp->pos);

	if ( Player->subsys_in_view < 0 ) {
		in_sight = ship_subsystem_in_sight(target_objp, subsys, &View_position, &subobj_pos);
	} else {
		in_sight = Player->subsys_in_view;
	}

	return in_sight;
}
