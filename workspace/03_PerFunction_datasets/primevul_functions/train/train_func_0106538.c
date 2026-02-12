static void tm_reclaim_thread(struct thread_struct *thr, uint8_t cause)
{


	if (!MSR_TM_SUSPENDED(mfmsr()))
		return;

	giveup_all(container_of(thr, struct task_struct, thread));

	tm_reclaim(thr, cause);


	if ((thr->ckpt_regs.msr & MSR_FP) == 0)
		memcpy(&thr->ckfp_state, &thr->fp_state,
		       sizeof(struct thread_fp_state));
	if ((thr->ckpt_regs.msr & MSR_VEC) == 0)
		memcpy(&thr->ckvr_state, &thr->vr_state,
		       sizeof(struct thread_vr_state));
}
