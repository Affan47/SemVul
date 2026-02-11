vinsn_vec_clear (vinsn_vec_t *vinsn_vec)
{
  unsigned len = VEC_length (vinsn_t, *vinsn_vec);
  if (len > 0)
    {
      vinsn_t vinsn;
      int n;

      FOR_EACH_VEC_ELT (vinsn_t, *vinsn_vec, n, vinsn)
        vinsn_detach (vinsn);
      VEC_block_remove (vinsn_t, *vinsn_vec, 0, len);
    }
}
