void bpf_jit_prog_release_other(struct bpf_prog *fp, struct bpf_prog *fp_other)
{


	fp->aux->prog = fp;
	bpf_prog_clone_free(fp_other);
}
