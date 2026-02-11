multipart_buffer_read_body(multipart_buffer *self)
{
    char buf[FILLUNIT], *out = "";

    while(multipart_buffer_read(self, buf, sizeof(buf)))
	out = (char*) apr_pstrcat(self->r->pool, out, buf, NULL);

#ifdef DEBUG
    ap_log_rerror(MPB_ERROR, "multipart_buffer_read_body: '%s'", out);
#endif

    return out;
}
