get_container_location(struct obj *obj,
                       int *loc,
                       int *container_nesting)
{
    if (!obj || !loc)
            return 0;

    if (container_nesting) *container_nesting = 0;
    while (obj && obj->where == OBJ_CONTAINED)
    {
        if (container_nesting) *container_nesting += 1;
        obj = obj->ocontainer;
    }
    if (obj)
    {
        *loc = obj->where;
        if (obj->where == OBJ_MINVENT) return obj->ocarry;
    }
    return (struct monst *)0;
}
