char_link(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t offset, size_t size)
{
	int is_img = (offset && data[-1] == '!'), level;
	size_t i = 1, txt_e, link_b = 0, link_e = 0, title_b = 0, title_e = 0;
	struct buf *content = 0;
	struct buf *link = 0;
	struct buf *title = 0;
	struct buf *u_link = 0;
	size_t org_work_size = rndr->work_bufs[BUFFER_SPAN].size;
	int text_has_nl = 0, ret = 0;
	int in_title = 0, qtype = 0;


	if ((is_img && !rndr->cb.image) || (!is_img && !rndr->cb.link))
		goto cleanup;


	for (level = 1; i < size; i++) {
		if (data[i] == '\n')
			text_has_nl = 1;

		else if (data[i - 1] == '\\')
			continue;

		else if (data[i] == '[')
			level++;

		else if (data[i] == ']') {
			level--;
			if (level <= 0)
				break;
		}
	}

	if (i >= size)
		goto cleanup;

	txt_e = i;
	i++;


	if (rndr->ext_flags & MKDEXT_FOOTNOTES && data[1] == '^') {
		if (txt_e < 3)
			goto cleanup;

		struct buf id = { 0, 0, 0, 0 };
		struct footnote_ref *fr;

		id.data = data + 2;
		id.size = txt_e - 2;

		fr = find_footnote_ref(&rndr->footnotes_found, id.data, id.size);


		if (fr && !fr->is_used) {
			if(!add_footnote_ref(&rndr->footnotes_used, fr))
				goto cleanup;
			fr->is_used = 1;
			fr->num = rndr->footnotes_used.count;
		}


		if (fr && rndr->cb.footnote_ref)
				ret = rndr->cb.footnote_ref(ob, fr->num, rndr->opaque);

		goto cleanup;
	}


	while (i < size && _isspace(data[i]))
		i++;


	if (i < size && data[i] == '(') {

		i++;

		while (i < size && _isspace(data[i]))
			i++;

		link_b = i;


		size_t nb_p = 0;

		while (i < size) {
			if (data[i] == '\\') i += 2;
			else if (data[i] == '(' && i != 0) {
				nb_p++; i++;
			}
			else if (data[i] == ')') {
				if (nb_p == 0) break;
				else nb_p--; i++;
			} else if (i >= 1 && _isspace(data[i-1]) && (data[i] == '\'' || data[i] == '"')) break;
			else i++;
		}

		if (i >= size) goto cleanup;
		link_e = i;


		if (data[i] == '\'' || data[i] == '"') {
			qtype = data[i];
			in_title = 1;
			i++;
			title_b = i;

			while (i < size) {
				if (data[i] == '\\') i += 2;
				else if (data[i] == qtype) {in_title = 0; i++;}
				else if ((data[i] == ')') && !in_title) break;
				else i++;
			}

			if (i >= size) goto cleanup;


			title_e = i - 1;
			while (title_e > title_b && _isspace(data[title_e]))
				title_e--;


			if (data[title_e] != '\'' &&  data[title_e] != '"') {
				title_b = title_e = 0;
				link_e = i;
			}
		}


		while (link_e > link_b && _isspace(data[link_e - 1]))
			link_e--;


		if (data[link_b] == '<') link_b++;
		if (data[link_e - 1] == '>') link_e--;


		if (link_e > link_b) {
			link = rndr_newbuf(rndr, BUFFER_SPAN);
			bufput(link, data + link_b, link_e - link_b);
		}

		if (title_e > title_b) {
			title = rndr_newbuf(rndr, BUFFER_SPAN);
			bufput(title, data + title_b, title_e - title_b);
		}

		i++;
	}


	else if (i < size && data[i] == '[') {
		struct buf id = { 0, 0, 0, 0 };
		struct link_ref *lr;


		i++;
		link_b = i;
		while (i < size && data[i] != ']') i++;
		if (i >= size) goto cleanup;
		link_e = i;


		if (link_b == link_e) {
			if (text_has_nl) {
				struct buf *b = rndr_newbuf(rndr, BUFFER_SPAN);
				size_t j;

				for (j = 1; j < txt_e; j++) {
					if (data[j] != '\n')
						bufputc(b, data[j]);
					else if (data[j - 1] != ' ')
						bufputc(b, ' ');
				}

				id.data = b->data;
				id.size = b->size;
			} else {
				id.data = data + 1;
				id.size = txt_e - 1;
			}
		} else {
			id.data = data + link_b;
			id.size = link_e - link_b;
		}

		lr = find_link_ref(rndr->refs, id.data, id.size);
		if (!lr)
			goto cleanup;


		link = lr->link;
		title = lr->title;
		i++;
	}


	else {
		struct buf id = { 0, 0, 0, 0 };
		struct link_ref *lr;


		if (text_has_nl) {
			struct buf *b = rndr_newbuf(rndr, BUFFER_SPAN);
			size_t j;

			for (j = 1; j < txt_e; j++) {
				if (data[j] != '\n')
					bufputc(b, data[j]);
				else if (data[j - 1] != ' ')
					bufputc(b, ' ');
			}

			id.data = b->data;
			id.size = b->size;
		} else {
			id.data = data + 1;
			id.size = txt_e - 1;
		}


		lr = find_link_ref(rndr->refs, id.data, id.size);
		if (!lr)
			goto cleanup;


		link = lr->link;
		title = lr->title;


		i = txt_e + 1;
	}


	if (txt_e > 1) {
		content = rndr_newbuf(rndr, BUFFER_SPAN);
		if (is_img) {
			bufput(content, data + 1, txt_e - 1);
		} else {


			rndr->in_link_body = 1;
			parse_inline(content, rndr, data + 1, txt_e - 1);
			rndr->in_link_body = 0;
		}
	}

	if (link) {
		u_link = rndr_newbuf(rndr, BUFFER_SPAN);
		unscape_text(u_link, link);
	}


	if (is_img) {
		if (ob->size && ob->data[ob->size - 1] == '!')
			ob->size -= 1;

		ret = rndr->cb.image(ob, u_link, title, content, rndr->opaque);
	} else {
		ret = rndr->cb.link(ob, u_link, title, content, rndr->opaque);
	}


cleanup:
	rndr->work_bufs[BUFFER_SPAN].size = (int)org_work_size;
	return ret ? i : 0;
}
