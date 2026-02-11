getMapDefaultValueForType(int type) {
    if (gm_is_float_type(type)) {
        return "0.0";
    } else if (gm_is_integer_type(type)) {
        return "0";
    } else if (gm_is_boolean_type(type)) {
        return "false";
    } else if (gm_is_node_type(type)) {
        return "gm_graph::NIL_NODE";
    } else if (gm_is_edge_type(type)) {
        return "gm_graph::NIL_EDGE";
    } else {

        assert(false);
    }
    return NULL;
}
