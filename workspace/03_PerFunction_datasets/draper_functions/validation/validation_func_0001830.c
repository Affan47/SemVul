test_hit(int chance, int ac, int vis)
{
	int k;


	k = randint0(100);


	if (k < 10) return (k < 5);


	if (!vis) chance = chance / 2;


	if ((chance > 0) && (randint0(chance) >= (ac * 3 / 4))) return (TRUE);


	return (FALSE);
}
