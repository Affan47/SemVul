void GraphConstructor::PrintCycles() {
  int num_nodes = outputs_.size();
  absl::flat_hash_set<int> unvisited;
  for (int i = 0; i < num_nodes; i++) {
    unvisited.insert(i);
  }
  while (!unvisited.empty()) {
    int cur_node = *unvisited.begin();


    std::vector<int> cur_branch;


    std::vector<bool> is_on_cur_branch(num_nodes, false);
    DFS(cur_node, &cur_branch, &is_on_cur_branch, &unvisited);
  }
}
