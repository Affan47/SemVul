nv50_vm_map(struct nvkm_vma *vma, struct nvkm_memory *pgt,
	    struct nvkm_mem *mem, u32 pte, u32 cnt, u64 phys, u64 delta)
{
	struct nvkm_ram *ram = vma->vm->mmu->subdev.device->fb->ram;
	u32 comp = (mem->memtype & 0x180) >> 7;
	u32 block, target;
	int i;


	target = 0;
	if (ram->stolen) {
		phys += ram->stolen;
		target = 3;
	}

	phys  = vm_addr(vma, phys, mem->memtype, target);
	pte <<= 3;
	cnt <<= 3;

	nvkm_kmap(pgt);
	while (cnt) {
		u32 offset_h = upper_32_bits(phys);
		u32 offset_l = lower_32_bits(phys);

		for (i = 7; i >= 0; i--) {
			block = 1 << (i + 3);
			if (cnt >= block && !(pte & (block - 1)))
				break;
		}
		offset_l |= (i << 7);

		phys += block << (vma->node->type - 3);
		cnt  -= block;
		if (comp) {
			u32 tag = mem->tag->offset + ((delta >> 16) * comp);
			offset_h |= (tag << 17);
			delta    += block << (vma->node->type - 3);
		}

		while (block) {
			nvkm_wo32(pgt, pte + 0, offset_l);
			nvkm_wo32(pgt, pte + 4, offset_h);
			pte += 8;
			block -= 8;
		}
	}
	nvkm_done(pgt);
}
