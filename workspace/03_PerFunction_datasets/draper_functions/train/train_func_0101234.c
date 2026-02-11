nv04_update_arb(struct drm_device *dev, int VClk, int bpp,
		int *burst, int *lwm)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvif_object *device = &nouveau_drm(dev)->device.object;
	struct nv_fifo_info fifo_data;
	struct nv_sim_state sim_data;
	int MClk = nouveau_hw_get_clock(dev, PLL_MEMORY);
	int NVClk = nouveau_hw_get_clock(dev, PLL_CORE);
	uint32_t cfg1 = nvif_rd32(device, NV04_PFB_CFG1);

	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	sim_data.bpp = bpp;
	sim_data.two_heads = nv_two_heads(dev);
	if ((dev->pdev->device & 0xffff) == 0x01a0  ||
	    (dev->pdev->device & 0xffff) == 0x01f0 ) {
		uint32_t type;

		pci_read_config_dword(pci_get_bus_and_slot(0, 1), 0x7c, &type);

		sim_data.memory_type = (type >> 12) & 1;
		sim_data.memory_width = 64;
		sim_data.mem_latency = 3;
		sim_data.mem_page_miss = 10;
	} else {
		sim_data.memory_type = nvif_rd32(device, NV04_PFB_CFG0) & 0x1;
		sim_data.memory_width = (nvif_rd32(device, NV_PEXTDEV_BOOT_0) & 0x10) ? 128 : 64;
		sim_data.mem_latency = cfg1 & 0xf;
		sim_data.mem_page_miss = ((cfg1 >> 4) & 0xf) + ((cfg1 >> 31) & 0x1);
	}

	if (drm->device.info.family == NV_DEVICE_INFO_V0_TNT)
		nv04_calc_arb(&fifo_data, &sim_data);
	else
		nv10_calc_arb(&fifo_data, &sim_data);

	*burst = ilog2(fifo_data.burst >> 4);
	*lwm = fifo_data.lwm >> 3;
}
