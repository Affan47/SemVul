handle_multi(request_rec *r)
{
    negotiation_state *neg;
    var_rec *best, *avail_recs;
    request_rec *sub_req;
    int res;
    int j;

    if (r->finfo.filetype != APR_NOFILE
        || !(ap_allow_options(r) & OPT_MULTI)) {
        return DECLINED;
    }

    neg = parse_accept_headers(r);

    if ((res = read_types_multi(neg))) {
      return_from_multi:

        avail_recs = (var_rec *) neg->avail_vars->elts;
        for (j = 0; j < neg->avail_vars->nelts; ++j) {
            var_rec *variant = &avail_recs[j];
            if (variant->sub_req) {
                ap_destroy_sub_req(variant->sub_req);
            }
        }
        return res;
    }
    if (neg->avail_vars->nelts == 0) {
        return DECLINED;
    }

    res = do_negotiation(r, neg, &best,
                         (r->method_number != M_GET) || r->args ||
                         (r->path_info && *r->path_info));
    if (res != 0)
        goto return_from_multi;

    if (!(sub_req = best->sub_req)) {


        sub_req = ap_sub_req_lookup_file(best->file_name, r, r->output_filters);
        if (sub_req->status != HTTP_OK) {
            res = sub_req->status;
            ap_destroy_sub_req(sub_req);
            goto return_from_multi;
        }
    }
    if (sub_req->args == NULL) {
        sub_req->args = r->args;
    }


    ap_internal_fast_redirect(sub_req, r);


    r->mtime = 0;


    avail_recs = (var_rec *) neg->avail_vars->elts;
    for (j = 0; j < neg->avail_vars->nelts; ++j) {
        var_rec *variant = &avail_recs[j];
        if (variant != best && variant->sub_req) {
            ap_destroy_sub_req(variant->sub_req);
        }
    }
    return OK;
}
