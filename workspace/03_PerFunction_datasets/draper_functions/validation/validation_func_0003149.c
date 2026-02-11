af9033_wr_reg_val_tab(struct af9033_dev *dev,
		const struct reg_val *tab, int tab_len)
{
#define MAX_TAB_LEN 212
	int ret, i, j;
	u8 buf[1 + MAX_TAB_LEN];

	dev_dbg(&dev->client->dev, "tab_len=%d\n", tab_len);

	if (tab_len > sizeof(buf)) {
		dev_warn(&dev->client->dev, "tab len %d is too big\n", tab_len);
		return -EINVAL;
	}

	for (i = 0, j = 0; i < tab_len; i++) {
		buf[j] = tab[i].val;

		if (i == tab_len - 1 || tab[i].reg != tab[i + 1].reg - 1) {
			ret = af9033_wr_regs(dev, tab[i].reg - j, buf, j + 1);
			if (ret < 0)
				goto err;

			j = 0;
		} else {
			j++;
		}
	}

	return 0;

err:
	dev_dbg(&dev->client->dev, "failed=%d\n", ret);

	return ret;
}
