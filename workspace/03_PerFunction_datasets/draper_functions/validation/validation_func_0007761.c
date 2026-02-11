cgraph_create_edge (struct cgraph_node *caller, struct cgraph_node *callee,
		    gimple call_stmt, gcov_type count, int freq)
{
  struct cgraph_edge *edge = cgraph_create_edge_1 (caller, callee, call_stmt,
						   count, freq);

  edge->indirect_unknown_callee = 0;
  initialize_inline_failed (edge);

  edge->next_caller = callee->callers;
  if (callee->callers)
    callee->callers->prev_caller = edge;
  edge->next_callee = caller->callees;
  if (caller->callees)
    caller->callees->prev_callee = edge;
  caller->callees = edge;
  callee->callers = edge;

  return edge;
}
