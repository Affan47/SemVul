save_re_pat(int idx, char_u *pat, int magic)
{
    if (spats[idx].pat != pat)
    {
	vim_free(spats[idx].pat);
	spats[idx].pat = vim_strsave(pat);
	spats[idx].magic = magic;
	spats[idx].no_scs = no_smartcase;
	last_idx = idx;
#ifdef FEAT_SEARCH_EXTRA

	if (p_hls)
	    redraw_all_later(SOME_VALID);
	set_no_hlsearch(FALSE);
#endif
    }
}
