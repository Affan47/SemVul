aapcs_vfp_is_return_candidate (enum arm_pcs pcs_variant,
			       enum machine_mode mode, const_tree type)
{
  int count ATTRIBUTE_UNUSED;
  enum machine_mode ag_mode ATTRIBUTE_UNUSED;

  if (!use_vfp_abi (pcs_variant, false))
    return false;
  return aapcs_vfp_is_call_or_return_candidate (pcs_variant, mode, type,
						&ag_mode, &count);
}
