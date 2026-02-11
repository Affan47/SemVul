nv31_mpeg_mthd_dma(struct nvkm_device *device, u32 mthd, u32 data)
{
	u32 inst = data << 4;
	u32 dma0 = nvkm_rd32(device, 0x700000 + inst);
	u32 dma1 = nvkm_rd32(device, 0x700004 + inst);
	u32 dma2 = nvkm_rd32(device, 0x700008 + inst);
	u32 base = (dma2 & 0xfffff000) | (dma0 >> 20);
	u32 size = dma1 + 1;


	if (!(dma0 & 0x00002000))
		return false;

	if (mthd == 0x0190) {

		nvkm_mask(device, 0x00b300, 0x00010000,
				  (dma0 & 0x00030000) ? 0x00010000 : 0);
		nvkm_wr32(device, 0x00b334, base);
		nvkm_wr32(device, 0x00b324, size);
	} else
	if (mthd == 0x01a0) {

		nvkm_mask(device, 0x00b300, 0x00020000,
				  (dma0 & 0x00030000) ? 0x00020000 : 0);
		nvkm_wr32(device, 0x00b360, base);
		nvkm_wr32(device, 0x00b364, size);
	} else {

		if (dma0 & 0x00030000)
			return false;

		nvkm_wr32(device, 0x00b370, base);
		nvkm_wr32(device, 0x00b374, size);
	}

	return true;
}
