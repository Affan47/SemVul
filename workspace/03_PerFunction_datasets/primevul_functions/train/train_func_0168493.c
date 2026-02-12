ecc_ecdsa_sign_itch (const struct ecc_curve *ecc)
{


  assert (ecc->p.size + ecc->p.invert_itch <= 3*ecc->p.size + ecc->mul_g_itch);
  return ECC_ECDSA_SIGN_ITCH (ecc->p.size);
}
