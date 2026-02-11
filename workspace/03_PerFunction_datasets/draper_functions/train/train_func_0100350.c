__make_move(cs_obj_t *o, int wx, int wy)
{


	__move_point(&o->point, wx, wy);


	if(o->flags & CS_OBJ_DOANIM)
	{


		if((o->flags & CS_OBJ_DYING)
				&& (o->anim.cframe >> 4 == 14))
			cs_obj_free(o);

		o->anim.cframe += o->anim.aspeed;
		o->anim.cframe %= o->anim.aframes << 4;
		o->anim.frame = (o->anim.cframe >> 4) + o->anim.fframe;
	}


	if(!(o->flags & CS_OBJ_DYING) && o->fire.rate)
	{
		if(o->fire.timer > 0)
			--o->fire.timer;
		else
		{
			o->fire.timer = o->fire.rate;
			__enemy_fire(o);
			if(o->on_fire)
				o->on_fire(o);
		}
	}
}
