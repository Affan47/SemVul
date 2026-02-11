_hx509_request_add_eku(hx509_context context,
		       hx509_request req,
		       const heim_oid *oid)
{
    void *val;
    int ret;

    val = realloc(req->eku.val, sizeof(req->eku.val[0]) * (req->eku.len + 1));
    if (val == NULL)
	return ENOMEM;
    req->eku.val = val;

    ret = der_copy_oid(oid, &req->eku.val[req->eku.len]);
    if (ret)
	return ret;

    req->eku.len += 1;

    return 0;
}
