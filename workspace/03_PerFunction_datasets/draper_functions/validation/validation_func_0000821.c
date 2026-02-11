be_chk_reset_complete(struct beiscsi_hba *phba)
{
	unsigned int num_loop;
	u8 *mpu_sem = 0;
	u32 status;

	num_loop = 1000;
	mpu_sem = (u8 *)phba->csr_va + MPU_EP_SEMAPHORE;
	msleep(5000);

	while (num_loop) {
		status = readl((void *)mpu_sem);

		if ((status & 0x80000000) || (status & 0x0000FFFF) == 0xC000)
			break;
		msleep(60);
		num_loop--;
	}

	if ((status & 0x80000000) || (!num_loop)) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BC_%d : Failed in be_chk_reset_complete"
			    "status = 0x%x\n", status);
		return -EIO;
	}

	return 0;
}
