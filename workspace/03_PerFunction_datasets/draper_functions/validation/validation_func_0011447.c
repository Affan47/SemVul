draw_frame_row (GdkPixbuf *frame_image, int target_width, int source_width, int source_v_position, int dest_v_position, GdkPixbuf *result_pixbuf, int left_offset, int height)
{
	int remaining_width, h_offset, slab_width;

	remaining_width = target_width;
	h_offset = 0;
	while (remaining_width > 0) {
		slab_width = remaining_width > source_width ? source_width : remaining_width;
		gdk_pixbuf_copy_area (frame_image, left_offset, source_v_position, slab_width, height, result_pixbuf, left_offset + h_offset, dest_v_position);
		remaining_width -= slab_width;
		h_offset += slab_width;
	}
}
