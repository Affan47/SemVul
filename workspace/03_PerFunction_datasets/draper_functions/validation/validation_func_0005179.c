p_among(FlatZincSpace& s, const ConExpr& ce, AST::Node* ann) {
      IntVarArgs x = s.arg2intvarargs(ce[1]);
      IntSet v = s.arg2intset(ce[2]);
      if (ce[0]->isIntVar()) {
        IntVar n = s.arg2IntVar(ce[0]);
        count(s,x,v,IRT_EQ,n,s.ann2icl(ann));
      } else {
        count(s,x,v,IRT_EQ,ce[0]->getInt(),s.ann2icl(ann));
      }
    }
