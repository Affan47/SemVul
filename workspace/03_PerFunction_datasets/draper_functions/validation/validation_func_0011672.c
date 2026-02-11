get_options(MethodParams& params, size_t index){
	return (params.count()>index) ? params.as_hash(index) : 0;
}
