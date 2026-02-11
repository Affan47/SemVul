print_xml_array(MWK_REQ_CTXT *rc, const char *tag,
                const apr_array_header_t *array)
{
    int i;
    const char *string;

    if (array == NULL)
        return;

    for (i = 0; i < array->nelts; i++) {
        string = APR_ARRAY_IDX(array, i, const char *);
        string = apr_xml_quote_string(rc->r->pool, string, false);
        ap_rprintf(rc->r, "<%s>%s</%s>", tag, string, tag);
    }
}
