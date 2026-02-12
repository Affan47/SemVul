static int bpf_tracing_prog_attach(struct bpf_prog *prog,
				   int tgt_prog_fd,
				   u32 btf_id)
{
	struct bpf_link_primer link_primer;
	struct bpf_prog *tgt_prog = NULL;
	struct bpf_trampoline *tr = NULL;
	struct bpf_tracing_link *link;
	u64 key = 0;
	int err;

	switch (prog->type) {
	case BPF_PROG_TYPE_TRACING:
		if (prog->expected_attach_type != BPF_TRACE_FENTRY &&
		    prog->expected_attach_type != BPF_TRACE_FEXIT &&
		    prog->expected_attach_type != BPF_MODIFY_RETURN) {
			err = -EINVAL;
			goto out_put_prog;
		}
		break;
	case BPF_PROG_TYPE_EXT:
		if (prog->expected_attach_type != 0) {
			err = -EINVAL;
			goto out_put_prog;
		}
		break;
	case BPF_PROG_TYPE_LSM:
		if (prog->expected_attach_type != BPF_LSM_MAC) {
			err = -EINVAL;
			goto out_put_prog;
		}
		break;
	default:
		err = -EINVAL;
		goto out_put_prog;
	}

	if (!!tgt_prog_fd != !!btf_id) {
		err = -EINVAL;
		goto out_put_prog;
	}

	if (tgt_prog_fd) {

		if (prog->type != BPF_PROG_TYPE_EXT) {
			err = -EINVAL;
			goto out_put_prog;
		}

		tgt_prog = bpf_prog_get(tgt_prog_fd);
		if (IS_ERR(tgt_prog)) {
			err = PTR_ERR(tgt_prog);
			tgt_prog = NULL;
			goto out_put_prog;
		}

		key = bpf_trampoline_compute_key(tgt_prog, NULL, btf_id);
	}

	link = kzalloc(sizeof(*link), GFP_USER);
	if (!link) {
		err = -ENOMEM;
		goto out_put_prog;
	}
	bpf_link_init(&link->link, BPF_LINK_TYPE_TRACING,
		      &bpf_tracing_link_lops, prog);
	link->attach_type = prog->expected_attach_type;

	mutex_lock(&prog->aux->dst_mutex);


	if (!prog->aux->dst_trampoline && !tgt_prog) {
		err = -ENOENT;
		goto out_unlock;
	}

	if (!prog->aux->dst_trampoline ||
	    (key && key != prog->aux->dst_trampoline->key)) {


		struct bpf_attach_target_info tgt_info = {};

		err = bpf_check_attach_target(NULL, prog, tgt_prog, btf_id,
					      &tgt_info);
		if (err)
			goto out_unlock;

		tr = bpf_trampoline_get(key, &tgt_info);
		if (!tr) {
			err = -ENOMEM;
			goto out_unlock;
		}
	} else {


		tr = prog->aux->dst_trampoline;
		tgt_prog = prog->aux->dst_prog;
	}

	err = bpf_link_prime(&link->link, &link_primer);
	if (err)
		goto out_unlock;

	err = bpf_trampoline_link_prog(prog, tr);
	if (err) {
		bpf_link_cleanup(&link_primer);
		link = NULL;
		goto out_unlock;
	}

	link->tgt_prog = tgt_prog;
	link->trampoline = tr;


	if (prog->aux->dst_prog &&
	    (tgt_prog_fd || tr != prog->aux->dst_trampoline))

		bpf_prog_put(prog->aux->dst_prog);
	if (prog->aux->dst_trampoline && tr != prog->aux->dst_trampoline)

		bpf_trampoline_put(prog->aux->dst_trampoline);

	prog->aux->dst_prog = NULL;
	prog->aux->dst_trampoline = NULL;
	mutex_unlock(&prog->aux->dst_mutex);

	return bpf_link_settle(&link_primer);
out_unlock:
	if (tr && tr != prog->aux->dst_trampoline)
		bpf_trampoline_put(tr);
	mutex_unlock(&prog->aux->dst_mutex);
	kfree(link);
out_put_prog:
	if (tgt_prog_fd && tgt_prog)
		bpf_prog_put(tgt_prog);
	return err;
}
