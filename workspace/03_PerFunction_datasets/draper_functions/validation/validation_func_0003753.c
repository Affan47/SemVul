EdgeByDir(int n, boolean out_edge) const {
  TopoNode* toponode = Node();
  if (toponode) {
    Iterator it;
    toponode->first(it);
    while (!toponode->done(it)) {
      TopoEdge* edge = toponode->get_edge(it);
      if (edge &&

	  (out_edge?edge->start_node():edge->end_node())==toponode)
	n--;
      if (!n) return (EdgeComp*)edge->value();
      toponode->next(it);
    }
  }
  return nil;
}
