rewriteLitSelect(const Expr &e){

  Proof pf;
  if(withProof())
    pf = newPf("rewrite_record_literal_select", e);

  int index=0;
  switch(e.getOpKind())
    {
    case RECORD_SELECT: {
      if(CHECK_PROOFS) {
	CHECK_SOUND(e[0].getOpKind()==RECORD,
		    "expected RECORD child:\n"
		    +e.toString());
      }
      index = getFieldIndex(e[0], getField(e));
      break;
    }
    case TUPLE_SELECT: {
      if(CHECK_PROOFS) {
	CHECK_SOUND(e[0].getOpKind()==TUPLE,
		    "expected TUPLE child:\n"
		    +e.toString());
      }
      index = getIndex(e);
      break;
    }
    default: {
      if(CHECK_PROOFS)
	CHECK_SOUND(false, "expected TUPLE_SELECT or RECORD_SELECT kind"
		    + e.toString());
    }
    }
  if(CHECK_PROOFS) {
    CHECK_SOUND(index!=-1 && index<e[0].arity(),
		"selected field did not appear in literal" + e.toString());
  }
  return newRWTheorem(e, e[0][index], Assumptions::emptyAssump(), pf);
}
