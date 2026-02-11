ath6kl_dbg_dump(enum ATH6K_DEBUG_MASK mask,
		     const char *msg, const char *prefix,
		     const void *buf, size_t len)
{
	if (debug_mask & mask) {
		if (msg)
			ath6kl_dbg(mask, "%s\n", msg);

		print_hex_dump_bytes(prefix, DUMP_PREFIX_OFFSET, buf, len);
	}


	trace_ath6kl_log_dbg_dump(msg ? msg : "", prefix ? prefix : "",
				  buf, len);
}
