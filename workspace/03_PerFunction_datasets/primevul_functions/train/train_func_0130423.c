p_b_symbol(p)
register struct parse *p;
{
	register char value;

	if(REQUIRE(MORE(), REG_EBRACK)) {}
	if (!EATTWO('[', '.'))
		return(GETNEXT());


	value = p_b_coll_elem(p, '.');
	if(REQUIRE(EATTWO('.', ']'), REG_ECOLLATE)) {}
	return(value);
}
