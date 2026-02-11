emit_scalar(ir_instruction *ir, unsigned op,
        		        st_dst_reg dst,
        			st_src_reg orig_src0, st_src_reg orig_src1)
{
   int i, j;
   int done_mask = ~dst.writemask;


   for (i = 0; i < 4; i++) {
      GLuint this_mask = (1 << i);
      glsl_to_tgsi_instruction *inst;
      st_src_reg src0 = orig_src0;
      st_src_reg src1 = orig_src1;

      if (done_mask & this_mask)
         continue;

      GLuint src0_swiz = GET_SWZ(src0.swizzle, i);
      GLuint src1_swiz = GET_SWZ(src1.swizzle, i);
      for (j = i + 1; j < 4; j++) {


         if (!(done_mask & (1 << j)) &&
             GET_SWZ(src0.swizzle, j) == src0_swiz &&
             GET_SWZ(src1.swizzle, j) == src1_swiz) {
            this_mask |= (1 << j);
         }
      }
      src0.swizzle = MAKE_SWIZZLE4(src0_swiz, src0_swiz,
        			   src0_swiz, src0_swiz);
      src1.swizzle = MAKE_SWIZZLE4(src1_swiz, src1_swiz,
        			  src1_swiz, src1_swiz);

      inst = emit(ir, op, dst, src0, src1);
      inst->dst.writemask = this_mask;
      done_mask |= this_mask;
   }
}
