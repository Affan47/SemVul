static int var_comparator(const RAnalVar *a, const RAnalVar *b){

	return (a && b)? (a->delta > b->delta) - (a->delta < b->delta) : 0;
}
