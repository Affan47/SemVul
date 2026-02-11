doc200x_ident_chip(struct mtd_info *mtd, int nr)
{
	struct nand_chip *this = mtd->priv;
	struct doc_priv *doc = this->priv;
	uint16_t ret;

	doc200x_select_chip(mtd, nr);
	doc200x_hwcontrol(mtd, NAND_CMD_READID,
			  NAND_CTRL_CLE | NAND_CTRL_CHANGE);
	doc200x_hwcontrol(mtd, 0, NAND_CTRL_ALE | NAND_CTRL_CHANGE);
	doc200x_hwcontrol(mtd, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);


	udelay(50);

	ret = this->read_byte(mtd) << 8;
	ret |= this->read_byte(mtd);

	if (doc->ChipID == DOC_ChipID_Doc2k && try_dword && !nr) {

		union {
			uint32_t dword;
			uint8_t byte[4];
		} ident;
		void __iomem *docptr = doc->virtadr;

		doc200x_hwcontrol(mtd, NAND_CMD_READID,
				  NAND_CTRL_CLE | NAND_CTRL_CHANGE);
		doc200x_hwcontrol(mtd, 0, NAND_CTRL_ALE | NAND_CTRL_CHANGE);
		doc200x_hwcontrol(mtd, NAND_CMD_NONE,
				  NAND_NCE | NAND_CTRL_CHANGE);

		udelay(50);

		ident.dword = readl(docptr + DoC_2k_CDSN_IO);
		if (((ident.byte[0] << 8) | ident.byte[1]) == ret) {
			printk(KERN_INFO "DiskOnChip 2000 responds to DWORD access\n");
			this->read_buf = &doc2000_readbuf_dword;
		}
	}

	return ret;
}
