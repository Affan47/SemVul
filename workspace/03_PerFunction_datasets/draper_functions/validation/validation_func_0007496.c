megaraid_mbox_fire_sync_cmd(adapter_t *adapter)
{
	mbox_t	*mbox;
	uint8_t	raw_mbox[sizeof(mbox_t)];
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	mbox64_t *mbox64;
	int	status = 0;
	int i;
	uint32_t dword;

	mbox = (mbox_t *)raw_mbox;

	memset((caddr_t)raw_mbox, 0, sizeof(mbox_t));

	raw_mbox[0] = 0xFF;

	mbox64	= raid_dev->mbox64;
	mbox	= raid_dev->mbox;


	if (megaraid_busywait_mbox(raid_dev) != 0) {
		status = 1;
		goto blocked_mailbox;
	}


	memcpy((caddr_t)mbox, (caddr_t)raw_mbox, 16);
	mbox->cmdid		= 0xFE;
	mbox->busy		= 1;
	mbox->poll		= 0;
	mbox->ack		= 0;
	mbox->numstatus		= 0;
	mbox->status		= 0;

	wmb();
	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x1);


	i = 0;
	status = 0;
	while (!mbox->numstatus && mbox->cmd == 0xFF) {
		rmb();
		msleep(1);
		i++;
		if (i > 1000 * 60) {
			status = 1;
			break;
		}
	}
	if (mbox->numstatus == 1)
		status = 1;


	dword = RDOUTDOOR(raid_dev);
	WROUTDOOR(raid_dev, dword);
	WRINDOOR(raid_dev,2);

	return status;

blocked_mailbox:
	con_log(CL_ANN, (KERN_WARNING "megaraid: blocked mailbox\n"));
	return status;
}
