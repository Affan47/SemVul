static bool setup_vmgexit_scratch(struct vcpu_svm *svm, bool sync, u64 len)
{
	struct vmcb_control_area *control = &svm->vmcb->control;
	struct ghcb *ghcb = svm->ghcb;
	u64 ghcb_scratch_beg, ghcb_scratch_end;
	u64 scratch_gpa_beg, scratch_gpa_end;
	void *scratch_va;

	scratch_gpa_beg = ghcb_get_sw_scratch(ghcb);
	if (!scratch_gpa_beg) {
		pr_err("vmgexit: scratch gpa not provided\n");
		return false;
	}

	scratch_gpa_end = scratch_gpa_beg + len;
	if (scratch_gpa_end < scratch_gpa_beg) {
		pr_err("vmgexit: scratch length (%#llx) not valid for scratch address (%#llx)\n",
		       len, scratch_gpa_beg);
		return false;
	}

	if ((scratch_gpa_beg & PAGE_MASK) == control->ghcb_gpa) {

		ghcb_scratch_beg = control->ghcb_gpa +
				   offsetof(struct ghcb, shared_buffer);
		ghcb_scratch_end = control->ghcb_gpa +
				   offsetof(struct ghcb, reserved_1);


		if (scratch_gpa_beg < ghcb_scratch_beg ||
		    scratch_gpa_end > ghcb_scratch_end) {
			pr_err("vmgexit: scratch area is outside of GHCB shared buffer area (%#llx - %#llx)\n",
			       scratch_gpa_beg, scratch_gpa_end);
			return false;
		}

		scratch_va = (void *)svm->ghcb;
		scratch_va += (scratch_gpa_beg - control->ghcb_gpa);
	} else {


		if (len > GHCB_SCRATCH_AREA_LIMIT) {
			pr_err("vmgexit: scratch area exceeds KVM limits (%#llx requested, %#llx limit)\n",
			       len, GHCB_SCRATCH_AREA_LIMIT);
			return false;
		}
		scratch_va = kzalloc(len, GFP_KERNEL_ACCOUNT);
		if (!scratch_va)
			return false;

		if (kvm_read_guest(svm->vcpu.kvm, scratch_gpa_beg, scratch_va, len)) {

			pr_err("vmgexit: kvm_read_guest for scratch area failed\n");

			kfree(scratch_va);
			return false;
		}


		svm->ghcb_sa_sync = sync;
		svm->ghcb_sa_free = true;
	}

	svm->ghcb_sa = scratch_va;
	svm->ghcb_sa_len = len;

	return true;
}
