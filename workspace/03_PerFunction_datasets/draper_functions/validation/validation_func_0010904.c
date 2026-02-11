visit_leave(ir_assignment *ir)
{
   if (do_graft(&ir->rhs) ||
       do_graft(&ir->condition))
      return visit_stop;


   return check_graft(ir, ir->lhs->variable_referenced());
}
