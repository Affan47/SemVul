mon_in_region(NhRegion *reg, struct monst *mon)
{
    int i;

    for (i = 0; i < reg->n_monst; i++)
            if (reg->monsters[i] == mon->m_id)
                    return true;
    return false;
}
