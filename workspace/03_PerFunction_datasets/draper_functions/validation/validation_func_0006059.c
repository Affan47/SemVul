transfer(method_desc* method, vbm_operand* sp,
                                    byte, byte&)
{
  var_desc* var = &method->vars[var_index];
  if (var->type == tp_void) {
    if (IS_INT_TYPE(var_type)) {
      var->min  = ranges[var_type].min;
      var->max  = ranges[var_type].max;
      var->mask = var->min|var->max;
    } else if (var_type == tp_long) {
      var[0].min  = 0x80000000;
      var[0].max  = 0x7fffffff;
      var[0].mask = 0xffffffff;
      var[1].min  = 0;
      var[1].max  = 0xffffffff;
      var[1].mask = 0xffffffff;
    } else {
      var->mask = (var->type == tp_self)
        ? var_desc::vs_not_null : var_desc::vs_unknown;
      var->min = 0;
      var->max = MAX_ARRAY_LENGTH;
    }
  }
  var->type = var_type;
  var->name = *var_name;
  var->start_pc = var_start_pc;
  return sp;
}
