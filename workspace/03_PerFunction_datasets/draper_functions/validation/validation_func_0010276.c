reset_func(piece_info_t *obj)
{
    city_info_t *cityp;

    cityp = find_city (obj->loc);

    if (cityp != NULL)
	if (cityp->func[obj->type] != NOFUNC) {
	    obj->func = cityp->func[obj->type];
	    (void) awake (obj);
	}
}
