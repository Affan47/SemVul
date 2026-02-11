user_dir_fighter(piece_info_t *obj, loc_t loc)
{
    if (map[loc].contents == MAP_CITY)
	fatal (obj, loc,
	       "That's never worked before, sir.  Do you really want to try? ",
	       "Your fighter was shot down.");

    else if (isupper (user_map[loc].contents)) {
	if (!getyn ("Sir, those are our men!  "
		    "Do you really want to attack them? "))
	    return;

	attack (obj, loc);
    }

    else attack (obj, loc);
}
