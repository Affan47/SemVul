void bpf_prog_sub(struct bpf_prog *prog, int i)
{


	WARN_ON(atomic64_sub_return(i, &prog->aux->refcnt) == 0);
}
