char *pointer(const char *fmt, char *buf, char *end, void *ptr,
	      struct printf_spec spec)
{
	const int default_width = 2 * sizeof(void *);

	if (!ptr && *fmt != 'K' && *fmt != 'x') {


		if (spec.field_width == -1)
			spec.field_width = default_width;
		return string(buf, end, "(null)", spec);
	}

	switch (*fmt) {
	case 'F':
	case 'f':
	case 'S':
	case 's':
		ptr = dereference_symbol_descriptor(ptr);

	case 'B':
		return symbol_string(buf, end, ptr, spec, fmt);
	case 'R':
	case 'r':
		return resource_string(buf, end, ptr, spec, fmt);
	case 'h':
		return hex_string(buf, end, ptr, spec, fmt);
	case 'b':
		switch (fmt[1]) {
		case 'l':
			return bitmap_list_string(buf, end, ptr, spec, fmt);
		default:
			return bitmap_string(buf, end, ptr, spec, fmt);
		}
	case 'M':
	case 'm':


		return mac_address_string(buf, end, ptr, spec, fmt);
	case 'I':


	case 'i':


		switch (fmt[1]) {
		case '6':
			return ip6_addr_string(buf, end, ptr, spec, fmt);
		case '4':
			return ip4_addr_string(buf, end, ptr, spec, fmt);
		case 'S': {
			const union {
				struct sockaddr		raw;
				struct sockaddr_in	v4;
				struct sockaddr_in6	v6;
			} *sa = ptr;

			switch (sa->raw.sa_family) {
			case AF_INET:
				return ip4_addr_string_sa(buf, end, &sa->v4, spec, fmt);
			case AF_INET6:
				return ip6_addr_string_sa(buf, end, &sa->v6, spec, fmt);
			default:
				return string(buf, end, "(invalid address)", spec);
			}}
		}
		break;
	case 'E':
		return escaped_string(buf, end, ptr, spec, fmt);
	case 'U':
		return uuid_string(buf, end, ptr, spec, fmt);
	case 'V':
		{
			va_list va;

			va_copy(va, *((struct va_format *)ptr)->va);
			buf += vsnprintf(buf, end > buf ? end - buf : 0,
					 ((struct va_format *)ptr)->fmt, va);
			va_end(va);
			return buf;
		}
	case 'K':
		if (!kptr_restrict)
			break;
		return restricted_pointer(buf, end, ptr, spec);
	case 'N':
		return netdev_bits(buf, end, ptr, fmt);
	case 'a':
		return address_val(buf, end, ptr, fmt);
	case 'd':
		return dentry_name(buf, end, ptr, spec, fmt);
	case 'C':
		return clock(buf, end, ptr, spec, fmt);
	case 'D':
		return dentry_name(buf, end,
				   ((const struct file *)ptr)->f_path.dentry,
				   spec, fmt);
#ifdef CONFIG_BLOCK
	case 'g':
		return bdev_name(buf, end, ptr, spec, fmt);
#endif

	case 'G':
		return flags_string(buf, end, ptr, fmt);
	case 'O':
		switch (fmt[1]) {
		case 'F':
			return device_node_string(buf, end, ptr, spec, fmt + 1);
		}
	case 'x':
		return pointer_string(buf, end, ptr, spec);
	}


	return ptr_to_id(buf, end, ptr, spec);
}
