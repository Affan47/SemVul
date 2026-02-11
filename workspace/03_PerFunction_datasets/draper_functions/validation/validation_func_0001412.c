refmpn_divmod_1c (mp_ptr rp, mp_srcptr sp, mp_size_t size,
		  mp_limb_t divisor, mp_limb_t carry)
{
  mp_ptr     sp_orig;
  mp_ptr     prod;
  mp_limb_t  carry_orig;

  ASSERT (refmpn_overlap_fullonly_p (rp, sp, size));
  ASSERT (size >= 0);
  ASSERT (carry < divisor);
  ASSERT_MPN (sp, size);
  ASSERT_LIMB (divisor);
  ASSERT_LIMB (carry);

  if (size == 0)
    return carry;

  sp_orig = refmpn_memdup_limbs (sp, size);
  prod = refmpn_malloc_limbs (size);
  carry_orig = carry;

  carry = refmpn_divmod_1c_workaround (rp, sp, size, divisor, carry);


#if 0
  printf ("size=%ld divisor=0x%lX carry=0x%lX remainder=0x%lX\n",
	  size, divisor, carry_orig, carry);
  mpn_trace("s",sp_copy,size);
  mpn_trace("r",rp,size);
  printf ("mul_1c %lX\n", refmpn_mul_1c (prod, rp, size, divisor, carry));
  mpn_trace("p",prod,size);
#endif
  ASSERT (refmpn_mul_1c (prod, rp, size, divisor, carry) == carry_orig);
  ASSERT (refmpn_cmp (prod, sp_orig, size) == 0);
  free (sp_orig);
  free (prod);

  return carry;
}
