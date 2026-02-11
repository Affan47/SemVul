constantKids(const Expr& e, vector<int>& idxs) {
  for(int i=0, iend=e.arity(); i<iend; ++i)
    if(e[i].getKind() == BVCONST) idxs.push_back(i);
}
