emit_assignment_writes(fs_reg &l, fs_reg &r,
				   const glsl_type *type, bool predicated)
{
   switch (type->base_type) {
   case GLSL_TYPE_FLOAT:
   case GLSL_TYPE_UINT:
   case GLSL_TYPE_INT:
   case GLSL_TYPE_BOOL:
      for (unsigned int i = 0; i < type->components(); i++) {
	 l.type = brw_type_for_base_type(type);
	 r.type = brw_type_for_base_type(type);

	 if (predicated || !l.equals(r)) {
	    fs_inst *inst = emit(MOV(l, r));
	    inst->predicate = predicated ? BRW_PREDICATE_NORMAL : BRW_PREDICATE_NONE;
	 }

	 l.reg_offset++;
	 r.reg_offset++;
      }
      break;
   case GLSL_TYPE_ARRAY:
      for (unsigned int i = 0; i < type->length; i++) {
	 emit_assignment_writes(l, r, type->fields.array, predicated);
      }
      break;

   case GLSL_TYPE_STRUCT:
      for (unsigned int i = 0; i < type->length; i++) {
	 emit_assignment_writes(l, r, type->fields.structure[i].type,
				predicated);
      }
      break;

   case GLSL_TYPE_SAMPLER:
   case GLSL_TYPE_ATOMIC_UINT:
      break;

   case GLSL_TYPE_VOID:
   case GLSL_TYPE_ERROR:
   case GLSL_TYPE_INTERFACE:
      assert(!"not reached");
      break;
   }
}
