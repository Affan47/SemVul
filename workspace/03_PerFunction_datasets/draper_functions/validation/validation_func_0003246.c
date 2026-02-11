get_stack_dec_field_acc(JVM_CLASS *class, JVM_OPCODE op, u4 index)
{
  int stack_decrement;
  char *this_desc;
  int tmpsize;
  CP_NODE *c;

  if(!class) {
    BAD_ARG();
    return 0;
  }

  c = cp_entry_by_index(class, index);
  if(!c) return -1;

  c = cp_entry_by_index(class, c->val->cpnode.Methodref.name_and_type_index);
  if(!c) return -1;

  c = cp_entry_by_index(class, c->val->cpnode.NameAndType.descriptor_index);
  if(!c) return -1;

  this_desc = cp_null_term_utf8(c->val);
  if(!this_desc) return -1;

  if((this_desc[0] == 'D') || (this_desc[0] == 'J'))
    tmpsize = 2;
  else
    tmpsize = 1;

  switch(op) {
    case jvm_getstatic:
      stack_decrement = 0;
      break;
    case jvm_putstatic:
      stack_decrement = tmpsize;
      break;
    case jvm_getfield:
      stack_decrement = 1;
      break;
    case jvm_putfield:
      stack_decrement = tmpsize + 1;
      break;
    default:
      debug_err("get_stack_decrement(): unexpected op type\n");
      free(this_desc);
      return -1;
  }

  free(this_desc);

  return stack_decrement;
}
