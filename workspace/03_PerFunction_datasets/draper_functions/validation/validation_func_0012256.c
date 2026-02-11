free_all_objects(mapstruct *m) {
    int i, j;
    object *op;

    for (i = 0; i < MAP_WIDTH(m); i++)
        for (j = 0; j < MAP_HEIGHT(m); j++) {
            object *previous_obj = NULL;

            while ((op = GET_MAP_OB(m, i, j)) != NULL) {
                if (op == previous_obj) {
                    LOG(llevDebug, "free_all_objects: Link error, bailing out.\n");
                    break;
                }
                previous_obj = op;
                op = HEAD(op);


                if (m->in_memory == MAP_IN_MEMORY)
                    clean_object(op);
                object_remove(op);
                object_free_drop_inventory(op);
            }
        }
#ifdef MANY_CORES


    for (op = objects; op != NULL; op = op->next) {
        if (!QUERY_FLAG(op, FLAG_REMOVED) && op->map == m) {
            LOG(llevDebug, "free_all_objects: object %s still on map after it should have been freed\n", op->name);
            abort();
        }
    }
#endif
}
