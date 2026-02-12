const Edge* Graph::AddEdge(Node* source, int x, Node* dest, int y) {
  TF_DCHECK_OK(IsValidNode(source)) << source->DebugString();
  TF_DCHECK_OK(IsValidNode(dest)) << dest->DebugString();


  if (source == source_node() || dest == sink_node() || x == kControlSlot ||
      y == kControlSlot) {
    DCHECK_EQ(x, kControlSlot) << source->DebugString();
    DCHECK_EQ(y, kControlSlot) << dest->DebugString();
  }

  Edge* e = nullptr;
  if (free_edges_.empty()) {
    e = new (arena_.Alloc(sizeof(Edge))) Edge;
  } else {
    e = free_edges_.back();
    free_edges_.pop_back();
  }
  e->id_ = edges_.size();
  e->src_ = source;
  e->dst_ = dest;
  e->src_output_ = x;
  e->dst_input_ = y;
  CHECK(source->out_edges_.insert(e).second);
  CHECK(dest->in_edges_.insert(e).second);
  edges_.push_back(e);
  ++num_edges_;

  if (!e->IsControlEdge()) {
    if (dest->in_edges_.size() >= dest->props_->input_types.size()) {


      dest->RunForwardTypeInference();
    }
  }

  return e;
}
