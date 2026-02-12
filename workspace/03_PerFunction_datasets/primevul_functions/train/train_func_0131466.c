enum follow_symlinks_result get_tree_entry_follow_symlinks(unsigned char *tree_sha1, const char *name, unsigned char *result, struct strbuf *result_path, unsigned *mode)
{
	int retval = MISSING_OBJECT;
	struct dir_state *parents = NULL;
	size_t parents_alloc = 0;
	size_t i, parents_nr = 0;
	unsigned char current_tree_sha1[20];
	struct strbuf namebuf = STRBUF_INIT;
	struct tree_desc t;
	int follows_remaining = GET_TREE_ENTRY_FOLLOW_SYMLINKS_MAX_LINKS;

	init_tree_desc(&t, NULL, 0UL);
	strbuf_addstr(&namebuf, name);
	hashcpy(current_tree_sha1, tree_sha1);

	while (1) {
		int find_result;
		char *first_slash;
		char *remainder = NULL;

		if (!t.buffer) {
			void *tree;
			unsigned char root[20];
			unsigned long size;
			tree = read_object_with_reference(current_tree_sha1,
							  tree_type, &size,
							  root);
			if (!tree)
				goto done;

			ALLOC_GROW(parents, parents_nr + 1, parents_alloc);
			parents[parents_nr].tree = tree;
			parents[parents_nr].size = size;
			hashcpy(parents[parents_nr].sha1, root);
			parents_nr++;

			if (namebuf.buf[0] == '\0') {
				hashcpy(result, root);
				retval = FOUND;
				goto done;
			}

			if (!size)
				goto done;


			init_tree_desc(&t, tree, size);
		}


		while (namebuf.buf[0] == '/') {
			strbuf_remove(&namebuf, 0, 1);
		}


		if ((first_slash = strchr(namebuf.buf, '/'))) {
			*first_slash = 0;
			remainder = first_slash + 1;
		}

		if (!strcmp(namebuf.buf, "..")) {
			struct dir_state *parent;


			if (parents_nr == 1) {
				if (remainder)
					*first_slash = '/';
				strbuf_add(result_path, namebuf.buf,
					   namebuf.len);
				*mode = 0;
				retval = FOUND;
				goto done;
			}
			parent = &parents[parents_nr - 1];
			free(parent->tree);
			parents_nr--;
			parent = &parents[parents_nr - 1];
			init_tree_desc(&t, parent->tree, parent->size);
			strbuf_remove(&namebuf, 0, remainder ? 3 : 2);
			continue;
		}


		if (namebuf.buf[0] == '\0') {
			hashcpy(result, parents[parents_nr - 1].sha1);
			retval = FOUND;
			goto done;
		}


		find_result = find_tree_entry(&t, namebuf.buf,
					      current_tree_sha1, mode);
		if (find_result) {
			goto done;
		}

		if (S_ISDIR(*mode)) {
			if (!remainder) {
				hashcpy(result, current_tree_sha1);
				retval = FOUND;
				goto done;
			}

			t.buffer = NULL;
			strbuf_remove(&namebuf, 0,
				      1 + first_slash - namebuf.buf);
		} else if (S_ISREG(*mode)) {
			if (!remainder) {
				hashcpy(result, current_tree_sha1);
				retval = FOUND;
			} else {
				retval = NOT_DIR;
			}
			goto done;
		} else if (S_ISLNK(*mode)) {

			unsigned long link_len;
			size_t len;
			char *contents, *contents_start;
			struct dir_state *parent;
			enum object_type type;

			if (follows_remaining-- == 0) {

				retval = SYMLINK_LOOP;
				goto done;
			}


			retval = DANGLING_SYMLINK;

			contents = read_sha1_file(current_tree_sha1, &type,
						  &link_len);

			if (!contents)
				goto done;

			if (contents[0] == '/') {
				strbuf_addstr(result_path, contents);
				free(contents);
				*mode = 0;
				retval = FOUND;
				goto done;
			}

			if (remainder)
				len = first_slash - namebuf.buf;
			else
				len = namebuf.len;

			contents_start = contents;

			parent = &parents[parents_nr - 1];
			init_tree_desc(&t, parent->tree, parent->size);
			strbuf_splice(&namebuf, 0, len,
				      contents_start, link_len);
			if (remainder)
				namebuf.buf[link_len] = '/';
			free(contents);
		}
	}
done:
	for (i = 0; i < parents_nr; i++)
		free(parents[i].tree);
	free(parents);

	strbuf_release(&namebuf);
	return retval;
}
