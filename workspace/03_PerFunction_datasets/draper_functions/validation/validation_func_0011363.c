dump_localparams_(ostream&out, unsigned indent) const
{
      typedef map<perm_string,param_expr_t>::const_iterator parm_iter_t;
      for (parm_iter_t cur = localparams.begin()
		 ; cur != localparams.end() ; cur ++) {
	    out << setw(indent) << "" << "localparam ";
	    if ((*cur).second.msb)
		  out << "[" << *(*cur).second.msb << ":"
		      << *(*cur).second.lsb << "] ";
	    out << (*cur).first << " = ";
	    if ((*cur).second.expr)
		  out << *(*cur).second.expr << ";" << endl;
	    else
		  out << "/* ERROR */;" << endl;
      }
}
