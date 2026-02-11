dgap_test_fep(struct board_t *brd)
{
	u8 __iomem *addr;
	u16 word;
	u16 err1;
	u16 err2;

	if (!brd || (brd->magic != DGAP_BOARD_MAGIC) || !brd->re_map_membase)
		return -EINVAL;

	addr = brd->re_map_membase;
	word = readw(addr + FEPSTAT);


	brd->wait_for_fep = 0;
	while (brd->wait_for_fep < 500) {

		if (word == *(u16 *)"OS") {


			word = readw(addr + FEP5_PLUS);
			if (word == *(u16 *)"5A")
				brd->bd_flags |= BD_FEP5PLUS;

			return 0;
		}
		msleep_interruptible(10);
		brd->wait_for_fep++;
		word = readw(addr + FEPSTAT);
	}


	err1 = readw(addr + SEQUENCE);
	err2 = readw(addr + ERROR);
	dev_warn(&brd->pdev->dev,
		 "FEPOS for %s not functioning.  Error #(%x,%x).\n",
		 brd->name, err1, err2);
	brd->state = BOARD_FAILED;
	brd->dpastatus = BD_NOFEP;

	return -EIO;
}
