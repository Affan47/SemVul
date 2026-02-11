scif_rb_count(struct scif_rb *rb, u32 size)
{
	if (scif_rb_ring_cnt(rb->current_write_offset,
			     rb->current_read_offset,
			     rb->size) < size) {
		rb->current_write_offset = *rb->write_ptr;


		smp_rmb();
	}
	return scif_rb_ring_cnt(rb->current_write_offset,
				rb->current_read_offset,
				rb->size);
}
