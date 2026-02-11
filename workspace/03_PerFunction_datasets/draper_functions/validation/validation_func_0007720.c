brcmf_sdio_download_firmware(struct brcmf_sdio *bus,
					const struct firmware *fw,
					void *nvram, u32 nvlen)
{
	int bcmerror = -EFAULT;
	u32 rstvec;

	sdio_claim_host(bus->sdiodev->func[1]);
	brcmf_sdio_clkctl(bus, CLK_AVAIL, false);

	rstvec = get_unaligned_le32(fw->data);
	brcmf_dbg(SDIO, "firmware rstvec: %x\n", rstvec);

	bcmerror = brcmf_sdio_download_code_file(bus, fw);
	release_firmware(fw);
	if (bcmerror) {
		brcmf_err("dongle image file download failed\n");
		brcmf_fw_nvram_free(nvram);
		goto err;
	}

	bcmerror = brcmf_sdio_download_nvram(bus, nvram, nvlen);
	brcmf_fw_nvram_free(nvram);
	if (bcmerror) {
		brcmf_err("dongle nvram file download failed\n");
		goto err;
	}


	if (!brcmf_chip_set_active(bus->ci, rstvec)) {
		brcmf_err("error getting out of ARM core reset\n");
		goto err;
	}


	brcmf_sdiod_change_state(bus->sdiodev, BRCMF_SDIOD_DATA);
	bcmerror = 0;

err:
	brcmf_sdio_clkctl(bus, CLK_SDONLY, false);
	sdio_release_host(bus->sdiodev->func[1]);
	return bcmerror;
}
