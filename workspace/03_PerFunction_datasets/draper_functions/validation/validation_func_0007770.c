refmpn_divexact_by3c (mp_ptr rp, mp_srcptr sp, mp_size_t size, mp_limb_t carry)
{
  mp_ptr     spcopy;
  mp_limb_t  c, cs;

  ASSERT (refmpn_overlap_fullonly_p (rp, sp, size));
  ASSERT (size >= 1);
  ASSERT (carry <= 2);
  ASSERT_MPN (sp, size);

  spcopy = refmpn_malloc_limbs (size);
  cs = refmpn_sub_1 (spcopy, sp, size, carry);

  for (c = 0; c <= 2; c++)
    if (refmpn_divmod_1c (rp, spcopy, size, CNST_LIMB(3), c) == 0)
      goto done;
  ASSERT_FAIL (no value of c satisfies);

 done:
  c += cs;
  ASSERT (c <= 2);

  free (spcopy);
  return c;
}
