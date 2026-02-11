next_month()
{


	int newShouldSetPower = get_should_set_power();

	if( newShouldSetPower == should_set_power )
		return;

	if( should_set_power )
		world.restore_power(loc_x1, loc_y1, loc_x2, loc_y2, 0, firm_recno);

	should_set_power = newShouldSetPower;

	if( should_set_power )
		world.set_power(loc_x1, loc_y1, loc_x2, loc_y2, nation_recno);
}
