sh_veu_querybuf(struct file *file, void *priv,
			   struct v4l2_buffer *buf)
{
	struct sh_veu_file *veu_file = priv;

	if (!sh_veu_is_streamer(veu_file->veu_dev, veu_file, buf->type))
		return -EBUSY;

	return v4l2_m2m_querybuf(file, veu_file->veu_dev->m2m_ctx, buf);
}
