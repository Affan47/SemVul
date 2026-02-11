get_support(Node *n, Node *super_tree, vector<Node *> *gene_trees) {
	if (!n->is_leaf() ){
		list<Node *>::iterator c;
		for(c = n->get_children().begin(); c != n->get_children().end(); c++) {
			get_support(*c, super_tree, gene_trees);
		}

		if (n != super_tree) {

			int count = 0;
			double root_avg_acc = 0;
			Node *temp_tree = new Node(*super_tree);
			temp_tree->reroot(temp_tree->find_by_prenum(n->get_preorder_number()));
			temp_tree->set_depth(0);
			temp_tree->fix_depths();
			temp_tree->preorder_number();
			int end = gene_trees->size();
			#pragma omp parallel for schedule(static) reduction(+: root_avg_acc) reduction(+: count)
			for(int i = 0; i < end; i++) {
				(*gene_trees)[i]->preorder_number();
				double acc = find_best_root_acc(temp_tree, (*gene_trees)[i]);
				if (acc > -1) {
					root_avg_acc += acc;
					count++;
				}
			}
			if (count > 0)
				root_avg_acc /= count;
			root_avg_acc /= 2.0;
			n->set_support(root_avg_acc);
			temp_tree->delete_tree();
		}
	}
}
