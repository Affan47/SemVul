static int attr_cmp(const void *one, const void *two)
{
	const VALUE_PAIR * const *a = one;
	const VALUE_PAIR * const *b = two;


	if (((*a)->attribute == DHCP2ATTR(53)) &&
	    (*b)->attribute != DHCP2ATTR(53)) return -1;


	if (((*a)->attribute == DHCP2ATTR(82)) &&
	    (*b)->attribute != DHCP2ATTR(82)) return +1;

	return ((*a)->attribute - (*b)->attribute);
}
