vector_ps_float(const VectorSparse& v1, float* v2, size_t dim) {
	double s = 0;
	for(auto i1 = v1.entries.begin(); i1!=v1.entries.end(); i1++) {


		s += (*i1).val * v2[(*i1).i];

	}
	return s;
}
