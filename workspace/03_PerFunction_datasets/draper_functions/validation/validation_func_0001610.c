bthci_CmdDisconnectLogicalLink(
	struct rtw_adapter *padapter,
	struct packet_irp_hcicmd_data *pHciCmd
	)
{
	enum hci_status status = HCI_STATUS_SUCCESS;

	struct bt_30info *pBTinfo = GET_BT_INFO(padapter);
	struct bt_mgnt *pBtMgnt = &pBTinfo->BtMgnt;
	struct bt_dgb *pBtDbg = &pBTinfo->BtDbg;
	u16	logicHandle;
	u8 i, j, find = 0, LogLinkCount = 0;

	pBtDbg->dbgHciInfo.hciCmdCntDisconnectLogLink++;

	logicHandle = *((u16 *)pHciCmd->Data);
	RTPRINT(FIOCTL, IOCTL_BT_HCICMD, ("DisconnectLogicalLink, logicHandle = 0x%x\n", logicHandle));


	for (j = 0; j < MAX_BT_ASOC_ENTRY_NUM; j++) {
		for (i = 0; i < MAX_LOGICAL_LINK_NUM; i++) {
			if (pBTinfo->BtAsocEntry[j].LogLinkCmdData[i].BtLogLinkhandle == logicHandle) {
				RTPRINT(FIOCTL, IOCTL_BT_HCICMD, ("DisconnectLogicalLink, logicHandle is matched  0x%x\n", logicHandle));
				bthci_ResetFlowSpec(padapter, j, i);
				find = 1;
				pBtMgnt->DisconnectEntryNum = j;
				break;
			}
		}
	}

	if (!find)
		status = HCI_STATUS_UNKNOW_CONNECT_ID;


	for (i = 0; i < MAX_LOGICAL_LINK_NUM; i++) {
		if (pBTinfo->BtAsocEntry[pBtMgnt->DisconnectEntryNum].LogLinkCmdData[i].BtLogLinkhandle != 0)
			LogLinkCount++;
	}


	bthci_EventCommandStatus(padapter,
			LINK_CONTROL_COMMANDS,
			HCI_DISCONNECT_LOGICAL_LINK,
			status);


	if (status == HCI_STATUS_SUCCESS) {
		bthci_EventDisconnectLogicalLinkComplete(padapter, status,
			logicHandle, HCI_STATUS_CONNECT_TERMINATE_LOCAL_HOST);
	}

	if (LogLinkCount == 0)
		mod_timer(&pBTinfo->BTDisconnectPhyLinkTimer,
			  jiffies + msecs_to_jiffies(100));

	return status;
}
