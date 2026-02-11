gt_ggc_mx_VEC_ipa_jump_func_t_gc (void *x_p)
{
  struct VEC_ipa_jump_func_t_gc * const x = (struct VEC_ipa_jump_func_t_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).prefix.num);
        for (i0 = 0; i0 != l0; i0++) {
          switch (((*x).base.vec[i0]).type)
            {
            case IPA_JF_KNOWN_TYPE:
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.known_type.base_type);
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.known_type.component_type);
              break;
            case IPA_JF_CONST:
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.constant);
              break;
            case IPA_JF_CONST_MEMBER_PTR:
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.member_cst.pfn);
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.member_cst.delta);
              break;
            case IPA_JF_PASS_THROUGH:
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.pass_through.operand);
              break;
            case IPA_JF_ANCESTOR:
              gt_ggc_m_9tree_node ((*x).base.vec[i0].value.ancestor.type);
              break;
            default:
              break;
            }
        }
      }
    }
}
