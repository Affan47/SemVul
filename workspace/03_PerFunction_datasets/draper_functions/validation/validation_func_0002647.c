ediMakeGrid(cchar *json)
{
    MprHash     *obj, *row;
    MprKey      *kp;
    EdiGrid     *grid;
    EdiRec      *rec;
    int         r, nrows, nfields;

    if ((obj = mprDeserialize(json)) == 0) {
        return 0;
    }
    nrows = mprGetHashLength(obj);
    if ((grid = ediCreateBareGrid(NULL, "", nrows)) == 0) {
        return 0;
    }
    for (r = 0, ITERATE_KEYS(obj, kp)) {
        if (kp->type != MPR_JSON_OBJ) {
            continue;
        }
        row = (MprHash*) kp->data;
        nfields = mprGetHashLength(row);
        if ((rec = ediCreateBareRec(NULL, "", nfields)) == 0) {
            return 0;
        }
        if (ediSetFields(rec, row) == 0) {
            return 0;
        }
        grid->records[r++] = rec;
    }
    return 0;
}
