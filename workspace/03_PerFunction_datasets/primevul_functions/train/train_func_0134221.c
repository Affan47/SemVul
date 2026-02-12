proto_registrar_dump_elastic(const gchar* filter)
{
	header_field_info *hfinfo;
	header_field_info *parent_hfinfo;
	guint i;
	gboolean open_object = TRUE;
	const char* prev_proto = NULL;
	gchar* str;
	gchar** protos = NULL;
	gchar* proto;
	gboolean found;
	guint j;
	gchar* type;


	if (filter) {
		protos = g_strsplit(filter, ",", -1);
	}


	json_dumper dumper = {
		.output_file = stdout,
		.flags = JSON_DUMPER_FLAGS_PRETTY_PRINT,
	};
	json_dumper_begin_object(&dumper);
	elastic_add_base_mapping(&dumper);

	json_dumper_set_member_name(&dumper, "mappings");
	json_dumper_begin_object(&dumper);
	json_dumper_set_member_name(&dumper, "doc");

	json_dumper_begin_object(&dumper);
	json_dumper_set_member_name(&dumper, "dynamic");
	json_dumper_value_anyf(&dumper, "false");

	json_dumper_set_member_name(&dumper, "properties");
	json_dumper_begin_object(&dumper);
	json_dumper_set_member_name(&dumper, "timestamp");
	json_dumper_begin_object(&dumper);
	json_dumper_set_member_name(&dumper, "type");
	json_dumper_value_string(&dumper, "date");
	json_dumper_end_object(&dumper);

	json_dumper_set_member_name(&dumper, "layers");
	json_dumper_begin_object(&dumper);
	json_dumper_set_member_name(&dumper, "properties");
	json_dumper_begin_object(&dumper);

	for (i = 0; i < gpa_hfinfo.len; i++) {
		if (gpa_hfinfo.hfi[i] == NULL)
			continue;

		PROTO_REGISTRAR_GET_NTH(i, hfinfo);


		if (hfinfo->id == hf_text_only)
			continue;

		if (!proto_registrar_is_protocol(i)) {
			PROTO_REGISTRAR_GET_NTH(hfinfo->parent, parent_hfinfo);


			if (protos) {
				found = FALSE;
				j = 0;
				proto = protos[0];
				while(proto) {
					if (!g_strcmp0(proto, parent_hfinfo->abbrev)) {
						found = TRUE;
						break;
					}
					j++;
					proto = protos[j];
				}
				if (!found)
					continue;
			}

			if (prev_proto && g_strcmp0(parent_hfinfo->abbrev, prev_proto)) {
				json_dumper_end_object(&dumper);
				json_dumper_end_object(&dumper);
				open_object = TRUE;
			}

			prev_proto = parent_hfinfo->abbrev;

			if (open_object) {
				json_dumper_set_member_name(&dumper, parent_hfinfo->abbrev);
				json_dumper_begin_object(&dumper);
				json_dumper_set_member_name(&dumper, "properties");
				json_dumper_begin_object(&dumper);
				open_object = FALSE;
			}

			type = ws_type_to_elastic(hfinfo->type);
			if (type) {
				str = g_strdup_printf("%s_%s", prev_proto, hfinfo->abbrev);
				json_dumper_set_member_name(&dumper, dot_to_underscore(str));
				g_free(str);
				json_dumper_begin_object(&dumper);
				json_dumper_set_member_name(&dumper, "type");
				json_dumper_value_string(&dumper, type);
				json_dumper_end_object(&dumper);
			}
		}
	}

	if (prev_proto) {
		json_dumper_end_object(&dumper);
		json_dumper_end_object(&dumper);
	}

	json_dumper_end_object(&dumper);
	json_dumper_end_object(&dumper);
	json_dumper_end_object(&dumper);
	json_dumper_end_object(&dumper);
	json_dumper_end_object(&dumper);
	json_dumper_end_object(&dumper);
	gboolean ret = json_dumper_finish(&dumper);
	DISSECTOR_ASSERT(ret);

	g_strfreev(protos);
}
