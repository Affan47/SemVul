Map_Insert(Crossfire_Map *map, PyObject *args) {
    int x, y;
    Crossfire_Object *what;

    if (!PyArg_ParseTuple(args, "O!ii", &Crossfire_ObjectType, &what, &x, &y))
        return NULL;

    MAPEXISTCHECK(map);


    ensure_map_in_memory(map);

    return Crossfire_Object_wrap(cf_map_insert_object(map->map, what->obj, x, y));
}
