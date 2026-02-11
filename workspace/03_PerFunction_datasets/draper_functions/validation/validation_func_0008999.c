init_copy(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u8 shift = nvbios_rd08(bios, init->offset + 5);
	u8 smask = nvbios_rd08(bios, init->offset + 6);
	u16 port = nvbios_rd16(bios, init->offset + 7);
	u8 index = nvbios_rd08(bios, init->offset + 9);
	u8  mask = nvbios_rd08(bios, init->offset + 10);
	u8  data;

	trace("COPY\t0x%04x[0x%02x] &= 0x%02x |= "
	      "((R[0x%06x] %s 0x%02x) & 0x%02x)\n",
	      port, index, mask, reg, (shift & 0x80) ? "<<" : ">>",
	      (shift & 0x80) ? (0x100 - shift) : shift, smask);
	init->offset += 11;

	data  = init_rdvgai(init, port, index) & mask;
	data |= init_shift(init_rd32(init, reg), shift) & smask;
	init_wrvgai(init, port, index, data);
}
