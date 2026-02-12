static void nested_svm_copy_common_state(struct vmcb *from_vmcb, struct vmcb *to_vmcb)
{


	to_vmcb->save.spec_ctrl = from_vmcb->save.spec_ctrl;
}
