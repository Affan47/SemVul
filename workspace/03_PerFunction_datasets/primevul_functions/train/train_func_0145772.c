signed_time_secs_to_str_buf(gint32 time_val, const guint32 frac,
    const gboolean is_nsecs, wmem_strbuf_t *buf)
{
	if(time_val < 0){
		wmem_strbuf_append_printf(buf, "-");
		if(time_val == G_MININT32) {


			unsigned_time_secs_to_str_buf(G_MAXUINT32, frac,
			    is_nsecs, buf);
		} else {


			unsigned_time_secs_to_str_buf(-time_val, frac,
			    is_nsecs, buf);
		}
	} else
		unsigned_time_secs_to_str_buf(time_val, frac, is_nsecs, buf);
}
