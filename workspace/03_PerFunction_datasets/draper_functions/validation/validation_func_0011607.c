addloc(name, type)
char *name;
struct typestruct *type;
{
    struct symstruct **hashptr;
    register struct symstruct *symptr;

    hashptr = gethashptr(name);
    symptr = *hashptr;
    while (symptr != NULL)
	symptr = symptr->next;
    symptr = locptr;
    locptr = (struct symstruct *) align(&symptr->name.namea[strlen(name) + 1]);
    if (locptr >= &locsyms[MAXLOCAL])
	limiterror("too many local symbols (101)");
    addsym(name, type, symptr);
    if (type->constructor == FUNCTION)
	symptr->storage = GLOBAL;
    else
	symptr->storage = LOCAL;
    symptr->level = level;
    if (*hashptr != NULL)
    {
	symptr->next = *hashptr;
	symptr->next->prev = &symptr->next;
    }
    *hashptr = symptr;
    symptr->prev = hashptr;
    return symptr;
}
