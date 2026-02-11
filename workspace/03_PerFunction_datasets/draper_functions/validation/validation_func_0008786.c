SDEnWideBus(FunctionalState NewState) {
	SDIO_CmdInitTypeDef SDIO_CmdInitStructure;
	SD_Error errorstatus = SD_OK;

	uint32_t scr[2] = {0, 0};

	if (SDIO_GetResponse(SDIO_RESP1) & SD_CARD_LOCKED) {
		errorstatus = SD_LOCK_UNLOCK_FAILED;
		return(errorstatus);
	}


	errorstatus = FindSCR(sdioData.RCA, scr);

	if (errorstatus != SD_OK) {
		return(errorstatus);
	}


	if (NewState == ENABLE) {

		if ((scr[1] & SD_WIDE_BUS_SUPPORT) != SD_ALLZERO) {

			SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) sdioData.RCA << 16;
			SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
			SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
			SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
			SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
			SDIO_SendCommand(&SDIO_CmdInitStructure);

			errorstatus = CmdResp1Error(SD_CMD_APP_CMD);

			if (errorstatus != SD_OK) {
				return(errorstatus);
			}


			SDIO_CmdInitStructure.SDIO_Argument = 0x2;
			SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_SD_SET_BUSWIDTH;
			SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
			SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
			SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
			SDIO_SendCommand(&SDIO_CmdInitStructure);

			errorstatus = CmdResp1Error(SD_CMD_APP_SD_SET_BUSWIDTH);

			if (errorstatus != SD_OK) {
				return(errorstatus);
			}

			return(errorstatus);
		} else {
			errorstatus = SD_REQUEST_NOT_APPLICABLE;
			return(errorstatus);
		}
	}

	else {

		if ((scr[1] & SD_SINGLE_BUS_SUPPORT) != SD_ALLZERO) {

			SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) sdioData.RCA << 16;
			SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_CMD;
			SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
			SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
			SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
			SDIO_SendCommand(&SDIO_CmdInitStructure);

			errorstatus = CmdResp1Error(SD_CMD_APP_CMD);

			if (errorstatus != SD_OK) {
				return(errorstatus);
			}


			SDIO_CmdInitStructure.SDIO_Argument = 0x00;
			SDIO_CmdInitStructure.SDIO_CmdIndex = SD_CMD_APP_SD_SET_BUSWIDTH;
			SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
			SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
			SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
			SDIO_SendCommand(&SDIO_CmdInitStructure);

			errorstatus = CmdResp1Error(SD_CMD_APP_SD_SET_BUSWIDTH);

			if (errorstatus != SD_OK) {
				return(errorstatus);
			}

			return(errorstatus);
		} else {
			errorstatus = SD_REQUEST_NOT_APPLICABLE;
			return(errorstatus);
		}
	}
}
