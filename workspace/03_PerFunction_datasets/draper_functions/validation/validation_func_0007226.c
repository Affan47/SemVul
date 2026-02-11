uniform_bits (const real_t *used_coeff, const word_t *used_states,
	      unsigned level, const coeff_t *coeff)
{
   unsigned edge;
   real_t   bits = 0;

   for (edge = 0; isedge (used_states [edge]); edge++)
   {
      rpf_t *rpf = used_states [edge] ? coeff->rpf : coeff->dc_rpf;

      bits += rpf->mantissa_bits + 1;
   }

   return bits;
}
