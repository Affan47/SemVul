save_search_patterns()
{
    if (save_level++ == 0)
    {
	saved_spats[0] = spats[0];
	if (spats[0].pat != NULL)
	    saved_spats[0].pat = vim_strsave(spats[0].pat);
	saved_spats[1] = spats[1];
	if (spats[1].pat != NULL)
	    saved_spats[1].pat = vim_strsave(spats[1].pat);
	saved_last_idx = last_idx;
# ifdef FEAT_SEARCH_EXTRA
	saved_no_hlsearch = no_hlsearch;
# endif
    }
}
