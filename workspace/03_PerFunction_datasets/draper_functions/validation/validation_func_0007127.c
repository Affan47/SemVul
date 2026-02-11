gx_char_cache_alloc(gs_memory_t * struct_mem, gs_memory_t * bits_mem,
            gs_font_dir * pdir, uint bmax, uint mmax, uint cmax, uint upper)
{
    uint chsize = (cmax + (cmax >> 1)) | 31;
    cached_fm_pair *mdata;
    cached_char **chars;


    chsize = max(chsize, ROUND_UP(bmax, sizeof_cached_char) / sizeof_cached_char + 1);


    while (chsize & (chsize + 1))
        chsize |= chsize >> 1;
    chsize++;
    mdata = gs_alloc_struct_array(struct_mem, mmax, cached_fm_pair,
                                  &st_cached_fm_pair_element,
                                  "font_dir_alloc(mdata)");
    chars = gs_alloc_struct_array(struct_mem, chsize, cached_char *,
                                  &st_cached_char_ptr_element,
                                  "font_dir_alloc(chars)");
    if (mdata == 0 || chars == 0) {
        gs_free_object(struct_mem, chars, "font_dir_alloc(chars)");
        gs_free_object(struct_mem, mdata, "font_dir_alloc(mdata)");
        return_error(gs_error_VMerror);
    }
    pdir->fmcache.mmax = mmax;
    pdir->fmcache.mdata = mdata;
    memset(mdata, 0, mmax * sizeof(*mdata));
    memset(chars, 0, chsize * sizeof(*chars));
    pdir->ccache.struct_memory = struct_mem;
    pdir->ccache.bits_memory = bits_mem;
    pdir->ccache.bmax = bmax;
    pdir->ccache.cmax = cmax;
    pdir->ccache.lower = upper / 10;
    pdir->ccache.upper = upper;
    pdir->ccache.table = chars;
    pdir->ccache.table_mask = chsize - 1;
    return gx_char_cache_init(pdir);
}
