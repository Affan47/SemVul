process_parameters(exec_list *instructions, exec_list *actual_parameters,
		   exec_list *parameters,
		   struct _mesa_glsl_parse_state *state)
{
   unsigned count = 0;

   foreach_list (n, parameters) {
      ast_node *const ast = exec_node_data(ast_node, n, link);
      ir_rvalue *result = ast->hir(instructions, state);

      ir_constant *const constant = result->constant_expression_value();
      if (constant != NULL)
	 result = constant;

      actual_parameters->push_tail(result);
      count++;
   }

   return count;
}
