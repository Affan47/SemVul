stripe_fill_pathinfo_xattr (xlator_t *this, stripe_local_t *local,
                            char **xattr_serz)
{
        int      ret             = -1;
        int32_t  padding         = 0;
        int32_t  tlen            = 0;
        char stripe_size_str[20] = {0,};
        char    *pathinfo_serz   = NULL;

        if (!local) {
                gf_log (this->name, GF_LOG_ERROR, "Possible NULL deref");
                goto out;
        }

        (void) snprintf (stripe_size_str, 20, "%ld",
                         (local->fctx) ? local->fctx->stripe_size : 0);


        padding = strlen (this->name) + strlen (STRIPE_PATHINFO_HEADER)
                + strlen (stripe_size_str) + 7;
        local->xattr_total_len += (padding + 2);

        pathinfo_serz = GF_CALLOC (local->xattr_total_len, sizeof (char),
                                   gf_common_mt_char);
        if (!pathinfo_serz)
                goto out;


        (void) sprintf (pathinfo_serz, "(<"STRIPE_PATHINFO_HEADER"%s:[%s]> ",
                        this->name, stripe_size_str);

        ret = stripe_xattr_aggregate (pathinfo_serz + padding, local, &tlen);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR,
                        "Cannot aggregate pathinfo list");
                goto out;
        }

        *(pathinfo_serz + padding + tlen) = ')';
        *(pathinfo_serz + padding + tlen + 1) = '\0';

        *xattr_serz = pathinfo_serz;

        ret = 0;
 out:
        return ret;
}
