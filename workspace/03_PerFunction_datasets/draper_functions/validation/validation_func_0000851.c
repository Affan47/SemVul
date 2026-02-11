broadsheet_spiflash_rewrite_sector(struct broadsheetfb_par *par,
					int sector_size, int data_start_addr,
					int data_len, const char *data)
{
	int err;
	char *sector_buffer;
	int tail_start_addr;
	int start_sector_addr;

	sector_buffer = kzalloc(sizeof(char)*sector_size, GFP_KERNEL);
	if (!sector_buffer)
		return -ENOMEM;


	start_sector_addr = (data_start_addr / sector_size) * sector_size;


	if (data_start_addr != start_sector_addr) {


		err = broadsheet_spiflash_read_range(par, start_sector_addr,
						data_start_addr, sector_buffer);
		if (err)
			goto out;
	}


	memcpy(sector_buffer + data_start_addr, data, data_len);


	tail_start_addr = (data_start_addr + data_len) % sector_size;

	if (tail_start_addr) {
		int tail_len;

		tail_len = sector_size - tail_start_addr;


		err = broadsheet_spiflash_read_range(par, tail_start_addr,
			tail_len, sector_buffer + tail_start_addr);
		if (err)
			goto out;
	}


	err = broadsheet_spiflash_erase_sector(par, start_sector_addr);
	if (err)
		goto out;


	err = broadsheet_spiflash_write_sector(par, start_sector_addr,
					sector_buffer, sector_size);
out:
	kfree(sector_buffer);
	return err;
}
