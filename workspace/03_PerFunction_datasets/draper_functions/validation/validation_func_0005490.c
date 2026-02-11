dump(ostream&out, unsigned ind) const
{
      if (expr_.count() == 0) {
	    out << setw(ind) << "" << "@* ";

      } else {
	    out << setw(ind) << "" << "@(" << *(expr_[0]);
	    if (expr_.count() > 1)
		  for (unsigned idx = 1 ;  idx < expr_.count() ;  idx += 1)
			out << " or " << *(expr_[idx]);

	    out << ")";
      }

      if (statement_) {
	    out << endl;
	    statement_->dump(out, ind+2);
      } else {
	    out << " ;" << endl;
      }
}
