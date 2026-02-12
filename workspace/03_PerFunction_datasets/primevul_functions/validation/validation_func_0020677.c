int arch_prepare_bpf_trampoline(struct bpf_tramp_image *im, void *image, void *image_end,
				const struct btf_func_model *m, u32 flags,
				struct bpf_tramp_progs *tprogs,
				void *orig_call)
{
	int ret, i, cnt = 0, nr_args = m->nr_args;
	int stack_size = nr_args * 8;
	struct bpf_tramp_progs *fentry = &tprogs[BPF_TRAMP_FENTRY];
	struct bpf_tramp_progs *fexit = &tprogs[BPF_TRAMP_FEXIT];
	struct bpf_tramp_progs *fmod_ret = &tprogs[BPF_TRAMP_MODIFY_RETURN];
	u8 **branches = NULL;
	u8 *prog;


	if (nr_args > 6)
		return -ENOTSUPP;

	if ((flags & BPF_TRAMP_F_RESTORE_REGS) &&
	    (flags & BPF_TRAMP_F_SKIP_FRAME))
		return -EINVAL;

	if (flags & BPF_TRAMP_F_CALL_ORIG)
		stack_size += 8;

	if (flags & BPF_TRAMP_F_SKIP_FRAME)


		orig_call += X86_PATCH_SIZE;

	prog = image;

	EMIT1(0x55);
	EMIT3(0x48, 0x89, 0xE5);
	EMIT4(0x48, 0x83, 0xEC, stack_size);
	EMIT1(0x53);

	save_regs(m, &prog, nr_args, stack_size);

	if (flags & BPF_TRAMP_F_CALL_ORIG) {

		emit_mov_imm64(&prog, BPF_REG_1, (long) im >> 32, (u32) (long) im);
		if (emit_call(&prog, __bpf_tramp_enter, prog)) {
			ret = -EINVAL;
			goto cleanup;
		}
	}

	if (fentry->nr_progs)
		if (invoke_bpf(m, &prog, fentry, stack_size))
			return -EINVAL;

	if (fmod_ret->nr_progs) {
		branches = kcalloc(fmod_ret->nr_progs, sizeof(u8 *),
				   GFP_KERNEL);
		if (!branches)
			return -ENOMEM;

		if (invoke_bpf_mod_ret(m, &prog, fmod_ret, stack_size,
				       branches)) {
			ret = -EINVAL;
			goto cleanup;
		}
	}

	if (flags & BPF_TRAMP_F_CALL_ORIG) {
		restore_regs(m, &prog, nr_args, stack_size);


		if (emit_call(&prog, orig_call, prog)) {
			ret = -EINVAL;
			goto cleanup;
		}

		emit_stx(&prog, BPF_DW, BPF_REG_FP, BPF_REG_0, -8);
		im->ip_after_call = prog;
		memcpy(prog, ideal_nops[NOP_ATOMIC5], X86_PATCH_SIZE);
		prog += X86_PATCH_SIZE;
	}

	if (fmod_ret->nr_progs) {


		emit_align(&prog, 16);


		for (i = 0; i < fmod_ret->nr_progs; i++)
			emit_cond_near_jump(&branches[i], prog, branches[i],
					    X86_JNE);
	}

	if (fexit->nr_progs)
		if (invoke_bpf(m, &prog, fexit, stack_size)) {
			ret = -EINVAL;
			goto cleanup;
		}

	if (flags & BPF_TRAMP_F_RESTORE_REGS)
		restore_regs(m, &prog, nr_args, stack_size);


	if (flags & BPF_TRAMP_F_CALL_ORIG) {
		im->ip_epilogue = prog;

		emit_mov_imm64(&prog, BPF_REG_1, (long) im >> 32, (u32) (long) im);
		if (emit_call(&prog, __bpf_tramp_exit, prog)) {
			ret = -EINVAL;
			goto cleanup;
		}

		emit_ldx(&prog, BPF_DW, BPF_REG_0, BPF_REG_FP, -8);
	}

	EMIT1(0x5B);
	EMIT1(0xC9);
	if (flags & BPF_TRAMP_F_SKIP_FRAME)

		EMIT4(0x48, 0x83, 0xC4, 8);
	EMIT1(0xC3);

	if (WARN_ON_ONCE(prog > (u8 *)image_end - BPF_INSN_SAFETY)) {
		ret = -EFAULT;
		goto cleanup;
	}
	ret = prog - (u8 *)image;

cleanup:
	kfree(branches);
	return ret;
}
