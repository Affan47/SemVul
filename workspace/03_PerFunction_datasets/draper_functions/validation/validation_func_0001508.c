autopick(olist, follow, pick_list)
struct obj *olist;
int follow;
menu_item **pick_list;
{
	menu_item *pi;
	struct obj *curr;
	int n;
	const char *otypes = flags.pickup_types;


	for (n = 0, curr = olist; curr; curr = FOLLOW(curr, follow))


#ifndef AUTOPICKUP_EXCEPTIONS
	    if (!*otypes || index(otypes, curr->oclass))
#else
	    if ((!*otypes || index(otypes, curr->oclass) ||
		 is_autopickup_exception(curr, TRUE)) &&
	    	 !is_autopickup_exception(curr, FALSE))
#endif
		n++;

	if (n) {
	    *pick_list = pi = (menu_item *) alloc(sizeof(menu_item) * n);
	    for (n = 0, curr = olist; curr; curr = FOLLOW(curr, follow))
#ifndef AUTOPICKUP_EXCEPTIONS
		if (!*otypes || index(otypes, curr->oclass)) {
#else
	    if ((!*otypes || index(otypes, curr->oclass) ||
		 is_autopickup_exception(curr, TRUE)) &&
	    	 !is_autopickup_exception(curr, FALSE)) {
#endif
		    pi[n].item.a_obj = curr;
		    pi[n].count = curr->quan;
		    n++;
		}
	}
	return n;
}
