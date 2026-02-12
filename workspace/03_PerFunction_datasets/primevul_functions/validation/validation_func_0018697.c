static void pre_sev_run(struct vcpu_svm *svm, int cpu)
{
	struct svm_cpu_data *sd = per_cpu(svm_data, cpu);
	int asid = sev_get_asid(svm->vcpu.kvm);


	svm->vmcb->control.asid = asid;


	if (sd->sev_vmcbs[asid] == svm->vmcb &&
	    svm->last_cpu == cpu)
		return;

	svm->last_cpu = cpu;
	sd->sev_vmcbs[asid] = svm->vmcb;
	svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ASID;
	mark_dirty(svm->vmcb, VMCB_ASID);
}
