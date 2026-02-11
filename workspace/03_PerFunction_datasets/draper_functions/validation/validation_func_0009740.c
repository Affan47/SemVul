findEntryForTime(GF_SampleTableBox *stbl, u64 DTS, u8 useCTS, u32 *sampleNumber, u32 *prevSampleNumber)
{
	u32 i, j, curSampNum, CTSOffset, count;
	u64 curDTS;
	GF_SttsEntry *ent;
	(*sampleNumber) = 0;
	(*prevSampleNumber) = 0;

	if (!stbl->CompositionOffset) useCTS = 0;


	useCTS = 0;


	if (stbl->TimeToSample->r_FirstSampleInEntry &&
		(DTS >= stbl->TimeToSample->r_CurrentDTS) ) {


		i = stbl->TimeToSample->r_currentEntryIndex;
		curDTS = stbl->TimeToSample->r_CurrentDTS;
		curSampNum = stbl->TimeToSample->r_FirstSampleInEntry;
	} else {
		i = 0;
		curDTS = stbl->TimeToSample->r_CurrentDTS = 0;
		curSampNum = stbl->TimeToSample->r_FirstSampleInEntry = 1;
		stbl->TimeToSample->r_currentEntryIndex = 0;
	}


	if (i && useCTS) {
		while (1) {
			stbl_GetSampleCTS(stbl->CompositionOffset, curSampNum, &CTSOffset);

			if ( i && (curDTS + CTSOffset > DTS) ) {
				ent = &stbl->TimeToSample->entries[i];
				curSampNum -= ent->sampleCount;
				curDTS -= ent->sampleDelta * ent->sampleCount;
				i --;
			} else if (!i) {

				curDTS = stbl->TimeToSample->r_CurrentDTS = 0;
				curSampNum = stbl->TimeToSample->r_FirstSampleInEntry = 1;
				stbl->TimeToSample->r_currentEntryIndex = 0;
				break;
			} else {

				break;
			}
		}
	}


	count = stbl->TimeToSample->nb_entries;
	for (; i<count; i++) {
		ent = &stbl->TimeToSample->entries[i];
		if (useCTS) {
			stbl_GetSampleCTS(stbl->CompositionOffset, curSampNum, &CTSOffset);
		} else {
			CTSOffset = 0;
		}
		for (j=0; j<ent->sampleCount; j++) {
			if (curDTS + CTSOffset >= DTS) goto entry_found;
			curSampNum += 1;
			curDTS += ent->sampleDelta;
		}

		stbl->TimeToSample->r_CurrentDTS += ent->sampleCount * ent->sampleDelta;
		stbl->TimeToSample->r_currentEntryIndex += 1;
		stbl->TimeToSample->r_FirstSampleInEntry += ent->sampleCount;
	}

	return GF_OK;

entry_found:

	if (curDTS + CTSOffset == DTS) {
		(*sampleNumber) = curSampNum;
	}

	else if (curDTS == DTS) {
		(*sampleNumber) = curSampNum;
	} else {

		if (curSampNum != 1) {
			(*prevSampleNumber) = curSampNum - 1;
		} else {
			(*prevSampleNumber) = 1;
		}
	}
	return GF_OK;
}
