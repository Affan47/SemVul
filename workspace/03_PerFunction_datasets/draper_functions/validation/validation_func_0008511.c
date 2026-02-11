_PHY_SimularityCompare(struct rtw_adapter *pAdapter, int result[][8], u8 c1, u8 c2)
{
	u32 i, j, diff, SimularityBitMap, bound = 0;
	struct hal_data_8723a *pHalData = GET_HAL_DATA(pAdapter);
	u8 final_candidate[2] = {0xFF, 0xFF};
	bool bResult = true;

	if (pHalData->rf_type == RF_2T2R)
		bound = 8;
	else
		bound = 4;

	SimularityBitMap = 0;

	for (i = 0; i < bound; i++) {
		diff = (result[c1][i] > result[c2][i]) ? (result[c1][i] - result[c2][i]) : (result[c2][i] - result[c1][i]);
		if (diff > MAX_TOLERANCE) {
			if ((i == 2 || i == 6) && !SimularityBitMap) {
				if (result[c1][i]+result[c1][i+1] == 0)
					final_candidate[(i/4)] = c2;
				else if (result[c2][i]+result[c2][i+1] == 0)
					final_candidate[(i/4)] = c1;
				else
					SimularityBitMap = SimularityBitMap|(1<<i);
			} else {
				SimularityBitMap = SimularityBitMap|(1<<i);
			}
		}
	}

	if (SimularityBitMap == 0) {
		for (i = 0; i < (bound/4); i++) {
			if (final_candidate[i] != 0xFF) {
				for (j = i*4; j < (i+1)*4-2; j++)
					result[3][j] = result[final_candidate[i]][j];
				bResult = false;
			}
		}
		return bResult;
	} else if (!(SimularityBitMap & 0x0F)) {

		for (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
		return false;
	} else if (!(SimularityBitMap & 0xF0) && pHalData->rf_type == RF_2T2R) {

		for (i = 4; i < 8; i++)
			result[3][i] = result[c1][i];
		return false;
	} else {
		return false;
	}
}
