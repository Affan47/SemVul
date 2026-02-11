gf100_devinit_disable(struct nvkm_devinit *init)
{
	struct nvkm_device *device = init->subdev.device;
	u32 r022500 = nvkm_rd32(device, 0x022500);
	u64 disable = 0ULL;

	if (r022500 & 0x00000001)
		disable |= (1ULL << NVKM_ENGINE_DISP);

	if (r022500 & 0x00000002) {
		disable |= (1ULL << NVKM_ENGINE_MSPDEC);
		disable |= (1ULL << NVKM_ENGINE_MSPPP);
	}

	if (r022500 & 0x00000004)
		disable |= (1ULL << NVKM_ENGINE_MSVLD);
	if (r022500 & 0x00000008)
		disable |= (1ULL << NVKM_ENGINE_MSENC);
	if (r022500 & 0x00000100)
		disable |= (1ULL << NVKM_ENGINE_CE0);
	if (r022500 & 0x00000200)
		disable |= (1ULL << NVKM_ENGINE_CE1);

	return disable;
}
