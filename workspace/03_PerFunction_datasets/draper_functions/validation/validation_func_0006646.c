compose_attach_parts(Compose *compose, MsgInfo *msginfo)
{
	MimeInfo *mimeinfo;
	MimeInfo *child;
	MimeInfo *firsttext = NULL;
	MimeInfo *encrypted = NULL;
	GNode    *node;
	gchar *outfile;
	const gchar *partname = NULL;

	mimeinfo = procmime_scan_message(msginfo);
	if (!mimeinfo) return;

	if (mimeinfo->node->children == NULL) {
		procmime_mimeinfo_free_all(mimeinfo);
		return;
	}


	child = (MimeInfo *) mimeinfo->node->children->data;
	while (child && child->node->children && (child->type == MIMETYPE_MULTIPART))
		child = (MimeInfo *)child->node->children->data;

	if (child) {
		if (child->type == MIMETYPE_TEXT) {
			firsttext = child;
			debug_print("First text part found\n");
		} else if (compose->mode == COMPOSE_REEDIT &&
			 child->type == MIMETYPE_APPLICATION &&
			 !g_ascii_strcasecmp(child->subtype, "pgp-encrypted")) {
			encrypted = (MimeInfo *)child->node->parent->data;
		}
	}
	child = (MimeInfo *) mimeinfo->node->children->data;
	while (child != NULL) {
		gint err;

		if (child == encrypted) {

			NEXT_PART_NOT_CHILD(child);
			continue;
		}

		if (child->type == MIMETYPE_MULTIPART) {

			child = procmime_mimeinfo_next(child);
			continue;
		}

		if (child == firsttext) {
			child = procmime_mimeinfo_next(child);
			continue;
		}

		outfile = procmime_get_tmp_file_name(child);
		if ((err = procmime_get_part(outfile, child)) < 0)
			g_warning("Can't get the part of multipart message. (%s)", strerror(-err));
		else {
			gchar *content_type;

			content_type = procmime_get_content_type_str(child->type, child->subtype);


			if ((strcmp(content_type, "application/pgp-signature") &&
			    strcmp(content_type, "application/pkcs7-signature") &&
			    strcmp(content_type, "application/x-pkcs7-signature"))
			    || compose->mode == COMPOSE_REDIRECT) {
				partname = procmime_mimeinfo_get_parameter(child, "filename");
				if (partname == NULL)
					partname = procmime_mimeinfo_get_parameter(child, "name");
				if (partname == NULL)
					partname = "";
				compose_attach_append(compose, outfile,
						      partname, content_type,
						      procmime_mimeinfo_get_parameter(child, "charset"));
			} else {
				compose_force_signing(compose, compose->account, NULL);
			}
			g_free(content_type);
		}
		g_free(outfile);
		NEXT_PART_NOT_CHILD(child);
	}
	procmime_mimeinfo_free_all(mimeinfo);
}
