luname_lookup(const char * name)
{
	const char	*cp;
	unsigned  sum = 0;
	const struct  uhash  *hp;

	if  (!doneit)
		rpwfile();
	cp = name;
	while  (*cp)
		sum += *cp++;
	hp = unhash[sum % HASHMOD];
	while  (hp)  {
		if  (strcmp(name, hp->pwh_name) == 0)
			return  hp;
		hp = hp->pwu_next;
	}
	return  (struct uhash *) 0;
}
