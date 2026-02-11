PT_add_to_chain(PTM2 *ptmain, POS_TREE *node, int name, int apos, int rpos)
{
    static char buffer[100];
    unsigned long old_first;
    char *data;
    int mainapos;
    data = (&node->data) + ptmain->mode;
    if (node->flags&1){
        PT_READ_INT(data,mainapos);
        data += 4;
    }else{
        PT_READ_SHORT(data,mainapos);
        data += 2;
    }
    PT_READ_PNTR(data,old_first);
    char *p;
    p = buffer;
    PT_WRITE_PNTR(p,old_first);
    p+= sizeof(PT_PNTR);
    PT_WRITE_NAT(p,name);
    PT_WRITE_NAT(p,rpos);
    PT_WRITE_NAT(p,apos);
    int size = p - buffer;
    p = (char *)PTM_get_mem(size);
    memcpy(p,buffer,size);
    PT_WRITE_PNTR(data,p);
    psg.stat.cut_offs ++;
    return NULL;
}
