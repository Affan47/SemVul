ecc_gostdsa_verify_itch (const struct ecc_curve *ecc)
{

  return 5*ecc->p.size + ecc->mul_itch;
}
