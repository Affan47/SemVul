insert_child_before(xml_node_type type_, const xml_node& node)
	{
		if (!impl::allow_insert_child(this->type(), type_)) return xml_node();
		if (!node._root || node._root->parent != _root) return xml_node();

		xml_node n(impl::allocate_node(impl::get_allocator(_root), type_));
		if (!n) return xml_node();

		n._root->parent = _root;

		if (node._root->prev_sibling_c->next_sibling)
			node._root->prev_sibling_c->next_sibling = n._root;
		else
			_root->first_child = n._root;

		n._root->prev_sibling_c = node._root->prev_sibling_c;
		n._root->next_sibling = node._root;
		node._root->prev_sibling_c = n._root;

		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));

		return n;
	}
