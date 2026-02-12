R_API ut64 r_bin_java_element_value_calc_size(RBinJavaElementValue *element_value) {
	RListIter *iter, *iter_tmp;
	RBinJavaElementValue *ev_element;
	RBinJavaElementValuePair *evps;
	ut64 sz = 0;
	if (element_value == NULL) {
		return sz;
	}

	sz += 1;
	switch (element_value->tag) {
	case R_BIN_JAVA_EV_TAG_BYTE:
	case R_BIN_JAVA_EV_TAG_CHAR:
	case R_BIN_JAVA_EV_TAG_DOUBLE:
	case R_BIN_JAVA_EV_TAG_FLOAT:
	case R_BIN_JAVA_EV_TAG_INT:
	case R_BIN_JAVA_EV_TAG_LONG:
	case R_BIN_JAVA_EV_TAG_SHORT:
	case R_BIN_JAVA_EV_TAG_BOOLEAN:
	case R_BIN_JAVA_EV_TAG_STRING:


		sz += 2;
		break;
	case R_BIN_JAVA_EV_TAG_ENUM:


		sz += 2;


		sz += 2;
		break;
	case R_BIN_JAVA_EV_TAG_CLASS:


		sz += 2;
		break;
	case R_BIN_JAVA_EV_TAG_ARRAY:


		sz += 2;
		r_list_foreach_safe (element_value->value.array_value.values, iter, iter_tmp, ev_element) {
			if (ev_element) {
				sz += r_bin_java_element_value_calc_size (ev_element);
			}
		}
		break;
	case R_BIN_JAVA_EV_TAG_ANNOTATION:


		sz += 2;


		sz += 2;
		element_value->value.annotation_value.element_value_pairs = r_list_newf (r_bin_java_element_pair_free);
		r_list_foreach_safe (element_value->value.annotation_value.element_value_pairs, iter, iter_tmp, evps) {
			if (evps) {
				sz += r_bin_java_element_pair_calc_size (evps);
			}
		}
		break;
	default:

		break;
	}
	return sz;
}
