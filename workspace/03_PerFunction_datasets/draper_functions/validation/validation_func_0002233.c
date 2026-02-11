create_isobarycenter(void)
{
    int n = 0;
    _set *set;
    _point *val;

    set = POP(_set);
    if (set == NULL) runtime_error(_("empty set"));
    get_mem(val, _point);
    val->x = 0;
    val->y = 0;
    do {
	val->x += set->p->x;
	val->y += set->p->y;
	n++;
	set = set->next;
    } while (set != NULL);
    val->x /= n;
    val->y /= n;
    PSH(val);
}
