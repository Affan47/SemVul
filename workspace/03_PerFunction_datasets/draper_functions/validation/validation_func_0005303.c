make_delay_nets(Design*des, NetScope*scope, NetExpr*expr)
{
      if (dynamic_cast<NetESignal*> (expr))
	    return expr;

      if (dynamic_cast<NetEConst*> (expr))
	    return expr;

      NetNet*sig = expr->synthesize(des, scope, expr);
      if (sig == 0) {
	    cerr << expr->get_fileline() << ": error: Expression " << *expr
		 << " is not suitable for delay expression." << endl;
	    return 0;
      }

      expr = new NetESignal(sig);
      return expr;
}
