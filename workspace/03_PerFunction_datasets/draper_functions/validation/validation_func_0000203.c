murrine_get_frame_gap_clip (int x, int y, int width, int height,
                            const FrameParameters *frame,
                            MurrineRectangle      *bevel,
                            MurrineRectangle      *border)
{
	switch (frame->gap_side)
	{
		case MRN_GAP_TOP:
			MURRINE_RECTANGLE_SET ((*bevel),  1.5+frame->gap_x, -0.5,
			                       frame->gap_width-3, 2.0);
			MURRINE_RECTANGLE_SET ((*border), 0.5+frame->gap_x, -0.5,
			                       frame->gap_width-2, 2.0);
			break;
		case MRN_GAP_BOTTOM:
			MURRINE_RECTANGLE_SET ((*bevel),  1.5+frame->gap_x, height-2.5,
			                       frame->gap_width-3, 2.0);
			MURRINE_RECTANGLE_SET ((*border), 0.5+frame->gap_x, height-1.5,
			                       frame->gap_width-2, 2.0);
			break;
		case MRN_GAP_LEFT:
			MURRINE_RECTANGLE_SET ((*bevel),  -0.5, 1.5+frame->gap_x,
			                       2.0, frame->gap_width-3);
			MURRINE_RECTANGLE_SET ((*border), -0.5, 0.5+frame->gap_x,
			                       1.0, frame->gap_width-2);
			break;
		case MRN_GAP_RIGHT:
			MURRINE_RECTANGLE_SET ((*bevel),  width-2.5, 1.5+frame->gap_x,
			                       2.0, frame->gap_width-3);
			MURRINE_RECTANGLE_SET ((*border), width-1.5, 0.5+frame->gap_x,
			                       1.0, frame->gap_width-2);
			break;
	}
}
