gf_sg_proto_set_in_graph(GF_Proto *proto, GF_SceneGraph *inScene, Bool set_in)
{
	u32 i;
	GF_Proto *tmp;
	GF_List *removeFrom;
	GF_List *insertIn;

	if (set_in) {
		removeFrom = proto->parent_graph->unregistered_protos;
		insertIn = proto->parent_graph->protos;
	} else {
		insertIn = proto->parent_graph->unregistered_protos;
		removeFrom = proto->parent_graph->protos;
	}

	gf_list_del_item(removeFrom, proto);

	i=0;
	while ((tmp = (GF_Proto*)gf_list_enum(insertIn, &i))) {
		if (tmp==proto) return GF_OK;
		if (!set_in) continue;

		if (tmp->ID==proto->ID) return GF_BAD_PARAM;
		if (!stricmp(tmp->Name, proto->Name)) return GF_BAD_PARAM;
	}
	return gf_list_add(insertIn, proto);
}
