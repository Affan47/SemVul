gf_odf_new_cc_name()
{
	GF_CC_Name *newDesc = (GF_CC_Name *) gf_malloc(sizeof(GF_CC_Name));
	if (!newDesc) return NULL;

	newDesc->ContentCreators = gf_list_new();
	if (! newDesc->ContentCreators) {
		gf_free(newDesc);
		return NULL;
	}
	newDesc->tag = GF_ODF_CC_NAME_TAG;
	return (GF_Descriptor *) newDesc;
}
