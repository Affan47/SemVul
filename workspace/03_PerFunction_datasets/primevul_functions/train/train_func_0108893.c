map_clear_int(
    buf_T	*buf UNUSED,
    int		mode,
    int		local UNUSED,
    int		abbr)
{
    mapblock_T	*mp, **mpp;
    int		hash;
    int		new_hash;

    validate_maphash();

    for (hash = 0; hash < 256; ++hash)
    {
	if (abbr)
	{
	    if (hash > 0)
		break;
#ifdef FEAT_LOCALMAP
	    if (local)
		mpp = &buf->b_first_abbr;
	    else
#endif
		mpp = &first_abbr;
	}
	else
	{
#ifdef FEAT_LOCALMAP
	    if (local)
		mpp = &buf->b_maphash[hash];
	    else
#endif
		mpp = &maphash[hash];
	}
	while (*mpp != NULL)
	{
	    mp = *mpp;
	    if (mp->m_mode & mode)
	    {
		mp->m_mode &= ~mode;
		if (mp->m_mode == 0)
		{
		    map_free(mpp);
		    continue;
		}


		new_hash = MAP_HASH(mp->m_mode, mp->m_keys[0]);
		if (!abbr && new_hash != hash)
		{
		    *mpp = mp->m_next;
#ifdef FEAT_LOCALMAP
		    if (local)
		    {
			mp->m_next = buf->b_maphash[new_hash];
			buf->b_maphash[new_hash] = mp;
		    }
		    else
#endif
		    {
			mp->m_next = maphash[new_hash];
			maphash[new_hash] = mp;
		    }
		    continue;
		}
	    }
	    mpp = &(mp->m_next);
	}
    }
}
