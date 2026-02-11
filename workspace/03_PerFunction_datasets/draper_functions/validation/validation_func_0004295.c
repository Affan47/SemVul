check_contained(container, mesg)
    struct obj *container;
    const char *mesg;
{
    struct obj *obj;
    char obj1_address[20], obj2_address[20];

    for (obj = container->cobj; obj; obj = obj->nobj) {
	if (obj->where != OBJ_CONTAINED)
	    pline("contained %s obj %s: %s\n", mesg,
		fmt_ptr((genericptr_t)obj, obj1_address),
		where_name(obj->where));
	else if (obj->ocontainer != container)
	    pline("%s obj %s not in container %s\n", mesg,
		fmt_ptr((genericptr_t)obj, obj1_address),
		fmt_ptr((genericptr_t)container, obj2_address));
    }
}
