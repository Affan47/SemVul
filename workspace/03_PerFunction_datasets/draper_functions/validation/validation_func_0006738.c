find_best_spr_helper(Node *n, Node *new_sibling, Node *super_tree,
		vector<Node *> &gene_trees, Node *&best_spr_move,
		Node *&best_sibling, int &min_distance, int &num_ties, vector<pair <int, pair<int, int> > > &stats) {

	if (new_sibling == n)
		return;


	if (new_sibling->lchild() != NULL) {
		find_best_spr_helper(n, new_sibling->lchild(), super_tree,
				gene_trees, best_spr_move, best_sibling, min_distance, num_ties, stats);
	}
	if (new_sibling->rchild() != NULL) {
		find_best_spr_helper(n, new_sibling->rchild(), super_tree,
				gene_trees, best_spr_move, best_sibling, min_distance, num_ties, stats);
	}


	if (n->parent() != NULL &&
			(new_sibling == n->parent())) {


		return;
	}
	if (n->parent() != NULL &&
			new_sibling->parent() != NULL &&
			n->parent()->parent() == new_sibling->parent()) {

		return;
	}
	if (new_sibling == n->get_sibling()) {

		return;
	}


	if (n != super_tree && new_sibling != n) {
		Node *old_sibling = n->get_sibling();


		int which_sibling = 0;
		Node *undo = n->spr(new_sibling, which_sibling);
		super_tree->set_depth(0);
		super_tree->fix_depths();


		int distance;
		if (APPROX) {
			if (UNROOTED)
				distance = rSPR_total_approx_distance_unrooted(super_tree, gene_trees);
			else
				distance = rSPR_total_approx_distance(super_tree, gene_trees);
		}
		else {
			if (UNROOTED)
				distance = rSPR_total_distance_unrooted(super_tree, gene_trees);
			else
				distance = rSPR_total_distance(super_tree, gene_trees);
		}
		if(stats.size() == 0)
			stats.push_back(make_pair(0,make_pair(rSPR_total_distance(super_tree, gene_trees),rSPR_total_approx_distance(super_tree, gene_trees))));
		else
			stats.push_back(make_pair(++(stats.back().first),make_pair(rSPR_total_distance(super_tree, gene_trees),rSPR_total_approx_distance(super_tree, gene_trees))));


		if (distance < min_distance) {
			min_distance = distance;
			best_spr_move = n;
			best_sibling = new_sibling;
			num_ties = 2;
		}
		else if (distance == min_distance) {
			int r = rand();
			if (r < RAND_MAX/num_ties) {
				min_distance = distance;
				best_spr_move = n;
				best_sibling = new_sibling;
			}
			num_ties++;
		}

		n->spr(undo, which_sibling);
		super_tree->set_depth(0);
		super_tree->fix_depths();


	}

}
