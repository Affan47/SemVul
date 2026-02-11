init_objects(void) {
#ifndef MEMORY_DEBUG
    int i;
#endif

    objects = NULL;
    active_objects = NULL;

#ifdef MEMORY_DEBUG
    free_objects = NULL;
#else
    free_objects = objarray;
    objarray[0].prev = NULL,
    objarray[0].next = &objarray[1],
    SET_FLAG(&objarray[0], FLAG_REMOVED);
    SET_FLAG(&objarray[0], FLAG_FREED);
    for (i = 1; i < STARTMAX-1; i++) {
        objarray[i].next = &objarray[i+1];
        objarray[i].prev = &objarray[i-1];
        SET_FLAG(&objarray[i], FLAG_REMOVED);
        SET_FLAG(&objarray[i], FLAG_FREED);
    }
    objarray[STARTMAX-1].next = NULL;
    objarray[STARTMAX-1].prev = &objarray[STARTMAX-2];
    SET_FLAG(&objarray[STARTMAX-1], FLAG_REMOVED);
    SET_FLAG(&objarray[STARTMAX-1], FLAG_FREED);
#endif
}
