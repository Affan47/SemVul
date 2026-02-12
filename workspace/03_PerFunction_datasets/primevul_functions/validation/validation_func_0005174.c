GF_Err stbl_RemoveShadow(GF_SampleTableBox *stbl, u32 sampleNumber)
{
	u32 i;
	GF_ShadowSyncBox *stsh;
	GF_StshEntry *ent;
	if (!stbl->ShadowSync) return GF_OK;
	stsh = stbl->ShadowSync;


	i=0;
	while ((ent = (GF_StshEntry *)gf_list_enum(stsh->entries, &i))) {
		if (ent->shadowedSampleNumber == sampleNumber) {
			i--;
			gf_list_rem(stsh->entries, i);
		}
	}

	stsh->r_LastEntryIndex = 0;
	stsh->r_LastFoundSample = 0;
	return GF_OK;
}
