uint32_t ldb_req_get_custom_flags(struct ldb_request *req)
{
	if (req != NULL && req->handle != NULL) {
		return req->handle->custom_flags;
	}


	return 0;
}
