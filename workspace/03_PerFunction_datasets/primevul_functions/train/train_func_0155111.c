static void update_permission_bitmask(struct kvm_mmu *mmu, bool ept)
{
	unsigned byte;

	const u8 x = BYTE_MASK(ACC_EXEC_MASK);
	const u8 w = BYTE_MASK(ACC_WRITE_MASK);
	const u8 u = BYTE_MASK(ACC_USER_MASK);

	bool cr4_smep = is_cr4_smep(mmu);
	bool cr4_smap = is_cr4_smap(mmu);
	bool cr0_wp = is_cr0_wp(mmu);
	bool efer_nx = is_efer_nx(mmu);

	for (byte = 0; byte < ARRAY_SIZE(mmu->permissions); ++byte) {
		unsigned pfec = byte << 1;


		u8 wf = (pfec & PFERR_WRITE_MASK) ? (u8)~w : 0;

		u8 uf = (pfec & PFERR_USER_MASK) ? (u8)~u : 0;

		u8 ff = (pfec & PFERR_FETCH_MASK) ? (u8)~x : 0;

		u8 smepf = 0;

		u8 smapf = 0;

		if (!ept) {

			u8 kf = (pfec & PFERR_USER_MASK) ? 0 : u;


			if (!efer_nx)
				ff = 0;


			if (!cr0_wp)
				wf = (pfec & PFERR_USER_MASK) ? wf : 0;


			if (cr4_smep)
				smepf = (pfec & PFERR_FETCH_MASK) ? kf : 0;


			if (cr4_smap)
				smapf = (pfec & (PFERR_RSVD_MASK|PFERR_FETCH_MASK)) ? 0 : kf;
		}

		mmu->permissions[byte] = ff | uf | wf | smepf | smapf;
	}
}
