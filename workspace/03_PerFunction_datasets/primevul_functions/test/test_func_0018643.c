static void phys_page_compact(struct uc_struct *uc, PhysPageEntry *lp, Node *nodes)
{
    unsigned valid_ptr = P_L2_SIZE;
    int valid = 0;
    PhysPageEntry *p;
    int i;

    if (lp->ptr == PHYS_MAP_NODE_NIL) {
        return;
    }

    p = nodes[lp->ptr];
    for (i = 0; i < P_L2_SIZE; i++) {
        if (p[i].ptr == PHYS_MAP_NODE_NIL) {
            continue;
        }

        valid_ptr = i;
        valid++;
        if (p[i].skip) {
            phys_page_compact(uc, &p[i], nodes);
        }
    }


    if (valid != 1) {
        return;
    }

    assert(valid_ptr < P_L2_SIZE);


    if (P_L2_LEVELS >= (1 << 6) &&
        lp->skip + p[valid_ptr].skip >= (1 << 6)) {
        return;
    }

    lp->ptr = p[valid_ptr].ptr;
    if (!p[valid_ptr].skip) {


        lp->skip = 0;
    } else {
        lp->skip += p[valid_ptr].skip;
    }
}
