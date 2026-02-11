kcm_ccache_new(krb5_context context,
	       const char *name,
	       kcm_ccache *ccache)
{
    krb5_error_code ret;

    ret = kcm_ccache_alloc(context, name, ccache);
    if (ret == 0) {


	kcm_retain_ccache(context, *ccache);
    }

    return ret;
}
