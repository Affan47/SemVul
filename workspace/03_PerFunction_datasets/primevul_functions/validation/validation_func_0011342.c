static int kvm_s390_cpus_from_pv(struct kvm *kvm, u16 *rcp, u16 *rrcp)
{
	struct kvm_vcpu *vcpu;
	u16 rc, rrc;
	int ret = 0;
	int i;


	kvm_for_each_vcpu(i, vcpu, kvm) {
		mutex_lock(&vcpu->mutex);
		if (kvm_s390_pv_destroy_cpu(vcpu, &rc, &rrc) && !ret) {
			*rcp = rc;
			*rrcp = rrc;
			ret = -EIO;
		}
		mutex_unlock(&vcpu->mutex);
	}
	return ret;
}
