lp_build_blend_factor_unswizzled(struct lp_build_blend_aos_context *bld,
                                 unsigned factor,
                                 boolean alpha)
{
   LLVMValueRef src_alpha = bld->src_alpha ? bld->src_alpha : bld->src;
   LLVMValueRef src1_alpha = bld->src1_alpha ? bld->src1_alpha : bld->src1;
   LLVMValueRef const_alpha = bld->const_alpha ? bld->const_alpha : bld->const_;

   switch (factor) {
   case PIPE_BLENDFACTOR_ZERO:
      return bld->base.zero;
   case PIPE_BLENDFACTOR_ONE:
      return bld->base.one;
   case PIPE_BLENDFACTOR_SRC_COLOR:
      return bld->src;
   case PIPE_BLENDFACTOR_SRC_ALPHA:
      return src_alpha;
   case PIPE_BLENDFACTOR_DST_COLOR:
   case PIPE_BLENDFACTOR_DST_ALPHA:
      return bld->dst;
   case PIPE_BLENDFACTOR_SRC_ALPHA_SATURATE:
      if(alpha)
         return bld->base.one;
      else {


         if (bld->src_alpha) {
            if (!bld->saturate)
               bld->saturate = lp_build_min(&bld->base, src_alpha, bld->base.zero);
         }
         else {
            if(!bld->inv_dst)
               bld->inv_dst = lp_build_comp(&bld->base, bld->dst);
            if(!bld->saturate)
               bld->saturate = lp_build_min(&bld->base, src_alpha, bld->inv_dst);
         }
         return bld->saturate;
      }
   case PIPE_BLENDFACTOR_CONST_COLOR:
      return bld->const_;
   case PIPE_BLENDFACTOR_CONST_ALPHA:
      return const_alpha;
   case PIPE_BLENDFACTOR_SRC1_COLOR:
      return bld->src1;
   case PIPE_BLENDFACTOR_SRC1_ALPHA:
      return src1_alpha;
   case PIPE_BLENDFACTOR_INV_SRC_COLOR:
      if(!bld->inv_src)
         bld->inv_src = lp_build_comp(&bld->base, bld->src);
      return bld->inv_src;
   case PIPE_BLENDFACTOR_INV_SRC_ALPHA:
      if(!bld->inv_src_alpha)
         bld->inv_src_alpha = lp_build_comp(&bld->base, src_alpha);
      return bld->inv_src_alpha;
   case PIPE_BLENDFACTOR_INV_DST_COLOR:
   case PIPE_BLENDFACTOR_INV_DST_ALPHA:
      if(!bld->inv_dst)
         bld->inv_dst = lp_build_comp(&bld->base, bld->dst);
      return bld->inv_dst;
   case PIPE_BLENDFACTOR_INV_CONST_COLOR:
      if(!bld->inv_const)
         bld->inv_const = lp_build_comp(&bld->base, bld->const_);
      return bld->inv_const;
   case PIPE_BLENDFACTOR_INV_CONST_ALPHA:
      if(!bld->inv_const_alpha)
         bld->inv_const_alpha = lp_build_comp(&bld->base, const_alpha);
      return bld->inv_const_alpha;
   case PIPE_BLENDFACTOR_INV_SRC1_COLOR:
      return lp_build_comp(&bld->base, bld->src1);
   case PIPE_BLENDFACTOR_INV_SRC1_ALPHA:
      return lp_build_comp(&bld->base, src1_alpha);
   default:
      assert(0);
      return bld->base.zero;
   }
}
