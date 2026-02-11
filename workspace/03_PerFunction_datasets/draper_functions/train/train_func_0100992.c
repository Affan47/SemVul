vb2_plane_vaddr(struct vb2_buffer *vb, unsigned int plane_no)
{
	if (plane_no >= vb->num_planes || !vb->planes[plane_no].mem_priv)
		return NULL;

	return call_ptr_memop(vb, vaddr, vb->planes[plane_no].mem_priv);

}
