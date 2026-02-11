DFdinobj(int32 list)
{
    CONSTR(FUNC, "DFdinobj");
    DIlist_ptr  list_rec;

    list_rec = GID2REC(list);

    if (!list_rec)
        HRETURN_ERROR(DFE_ARGS, FAIL);

    return (list_rec->num);
}
