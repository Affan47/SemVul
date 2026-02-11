rbthash_comparator (void *entry1, void *entry2, void *param)
{
        int             ret = 0;
        rbthash_entry_t *e1 = NULL;
        rbthash_entry_t *e2 = NULL;

        if ((!entry1) || (!entry2) || (!param))
                return -1;

        e1 = (rbthash_entry_t *)entry1;
        e2 = (rbthash_entry_t *)entry2;

        if (e1->keylen != e2->keylen) {
                if (e1->keylen < e2->keylen)
                        ret = -1;
                else if (e1->keylen > e2->keylen)
                        ret = 1;
        } else
                ret = memcmp (e1->key, e2->key, e1->keylen);

        return ret;
}
