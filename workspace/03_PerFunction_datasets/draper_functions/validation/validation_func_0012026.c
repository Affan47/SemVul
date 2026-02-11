ReadChildren (istream& in, void* addr1, void* addr2, void* addr3, void* addr4) {
  OverlayComp* child = nil;
  GraphComp* comps = (GraphComp*)addr1;
  int num_edge = comps->GetNumEdge();
  int num_node = comps->GetNumNode();

  int startnode[num_edge];
  int endnode[num_edge];
  EdgeComp* edges[num_edge];
  NodeComp* nodes[num_node];
  int edge_cnt = 0;
  int node_cnt = 0;

  char buf[BUFSIZ];

  while (in.good()) {
    if (read_name(in, buf, BUFSIZ)) break;

    int status;
    if (status = read_gsptspic(buf, in, comps)) {
      if (status==-1) break;
    }

    else if (strcmp(buf, "node") == 0) {
      child = new NodeComp(in, comps);
      nodes[node_cnt] = (NodeComp*)child;
      node_cnt++;
    }

    else if (strcmp(buf, "edge") == 0) {
      child = new EdgeComp(in, comps);
      EdgeComp* comp = (EdgeComp*)child;
      startnode[edge_cnt] = comp->GetStartNode();
      endnode[edge_cnt] = comp->GetEndNode();
      edges[edge_cnt] = comp;
      edge_cnt++;
    }

    else {
      child = read_obj(buf, in, comps);
      if (!child) return -1;
    }

    if (child) {
      if (in.good() && child->valid()) {
	comps->Append(child);
      } else {

	delete child;
	return -1;
      }
    }
  }
  for (int i=0; i<num_edge; i++) {
    int start_id = startnode[i];
    int end_id = endnode[i];
    if (start_id < 0 || end_id < 0)
      comps->AppendEdge(edges[i]);
    edges[i]->AttachNodes(start_id < 0 ? nil : nodes[start_id],
			  end_id < 0 ? nil : nodes[end_id]);
  }
  return 0;
}
