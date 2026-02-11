new_hscent(STRPTR newid) {
    HSCENT *newent = (HSCENT*) umalloc(sizeof(HSCENT));

#if DEBUG_ENTITY
    fprintf(stderr, DHL "   new_enty %s\n", newid);
#endif

    if (newent) {

       newent->name = strclone(newid);
       newent->replace[0] = newent->replace[1] = '\0';
       newent->numeric = 0;
       newent->flags = 0;
    }
    return (newent);
}
