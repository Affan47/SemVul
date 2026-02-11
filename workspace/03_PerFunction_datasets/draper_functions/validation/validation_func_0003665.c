gf_clock_find(GF_List *Clocks, u16 clockID, u16 ES_ID)
{
	u32 i;
	GF_Clock *tmp;
	i=0;
	while ((tmp = (GF_Clock *)gf_list_enum(Clocks, &i))) {

		if (tmp->clockID == clockID) return tmp;

		if (ES_ID && (tmp->clockID == ES_ID)) return tmp;
	}

	return NULL;
}
