compute_reduced_ring(const Ring &orig_string, double res) {


	const std::vector<Vertex> &pts_in = orig_string.pts;
	const size_t num_in = pts_in.size();

	double tolerance = res;
	int i;

	std::vector<segment_t> stack(num_in);
	size_t stack_ptr = 0;

	ReducedRing keep;
	keep.segs.reserve(num_in);


	keep.segs.push_back(segment_t(num_in-1, 0));

	stack[stack_ptr].begin = 0;
	stack[stack_ptr].end = num_in-1;
	stack_ptr++;
	while(stack_ptr) {
		stack_ptr--;
		int seg_begin = stack[stack_ptr].begin;
		int seg_end = stack[stack_ptr].end;


		double max_dist = -1.0;
		int idx_of_max = -1;

		double seg_vec_x = pts_in[seg_end].x - pts_in[seg_begin].x;
		double seg_vec_y = pts_in[seg_end].y - pts_in[seg_begin].y;
		double seg_vec_len = veclen(seg_vec_x, seg_vec_y);
		if(seg_vec_len > 0.0) {

			seg_vec_x /= seg_vec_len;
			seg_vec_y /= seg_vec_len;
			for(i=seg_begin+1; i<seg_end; i++) {
				double dist_to_seg = get_dist_to_seg(seg_vec_x, seg_vec_y,
					pts_in[seg_begin], pts_in[seg_end], pts_in[i]);
				if(dist_to_seg < 0.0) fatal_error("dist_to_seg < 0.0");
				if(std::isnan(dist_to_seg)) fatal_error("dist_to_seg == NaN");

				if(dist_to_seg > max_dist) {
					max_dist = dist_to_seg;
					idx_of_max = i;
				}
			}
		} else {


			for(i=seg_begin+1; i<seg_end; i++) {
				double dx = pts_in[i].x - pts_in[seg_begin].x;
				double dy = pts_in[i].y - pts_in[seg_begin].y;
				double dist_to_seg = veclen(dx, dy);

				if(dist_to_seg > max_dist) {
					max_dist = dist_to_seg;
					idx_of_max = i;
				}
			}
		}


		if(max_dist >= tolerance) {
			if(idx_of_max <= 0) fatal_error(
				"idx_of_max out of range (perhaps it wasn't set?)");


			stack[stack_ptr].begin = seg_begin;
			stack[stack_ptr].end = idx_of_max;
			stack_ptr++;
			if(stack_ptr >= num_in) fatal_error("stack overflow in dp.c");

			stack[stack_ptr].begin = idx_of_max;
			stack[stack_ptr].end = seg_end;
			stack_ptr++;
			if(stack_ptr >= num_in) fatal_error("stack overflow in dp.c");
		} else {


			if(keep.segs.size() == num_in) fatal_error("output stack overflow in dp.c");
			keep.segs.push_back(segment_t(seg_begin, seg_end));
		}
	}


	return keep;
}
