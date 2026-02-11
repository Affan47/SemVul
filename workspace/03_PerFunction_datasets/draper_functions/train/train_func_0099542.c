try_rewrite_rhs_to_dst(ir_assignment *ir,
                                   fs_reg dst,
                                   fs_reg src,
                                   fs_inst *pre_rhs_inst,
                                   fs_inst *last_rhs_inst)
{

   if (ir->condition ||
       !(ir->lhs->type->is_scalar() ||
        (ir->lhs->type->is_vector() &&
         ir->write_mask == (1 << ir->lhs->type->vector_elements) - 1)))
      return false;


   fs_inst *modify = get_instruction_generating_reg(pre_rhs_inst,
						    last_rhs_inst,
						    src);
   if (!modify)
      return false;


   if (virtual_grf_sizes[dst.reg] != modify->regs_written)
      return false;


   modify->dst = dst;

   return true;
}
