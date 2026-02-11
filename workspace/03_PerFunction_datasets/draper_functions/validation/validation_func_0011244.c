rectangle_check_changes(GF_Node *node, Drawable *stack, GF_TraverseState *tr_state)
{


	if (gf_node_dirty_get(node)) {
		drawable_reset_path(stack);
		gf_path_add_rect_center(stack->path, 0, 0, ((M_Rectangle *) node)->size.x, ((M_Rectangle *) node)->size.y);
		gf_node_dirty_clear(node, 0);
		drawable_mark_modified(stack, tr_state);
	}
}
