gf_smil_mark_modified(SMIL_Timing_RTI *rti, Bool remove)
{
	GF_SceneGraph * sg = rti->timed_elt->sgprivate->scenegraph;
	while (sg->parent_scene) sg = sg->parent_scene;
	if (remove) {
		gf_list_del_item(sg->modified_smil_timed_elements, rti);
	} else {
		gf_list_add(sg->modified_smil_timed_elements, rti);
	}
}
