init_io_condition_met(struct nvbios_init *init, u8 cond)
{
	struct nvkm_bios *bios = init->bios;
	u16 table = init_io_condition_table(init);
	if (table) {
		u16 port = nvbios_rd16(bios, table + (cond * 5) + 0);
		u8 index = nvbios_rd08(bios, table + (cond * 5) + 2);
		u8  mask = nvbios_rd08(bios, table + (cond * 5) + 3);
		u8 value = nvbios_rd08(bios, table + (cond * 5) + 4);
		trace("\t[0x%02x] (0x%04x[0x%02x] & 0x%02x) == 0x%02x\n",
		      cond, port, index, mask, value);
		return (init_rdvgai(init, port, index) & mask) == value;
	}
	return false;
}
