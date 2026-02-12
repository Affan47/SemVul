void ClassHierarchyIterator::next() {
  assert(_current != NULL, "required");
  if (_visit_subclasses && _current->subklass() != NULL) {
    _current = _current->subklass();
    return;
  }
  _visit_subclasses = true;
  while (_current->next_sibling() == NULL && _current != _root) {
    _current = _current->superklass();
  }
  if (_current == _root) {

    _current = NULL;
    return;
  }
  _current = _current->next_sibling();
  return;
}
