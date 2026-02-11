push_LT(gxml_data * xd)
{
    giiLabelTable * lt = &xd->gim->labeltable;

    if( lt->length || lt->key || lt->label ) {
        fprintf(stderr,"** multiple giiLabelTables?\n");
    }

    return 0;
}
