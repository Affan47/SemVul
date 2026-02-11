xmms_xform_metadata_collect_r (xmms_xform_t *xform, metadata_festate_t *info,
                               GString *namestr)
{
	if (xform->prev) {
		xmms_xform_metadata_collect_r (xform->prev, info, namestr);
	}

	if (xform->plugin) {
		if (namestr->len) {
			g_string_append_c (namestr, ':');
		}
		g_string_append (namestr, xmms_xform_shortname (xform));
	}

	if (xform->metadata_changed) {
		xmms_xform_metadata_collect_one (xform, info);
	}

	xform->metadata_collected = TRUE;
}
