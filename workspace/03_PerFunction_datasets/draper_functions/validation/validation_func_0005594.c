has_aa_term(Design*des, NetScope*scope)
{
      bool flag = false;
      for (unsigned idx = 0 ; idx < expr_.count() ; idx += 1) {
	    flag = expr_[idx]->has_aa_term(des, scope) || flag;
      }
      return flag;
}
