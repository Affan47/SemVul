s2b_set_field(SWFReader *read, GF_List *dst, GF_Node *n, char *fieldName, s32 pos, u32 type, void *val, Bool insert)
{
	u32 i, count;
	GF_FieldInfo info;
	GF_Command *com = NULL;
	GF_CommandField *f;

	gf_node_get_field_by_name(n, fieldName, &info);

	count = gf_list_count(dst);
	for (i=0; i<count; i++) {
		com = gf_list_get(dst, i);
		if (com->node!=n) continue;
		f = gf_list_get(com->command_fields, 0);
		if (f->fieldIndex != info.fieldIndex) continue;
		if (f->pos != pos) continue;

		if (insert) return;

		if (type==GF_SG_VRML_SFSTRING) {
			if (((SFString*)f->field_ptr)->buffer)
				gf_free(((SFString*)f->field_ptr)->buffer);
			((SFString*)f->field_ptr)->buffer = gf_strdup( (char *) val);
		} else {
			gf_sg_vrml_field_copy(f->field_ptr, val, type);
		}
		gf_list_rem(dst, i);
		gf_list_add(dst, com);
		return;
	}

	com = gf_sg_command_new(read->load->scene_graph, (pos<0) ? GF_SG_FIELD_REPLACE : GF_SG_INDEXED_REPLACE);
	com->node = n;
	gf_node_register(com->node, NULL);
	f = gf_sg_command_field_new(com);
	f->field_ptr = gf_sg_vrml_field_pointer_new(type);
	if (type==GF_SG_VRML_SFSTRING) {
		((SFString*)f->field_ptr)->buffer = gf_strdup( (char *) val);
	} else {
		gf_sg_vrml_field_copy(f->field_ptr, val, type);
	}
	f->fieldType = type;
	f->pos = pos;
	f->fieldIndex = info.fieldIndex;

	if (insert)
		gf_list_insert(dst, com, 0);
	else
		gf_list_add(dst, com);
}
