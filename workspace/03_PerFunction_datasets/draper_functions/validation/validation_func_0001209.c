moveStar( struct state *st, starline * stl )
{

	stl->begin.Z -= st->z_speed;
	stl->end.Z -= st->z_speed;

	calcStar( &stl->begin );
	calcStar( &stl->end );

	return ( stl->begin.Z <= 0 || stl->end.Z <= 0 );

}
