go_fake_floorl (long double x)
{
	if (x == floorl (x))
		return x;

	return (x >= 0)
		? floorl (go_add_epsilonl (x))
		: floorl (go_sub_epsilonl (x));
}
