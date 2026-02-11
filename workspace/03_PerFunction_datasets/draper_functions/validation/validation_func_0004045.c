get_tc_index(const char *descriptor, int modid)
{
    int             i;
    struct tc      *tcp;
    struct module  *mp;
    struct module_import *mip;


    for (mp = module_head; mp; mp = mp->next)
        if (mp->modid == modid)
            break;
    if (mp)
        for (i = 0, mip = mp->imports; i < mp->no_imports; ++i, ++mip) {
            if (!label_compare(mip->label, descriptor)) {


                modid = mip->modid;
                break;
            }
        }


    for (i = 0, tcp = tclist; i < MAXTC; i++, tcp++) {
        if (tcp->type == 0)
            break;
        if (!label_compare(descriptor, tcp->descriptor) &&
            ((modid == tcp->modid) || (modid == -1))) {
            return i;
        }
    }
    return -1;
}
