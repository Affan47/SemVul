ipcp_init_cloned_node (struct cgraph_node *orig_node,
		       struct cgraph_node *new_node)
{
  gcc_checking_assert (ipa_node_params_vector
		       && (VEC_length (ipa_node_params_t,
				       ipa_node_params_vector)
			   > (unsigned) cgraph_max_uid));
  gcc_checking_assert (IPA_NODE_REF (new_node)->params);
  IPA_NODE_REF (new_node)->ipcp_orig_node = orig_node;
}
