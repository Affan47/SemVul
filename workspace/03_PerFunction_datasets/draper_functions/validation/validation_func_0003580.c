beam_get_cull_vals(object *objp, beam *b, float *cull_dot, float *cull_dist)
{
	switch(objp->type){


	case OBJ_DEBRIS:
	case OBJ_ASTEROID:
		*cull_dot = 1.0f - ((1.0f - beam_get_cone_dot(b)) * 1.10f);
		*cull_dist = 50.0f * 50.0f;
		return;


	case OBJ_WEAPON:
		*cull_dot = 1.0f - ((1.0f - beam_get_cone_dot(b)) * 1.5f);
		*cull_dist = 300.0f * 300.0f;
		return;

	case OBJ_SHIP:


		if(Ship_info[Ships[objp->instance].ship_info_index].flags & (SIF_BIG_SHIP | SIF_HUGE_SHIP)){
			*cull_dot = 1.0f - ((1.0f - beam_get_cone_dot(b)) * 1.25f);

			*cull_dist = (objp->radius * 1.3f) * (objp->radius * 1.3f);
			return;
		}


		*cull_dot = 1.0f - ((1.0f - beam_get_cone_dot(b)) * 1.5f);
		*cull_dist = 300.0f * 300.0f;
		return;
	}


	Int3();
	*cull_dot = 1.0f;
	*cull_dist = 0.0f;
	return;
}
