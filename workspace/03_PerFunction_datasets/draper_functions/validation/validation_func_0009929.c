nvkm_mc_intr_mask(struct nvkm_mc *mc)
{
	u32 intr = mc->func->intr_mask(mc);
	if (WARN_ON_ONCE(intr == 0xffffffff))
		intr = 0;
	return intr;
}
