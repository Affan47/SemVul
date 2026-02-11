hit(int dmg)
{
	if(_state != normal)
		return;

	if(!dmg)
		dmg = 1000;

	if(_health && (dmg < _health))
		manage.noise_damage((float)dmg / _health);
	else
		manage.noise_damage(1.0f);

	_health -= dmg;
	if(_health > 0)
		sound.g_player_damage();
	else
	{
		_health = 0;
		manage.lost_myship();
		state(dead);
		sound.g_player_explo_start();
	}
}
