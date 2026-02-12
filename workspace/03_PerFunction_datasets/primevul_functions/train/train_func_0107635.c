static void bpf_prog_clone_free(struct bpf_prog *fp)
{


	fp->aux = NULL;
	__bpf_prog_free(fp);
}
