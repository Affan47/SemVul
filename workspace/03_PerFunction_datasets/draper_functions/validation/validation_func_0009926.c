mmc_app_send_scr(struct mmc_card *card, u32 *scr)
{
	int err;
	struct mmc_request mrq = {NULL};
	struct mmc_command cmd = {0};
	struct mmc_data data = {0};
	struct scatterlist sg;
	void *data_buf;

	BUG_ON(!card);
	BUG_ON(!card->host);
	BUG_ON(!scr);


	err = mmc_app_cmd(card->host, card);
	if (err)
		return err;


	data_buf = kmalloc(sizeof(card->raw_scr), GFP_KERNEL);
	if (data_buf == NULL)
		return -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_APP_SEND_SCR;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 8;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, data_buf, 8);

	mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(card->host, &mrq);

	memcpy(scr, data_buf, sizeof(card->raw_scr));
	kfree(data_buf);

	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	scr[0] = be32_to_cpu(scr[0]);
	scr[1] = be32_to_cpu(scr[1]);

	return 0;
}
