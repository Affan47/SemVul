includes (const Unit *a, const Unit *b) const {
  Map::const_iterator a_iter = _nodes.find (a);
  Map::const_iterator b_iter = _nodes.find (b);
  if (a_iter == _nodes.end () || b_iter == _nodes.end ())
    return false;
  bool result = includes (a_iter->second, b_iter->second);


  reset_visited ();

  return result;
}
