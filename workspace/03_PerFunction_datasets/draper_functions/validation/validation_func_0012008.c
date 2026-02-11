vd_query_destroy (VDQuery* vd_query)
{
	if (!vd_query)
		return;

	free (vd_query->_search_term);
	buffer_destroy (vd_query->_result_buffer);

	free (HTTP_PROXY_HOST);
	HTTP_PROXY_HOST = NULL;

	free (vd_query);
}
