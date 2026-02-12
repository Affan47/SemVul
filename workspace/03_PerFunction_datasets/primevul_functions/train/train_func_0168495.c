ecc_gostdsa_verify (const struct ecc_curve *ecc,
		  const mp_limb_t *pp,
		  size_t length, const uint8_t *digest,
		  const mp_limb_t *rp, const mp_limb_t *sp,
		  mp_limb_t *scratch)
{


#define hp (scratch)
#define vp (scratch + ecc->p.size)
#define z1 (scratch + 3*ecc->p.size)
#define z2 (scratch + 4*ecc->p.size)

#define P1 (scratch + 4*ecc->p.size)
#define P2 (scratch)


  if (! (ecdsa_in_range (ecc, rp)
	 && ecdsa_in_range (ecc, sp)))
    return 0;

  gost_hash (&ecc->q, hp, length, digest);

  if (mpn_zero_p (hp, ecc->p.size))
    mpn_add_1 (hp, hp, ecc->p.size, 1);


  ecc->q.invert (&ecc->q, vp, hp, vp + ecc->p.size);


  ecc_mod_mul_canonical (&ecc->q, z1, sp, vp, z1);


  mpn_sub_n (hp, ecc->q.m, rp, ecc->p.size);
  ecc_mod_mul_canonical (&ecc->q, z2, hp, vp, z2);


  ecc->mul (ecc, P2, z2, pp, z2 + ecc->p.size);


  ecc->mul_g (ecc, P1, z1, P1 + 3*ecc->p.size);


  ecc->add_hhh (ecc, P1, P1, P2, P1 + 3*ecc->p.size);


  ecc->h_to_a (ecc, 2, P2, P1, P1 + 3*ecc->p.size);

  return (mpn_cmp (rp, P2, ecc->p.size) == 0);
#undef P2
#undef P1
#undef z2
#undef z1
#undef hp
#undef vp
}
