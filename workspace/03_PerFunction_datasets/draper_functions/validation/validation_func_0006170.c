RemoveChildAfter(XmlChild* predecessor) {
  XmlChild* next;

  if (predecessor == NULL) {
    next = first_child_;
    first_child_ = next->next_child_;
  }
  else {
    next = predecessor->next_child_;
    predecessor->next_child_ = next->next_child_;
  }

  if (last_child_ == next)
    last_child_ = predecessor;

  delete next;
}
