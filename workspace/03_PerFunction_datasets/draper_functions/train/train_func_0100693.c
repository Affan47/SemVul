bthci_CmdAMPTestEnd(struct rtw_adapter *padapter,
		    struct packet_irp_hcicmd_data *pHciCmd)
{
	enum hci_status status = HCI_STATUS_SUCCESS;
	struct bt_30info *pBTInfo = GET_BT_INFO(padapter);
	struct bt_hci_info *pBtHciInfo = &pBTInfo->BtHciInfo;

	if (!pBtHciInfo->bInTestMode) {
		RTPRINT(FIOCTL, (IOCTL_BT_EVENT|IOCTL_BT_LOGO), ("Not in Test mode, return status = HCI_STATUS_CMD_DISALLOW\n"));
		status = HCI_STATUS_CMD_DISALLOW;
		return status;
	}

	pBtHciInfo->bTestIsEnd = true;

	del_timer_sync(&pBTInfo->BTTestSendPacketTimer);

	rtl8723a_check_bssid(padapter, true);


	{
		u8 localBuf[4] = "";
		struct packet_irp_hcievent_data *PPacketIrpEvent;

		RTPRINT(FIOCTL, (IOCTL_BT_EVENT|IOCTL_BT_LOGO), ("AMP Test End Event \n"));
		PPacketIrpEvent = (struct packet_irp_hcievent_data *)(&localBuf[0]);
		PPacketIrpEvent->EventCode = HCI_EVENT_AMP_TEST_END;
		PPacketIrpEvent->Length = 2;

		PPacketIrpEvent->Data[0] = status;
		PPacketIrpEvent->Data[1] = pBtHciInfo->TestScenario;

		bthci_IndicateEvent(padapter, PPacketIrpEvent, 4);
	}

	bthci_EventAMPReceiverReport(padapter, 0x01);

	return status;
}
