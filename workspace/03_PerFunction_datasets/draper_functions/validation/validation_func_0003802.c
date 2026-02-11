SiS_SearchModeID(struct SiS_Private *SiS_Pr, unsigned short *ModeNo,
		 unsigned short *ModeIdIndex)
{
	if ((*ModeNo) <= 0x13) {

		if ((*ModeNo) != 0x03)
			return 0;

		(*ModeIdIndex) = 0;

	} else {

		for (*ModeIdIndex = 0;; (*ModeIdIndex)++) {

			if (SiS_Pr->SiS_EModeIDTable[*ModeIdIndex].Ext_ModeID ==
			    (*ModeNo))
				break;

			if (SiS_Pr->SiS_EModeIDTable[*ModeIdIndex].Ext_ModeID ==
			    0xFF)
				return 0;
		}

	}

	return 1;
}
