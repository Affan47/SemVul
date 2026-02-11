tocharset (TTree *tree, Charset *cs) {
  switch (tree->tag) {
    case TSet: {
      loopset(i, cs->cs[i] = treebuffer(tree)[i]);
      return 1;
    }
    case TChar: {
      assert(0 <= tree->u.n && tree->u.n <= UCHAR_MAX);
      loopset(i, cs->cs[i] = 0);
      setchar(cs->cs, tree->u.n);
      return 1;
    }
    case TAny: {
      loopset(i, cs->cs[i] = 0xFF);
      return 1;
    }
    default: return 0;
  }
}
