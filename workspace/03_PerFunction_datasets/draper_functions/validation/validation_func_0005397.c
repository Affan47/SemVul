intel_hiz_exec(struct brw_context *brw, struct intel_mipmap_tree *mt,
	       unsigned int level, unsigned int layer, gen6_hiz_op op)
{
   const char *opname = NULL;

   switch (op) {
   case GEN6_HIZ_OP_DEPTH_RESOLVE:
      opname = "depth resolve";
      break;
   case GEN6_HIZ_OP_HIZ_RESOLVE:
      opname = "hiz ambiguate";
      break;
   case GEN6_HIZ_OP_DEPTH_CLEAR:
      opname = "depth clear";
      break;
   case GEN6_HIZ_OP_NONE:
      opname = "noop?";
      break;
   }

   DBG("%s %s to mt %p level %d layer %d\n",
       __FUNCTION__, opname, mt, level, layer);

   brw_hiz_op_params params(mt, level, layer, op);
   brw_blorp_exec(brw, &params);
}
