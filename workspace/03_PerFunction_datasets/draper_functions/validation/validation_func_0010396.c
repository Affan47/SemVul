fireball_wormhole_intensity( object *obj )
{
	int			num, objnum;
	fireball		*fb;

	num = obj->instance;
	objnum = OBJ_INDEX(obj);
	Assertion( Fireballs[num].objnum == objnum, "Basic sanity check. Fireballs[num].objnum (%d) should == objnum (%d)", Fireballs[num].objnum, objnum );

	fb = &Fireballs[num];

	float t = fb->time_elapsed;
	float rad;

	if ( t < WARPHOLE_GROW_TIME )	{
		rad = (float)pow(t/WARPHOLE_GROW_TIME,0.4f);
	} else if ( t < fb->total_time - WARPHOLE_GROW_TIME )	{
		rad = 1;
	} else {
		rad = (float)pow((fb->total_time - t)/WARPHOLE_GROW_TIME,0.4f);
	}
	return rad;
}
