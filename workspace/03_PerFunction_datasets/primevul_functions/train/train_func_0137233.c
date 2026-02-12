static void bpf_link_free(struct bpf_link *link)
{
	bpf_link_free_id(link->id);
	if (link->prog) {

		link->ops->release(link);
		bpf_prog_put(link->prog);
	}

	link->ops->dealloc(link);
}
