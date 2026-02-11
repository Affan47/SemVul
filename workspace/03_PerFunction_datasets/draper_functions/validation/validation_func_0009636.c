z_decomp_free(void *arg)
{
	struct ppp_deflate_state *state = (struct ppp_deflate_state *) arg;

	if (state) {
		zlib_inflateEnd(&state->strm);
		vfree(state->strm.workspace);
		kfree(state);
	}
}
