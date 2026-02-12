GF_Err metx_on_child_box(GF_Box *s, GF_Box *a, Bool is_rem)
{
	GF_MetaDataSampleEntryBox *ptr = (GF_MetaDataSampleEntryBox *)s;
	switch (a->type) {
	case GF_ISOM_BOX_TYPE_TXTC:

		BOX_FIELD_ASSIGN(config, GF_TextConfigBox)
		break;
	}
	return GF_OK;
}
