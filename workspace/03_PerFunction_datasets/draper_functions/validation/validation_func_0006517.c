be_mbox_db_ready_wait(struct be_adapter *adapter, void __iomem *db)
{
	int msecs = 0;
	u32 ready;

	do {
		if (be_check_error(adapter, BE_ERROR_ANY))
			return -EIO;

		ready = ioread32(db);
		if (ready == 0xffffffff)
			return -1;

		ready &= MPU_MAILBOX_DB_RDY_MASK;
		if (ready)
			break;

		if (msecs > 4000) {
			dev_err(&adapter->pdev->dev, "FW not responding\n");
			be_set_error(adapter, BE_ERROR_FW);
			be_detect_error(adapter);
			return -1;
		}

		msleep(1);
		msecs++;
	} while (true);

	return 0;
}
