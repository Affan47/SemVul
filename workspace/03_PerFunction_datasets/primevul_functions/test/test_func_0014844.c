emacs_tags_file_eof(findtags_state_T *st)
{
    if (!incstack_idx)
	return FALSE;


    --incstack_idx;
    fclose(st->fp);
    st->fp = incstack[incstack_idx].fp;
    STRCPY(st->tag_fname, incstack[incstack_idx].etag_fname);
    vim_free(incstack[incstack_idx].etag_fname);
    st->is_etag = TRUE;

    return TRUE;
}
