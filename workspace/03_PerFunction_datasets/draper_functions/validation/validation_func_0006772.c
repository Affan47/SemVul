gf100_grctx_generate_r406800(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	u64 tpc_mask = 0, tpc_set = 0;
	u8  tpcnr[GPC_MAX];
	int gpc, tpc;
	int i, a, b;

	memcpy(tpcnr, gr->tpc_nr, sizeof(gr->tpc_nr));
	for (gpc = 0; gpc < gr->gpc_nr; gpc++)
		tpc_mask |= ((1ULL << gr->tpc_nr[gpc]) - 1) << (gpc * 8);

	for (i = 0, gpc = -1, b = -1; i < 32; i++) {
		a = (i * (gr->tpc_total - 1)) / 32;
		if (a != b) {
			b = a;
			do {
				gpc = (gpc + 1) % gr->gpc_nr;
			} while (!tpcnr[gpc]);
			tpc = gr->tpc_nr[gpc] - tpcnr[gpc]--;

			tpc_set |= 1ULL << ((gpc * 8) + tpc);
		}

		nvkm_wr32(device, 0x406800 + (i * 0x20), lower_32_bits(tpc_set));
		nvkm_wr32(device, 0x406c00 + (i * 0x20), lower_32_bits(tpc_set ^ tpc_mask));
		if (gr->gpc_nr > 4) {
			nvkm_wr32(device, 0x406804 + (i * 0x20), upper_32_bits(tpc_set));
			nvkm_wr32(device, 0x406c04 + (i * 0x20), upper_32_bits(tpc_set ^ tpc_mask));
		}
	}
}
