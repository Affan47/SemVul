clear_struct1(misc5_struct1 *buf)
{
    unsigned i;

    for(i=0;i<buf->st1_el2.len;i++)
        clear_struct2(&((( misc5_struct2 *)(buf->st1_el2.p))[i]));
    HDfree(buf->st1_el2.p);
}
