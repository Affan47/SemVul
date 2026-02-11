IdentifyWeakHandles(WeakSlotCallback f) {
  for (Node* current = head_; current != NULL; current = current->next()) {
    if (current->state_ == Node::WEAK) {
      if (f(&current->object_)) {
        current->state_ = Node::PENDING;
        LOG(HandleEvent("GlobalHandle::Pending", current->handle().location()));
      }
    }
  }
}
