glusterd_is_rb_ongoing (glusterd_volinfo_t *volinfo)
{
        gf_boolean_t     ret = _gf_false;

        GF_ASSERT (volinfo);

        if (glusterd_is_rb_started (volinfo) ||
            glusterd_is_rb_paused (volinfo))
                ret = _gf_true;

        return ret;
}
