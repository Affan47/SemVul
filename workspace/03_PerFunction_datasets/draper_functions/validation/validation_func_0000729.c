canonCombineLikeTerms(const std::vector<Expr> & sumExprs)
{
  Rational constant = 0;
  MonomMap sumHashMap;
  vector<Expr> sumKids;


  std::vector<Expr>::const_iterator i = sumExprs.begin();
  for (; i != sumExprs.end(); ++i) {
    Expr mul = *i;
    if (mul.isRational()) {
      constant = constant + mul.getRational();
    }
    else {
      switch (mul.getKind()) {
      case MULT: {
        std::vector<Expr> mulKids;
        DebugAssert(mul.arity() > 1 && mul[0].isRational(),"");
        mulKids.push_back(rat(1));
        Expr::iterator j = mul.begin();
        ++j;
        for (; j!= mul.end(); ++j) {
          mulKids.push_back(*j);
        }


        Expr tempExpr = mulKids.size() > 2 ? multExpr(mulKids): mulKids[1];
	MonomMap::iterator i=sumHashMap.find(tempExpr);
        if (i == sumHashMap.end()) {
          sumHashMap[tempExpr] = mul[0].getRational();
        }
        else {
          (*i).second += mul[0].getRational();
        }
      }
        break;
      default: {
	MonomMap::iterator i=sumHashMap.find(mul);

        if (i == sumHashMap.end()) {
          sumHashMap[mul] = 1;
        }
        else {
          (*i).second += 1;
        }
        break;
      }
      }
    }
  }

  sumKids.push_back(rat(constant));
  MonomMap::iterator j = sumHashMap.begin(), jend=sumHashMap.end();
  for(; j != jend; ++j) {
    if ((*j).second != 0)
      sumKids.push_back
	(canonMultMtermMterm(rat((*j).second) * (*j).first).getRHS());
  }


  if ((constant == 0) && (sumKids.size() == 2)) {
    return sumKids[1];
  }
  else if (sumKids.size() == 1) {
    return sumKids[0];
  }
  else
    return plusExpr(sumKids);
}
