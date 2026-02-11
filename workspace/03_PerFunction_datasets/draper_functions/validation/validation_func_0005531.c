index_dump_node(struct index_node_f *node, struct buffer *buf,
								int fd)
{
	struct index_value *v;
	int ch, pushed;

	pushed = buf_pushchars(buf, node->prefix);

	for (v = node->values; v != NULL; v = v->next) {
		write_str_safe(fd, buf->bytes, buf->used);
		write_str_safe(fd, " ", 1);
		write_str_safe(fd, v->value, strlen(v->value));
		write_str_safe(fd, "\n", 1);
	}

	for (ch = node->first; ch <= node->last; ch++) {
		struct index_node_f *child = index_readchild(node, ch);

		if (!child)
			continue;

		buf_pushchar(buf, ch);
		index_dump_node(child, buf, fd);
		buf_popchar(buf);
	}

	buf_popchars(buf, pushed);
	index_close(node);
}
