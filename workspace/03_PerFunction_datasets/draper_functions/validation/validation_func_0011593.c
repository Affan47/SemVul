F_gt(struct alisp_instance *instance, struct alisp_object * args)
{
	struct alisp_object * p1, * p2;

	p1 = eval(instance, car(args));
	p2 = eval(instance, car(cdr(args)));
	delete_tree(instance, cdr(cdr(args)));
	delete_object(instance, cdr(args));
	delete_object(instance, args);

	if (alisp_compare_type(p1, ALISP_OBJ_INTEGER) &&
	    alisp_compare_type(p2, ALISP_OBJ_INTEGER)) {
		if (p1->value.i > p2->value.i) {
		      __true:
			delete_tree(instance, p1);
			delete_tree(instance, p2);
			return &alsa_lisp_t;
		}
	} else if ((alisp_compare_type(p1, ALISP_OBJ_INTEGER) ||
	            alisp_compare_type(p1, ALISP_OBJ_FLOAT)) &&
		   (alisp_compare_type(p2, ALISP_OBJ_INTEGER) ||
		    alisp_compare_type(p2, ALISP_OBJ_FLOAT))) {
		double f1, f2;
		f1 = alisp_compare_type(p1, ALISP_OBJ_INTEGER) ? p1->value.i : p1->value.f;
		f2 = alisp_compare_type(p2, ALISP_OBJ_INTEGER) ? p2->value.i : p2->value.f;
		if (f1 > f2)
			goto __true;
	} else {
		lisp_warn(instance, "comparison with a non integer or float operand");
	}

	delete_tree(instance, p1);
	delete_tree(instance, p2);
	return &alsa_lisp_nil;
}
