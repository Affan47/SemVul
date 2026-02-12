static inline RBinWasmTypeVec *parse_type_vector(RBuffer *b, ut64 bound) {
	RBinWasmTypeVec *vec = R_NEW0 (RBinWasmTypeVec);

	if (vec && !consume_str_new (b, bound, &vec->count, (char **)&vec->types)) {
		free_type_vec (vec);
		return NULL;
	}
	return vec;
}
