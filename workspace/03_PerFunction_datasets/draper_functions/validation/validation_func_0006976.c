TryCallApply(Call* expr) {
  Expression* callee = expr->expression();
  Property* prop = callee->AsProperty();
  ASSERT(prop != NULL);

  if (!expr->IsMonomorphic() || expr->check_type() != RECEIVER_MAP_CHECK) {
    return false;
  }
  Handle<Map> function_map = expr->GetReceiverTypes()->first();
  if (function_map->instance_type() != JS_FUNCTION_TYPE ||
      !expr->target()->shared()->HasBuiltinFunctionId() ||
      expr->target()->shared()->builtin_function_id() != kFunctionApply) {
    return false;
  }

  if (info()->scope()->arguments() == NULL) return false;

  ZoneList<Expression*>* args = expr->arguments();
  if (args->length() != 2) return false;

  VariableProxy* arg_two = args->at(1)->AsVariableProxy();
  if (arg_two == NULL || !arg_two->var()->IsStackAllocated()) return false;
  HValue* arg_two_value = environment()->Lookup(arg_two->var());
  if (!arg_two_value->CheckFlag(HValue::kIsArguments)) return false;


  if (function_state()->outer() != NULL) {
    Bailout("Function.prototype.apply optimization in inlined function");
    return true;
  }


  VisitForValue(prop->obj());
  if (HasStackOverflow() || current_block() == NULL) return true;
  HValue* function = Top();
  AddCheckConstantFunction(expr, function, function_map, true);
  Drop(1);

  VisitForValue(args->at(0));
  if (HasStackOverflow() || current_block() == NULL) return true;
  HValue* receiver = Pop();
  HInstruction* elements = AddInstruction(new(zone()) HArgumentsElements);
  HInstruction* length = AddInstruction(new(zone()) HArgumentsLength(elements));
  HInstruction* result =
      new(zone()) HApplyArguments(function, receiver, length, elements);
  result->set_position(expr->position());
  ast_context()->ReturnInstruction(result, expr->id());
  return true;
}
