trace_mask(BitGrid &mask, size_t w, size_t h, int64_t min_area, bool no_donuts) {
	if(VERBOSE >= 4) debug_write_mask(mask, w, h);

	Mpoly out_poly;

	recursive_trace(mask, w, h, make_enclosing_ring(w, h), 0, out_poly, -1, min_area, no_donuts);
	printf("Trace found %zd rings.\n", out_poly.rings.size());


	return out_poly;
}

}
