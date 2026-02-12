void sev_es_prepare_guest_switch(struct vcpu_svm *svm, unsigned int cpu)
{
	struct svm_cpu_data *sd = per_cpu(svm_data, cpu);
	struct vmcb_save_area *hostsa;


	vmsave(__sme_page_pa(sd->save_area));


	hostsa = (struct vmcb_save_area *)(page_address(sd->save_area) + 0x400);
	hostsa->xcr0 = xgetbv(XCR_XFEATURE_ENABLED_MASK);


	hostsa->pkru = read_pkru();


	hostsa->xss = host_xss;
}
