GF_Err stbl_GetSampleShadow(GF_ShadowSyncBox *stsh, u32 *sampleNumber, u32 *syncNum)
{
	u32 i, count;
	GF_StshEntry *ent;

	if (stsh->r_LastFoundSample && (stsh->r_LastFoundSample <= *sampleNumber)) {
		i = stsh->r_LastEntryIndex;
	} else {
		i = 0;
		stsh->r_LastFoundSample = 1;
	}

	ent = NULL;
	(*syncNum) = 0;

	count = gf_list_count(stsh->entries);
	for (; i<count; i++) {
		ent = (GF_StshEntry*)gf_list_get(stsh->entries, i);

		if (ent->shadowedSampleNumber == *sampleNumber) {
			(*syncNum) = ent->syncSampleNumber;
			stsh->r_LastFoundSample = *sampleNumber;
			stsh->r_LastEntryIndex = i;
			return GF_OK;
		} else if (ent->shadowedSampleNumber > *sampleNumber) {


			if (!i) return GF_OK;

			ent = (GF_StshEntry*)gf_list_get(stsh->entries, i-1);
			(*syncNum) = ent->syncSampleNumber;

			(*sampleNumber) = ent->shadowedSampleNumber;

			stsh->r_LastEntryIndex = i-1;
			stsh->r_LastFoundSample = ent->shadowedSampleNumber;
		}
	}
	stsh->r_LastEntryIndex = i-1;
	stsh->r_LastFoundSample = ent ? ent->shadowedSampleNumber : 0;
	return GF_OK;
}
