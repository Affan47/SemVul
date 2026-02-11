Text ()
{
	ostringstream oss;
	if (stoich > 1)
		oss << stoich;
	return oss.str ();
}
