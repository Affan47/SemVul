PyHTTPResponseParser_parser_failed(PyHTTPResponseParser* self)
{
    if (self->parser->http_errno != HPE_OK) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}
