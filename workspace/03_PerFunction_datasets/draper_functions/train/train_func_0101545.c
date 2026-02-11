gk104_pmu_pgob(struct nvkm_pmu *pmu, bool enable)
{
	struct nvkm_device *device = pmu->subdev.device;

	if (!(nvkm_fuse_read(device->fuse, 0x31c) & 0x00000001))
		return;

	nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
	nvkm_rd32(device, 0x000200);
	nvkm_mask(device, 0x000200, 0x08000000, 0x08000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000002);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x020004, 0xc0000000, enable ? 0xc0000000 : 0x40000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000000);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x000200, 0x08000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
	nvkm_rd32(device, 0x000200);

	if (nvkm_boolopt(device->cfgopt, "War00C800_0", true)) {
		switch (device->chipset) {
		case 0xe4:
			magic(device, 0x04000000);
			magic(device, 0x06000000);
			magic(device, 0x0c000000);
			magic(device, 0x0e000000);
			break;
		case 0xe6:
			magic(device, 0x02000000);
			magic(device, 0x04000000);
			magic(device, 0x0a000000);
			break;
		case 0xe7:
			magic(device, 0x02000000);
			break;
		default:
			break;
		}
	}
}
