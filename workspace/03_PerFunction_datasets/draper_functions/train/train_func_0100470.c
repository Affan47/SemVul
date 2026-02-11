get_pnt_info(const skip_alloc_t *slot_p, pnt_info_t *info_p)
{
  info_p->pi_fence_b = BIT_IS_SET(slot_p->sa_flags, ALLOC_FLAG_FENCE);
  info_p->pi_blanked_b = BIT_IS_SET(slot_p->sa_flags, ALLOC_FLAG_BLANK);

  info_p->pi_alloc_start = slot_p->sa_mem;

  if (info_p->pi_fence_b) {
    char * a_p;
    a_p=align_to((char *)info_p->pi_alloc_start +FENCE_BOTTOM_SIZE,slot_p->sa_align);
    info_p->pi_fence_bottom = a_p-FENCE_BOTTOM_SIZE;
    info_p->pi_user_start = a_p;
  }
  else {
    info_p->pi_fence_bottom = NULL;
    info_p->pi_user_start = align_to((char *)info_p->pi_alloc_start,slot_p->sa_align);
  }

  info_p->pi_align=slot_p->sa_align;
  info_p->pi_user_bounds = (char *)info_p->pi_user_start +
    slot_p->sa_user_size;

  info_p->pi_alloc_bounds = (char *)slot_p->sa_mem + slot_p->sa_total_size;

  if (info_p->pi_fence_b) {
    info_p->pi_fence_top = info_p->pi_user_bounds;
    info_p->pi_upper_bounds = (char *)info_p->pi_alloc_bounds - FENCE_TOP_SIZE;
  }
  else {
    info_p->pi_fence_top = NULL;
    info_p->pi_upper_bounds = info_p->pi_alloc_bounds;
  }
}
