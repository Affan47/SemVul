keydb_insert_keyblock (KEYDB_HANDLE hd, KBNODE kb)
{
    int rc = -1;
    int idx;

    if (!hd)
        return G10ERR_INV_ARG;

    if( opt.dry_run )
	return 0;

    if ( hd->found >= 0 && hd->found < hd->used)
        idx = hd->found;
    else if ( hd->current >= 0 && hd->current < hd->used)
        idx = hd->current;
    else
        return G10ERR_GENERAL;

    rc = lock_all (hd);
    if (rc)
        return rc;

    switch (hd->active[idx].type) {
      case KEYDB_RESOURCE_TYPE_NONE:
        rc = G10ERR_GENERAL;
        break;
      case KEYDB_RESOURCE_TYPE_KEYRING:
        rc = keyring_insert_keyblock (hd->active[idx].u.kr, kb);
        break;
    }

    unlock_all (hd);
    return rc;
}
