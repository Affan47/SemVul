createCol(MdbTable *table, cchar *columnName)
{
    MdbSchema    *schema;
    MdbCol       *col;

    if ((col = lookupColumn(table, columnName)) != 0) {
        return 0;
    }
    if ((schema = growSchema(table)) == 0) {
        return 0;
    }
    col = &schema->cols[schema->ncols];
    col->cid = schema->ncols++;
    col->name = sclone(columnName);
    return col;
}
