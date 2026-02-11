H5ST_search(H5ST_tree_t *tree, const char *s)
{
    H5ST_ptr_t p;
    htri_t ret_value=FALSE;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    p = tree->root;
    while (p) {
        if (*s < p->splitchar)
            p = p->lokid;
        else if (*s == p->splitchar)  {
            if (*s++ == 0)
                HGOTO_DONE(TRUE);
            p = p->eqkid;
        } else
            p = p->hikid;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
