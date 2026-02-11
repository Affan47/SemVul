aarch64_frame_pointer_required (void)
{


  if (cfun->calls_alloca)
    return true;


  if (flag_omit_frame_pointer && !faked_omit_frame_pointer)
    return false;
  else if (flag_omit_leaf_frame_pointer)
    return !crtl->is_leaf;
  return true;
}
