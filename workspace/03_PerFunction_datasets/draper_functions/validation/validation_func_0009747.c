F_mpz_poly_byte_unpack_unsigned(F_mpz_poly_t poly_m, const mp_limb_t * array,
                               const ulong length, const ulong coeff_bytes)
{
   const ulong limbs_per_coeff = (coeff_bytes>>FLINT_LG_BYTES_PER_LIMB);
   const ulong extra_bytes_per_coeff = coeff_bytes
                                    - (limbs_per_coeff<<FLINT_LG_BYTES_PER_LIMB);

   const ulong limbs = ((coeff_bytes - 1)>>FLINT_LG_BYTES_PER_LIMB) + 1;

   mp_limb_t * temp = (mp_limb_t*) flint_stack_alloc(limbs + 2);

   ulong limb_upto = 0;
   ulong byte_offset = 0;

	mpz_t t;

   ulong old_length = poly_m->length;
	F_mpz_poly_fit_length(poly_m, length);
	_F_mpz_poly_set_length(poly_m, length);
	F_mpz * coeff_m = poly_m->coeffs;
	if (length > old_length) F_mpn_clear(coeff_m + old_length, length - old_length);

   for (ulong i = 0; i < length; i++)
   {
       if ((*coeff_m == 0L) && (limbs != 1))
		 {
			 __mpz_struct * mpz_ptr = _F_mpz_promote(coeff_m);
          if (limbs + 1 > mpz_ptr->_mp_alloc) mpz_realloc(mpz_ptr, limbs + 1);
			 mp_limb_t * data = mpz_ptr->_mp_d;
			 __F_mpz_poly_unpack_bytes(data, array, limb_upto,
                                             byte_offset, coeff_bytes);
			 ulong size = limbs;
			 while ((size) && (data[size - 1] == 0L)) size--;
			 mpz_ptr->_mp_size = size;
			 if (size <= 1) _F_mpz_demote_val(coeff_m);
		 } else
		 {
			 F_mpn_clear(temp, limbs + 2);
          __F_mpz_poly_unpack_bytes(temp + 1, array, limb_upto,
                                             byte_offset, coeff_bytes);
          temp[0] = limbs;
          NORM(temp);

          if (temp[0] == 1)
		       F_mpz_add_ui(coeff_m, coeff_m, temp[1]);
		    else if (temp[0])
		    {
             t->_mp_size = temp[0];
			    t->_mp_d = temp + 1;
			    F_mpz_add_mpz(coeff_m, coeff_m, t);
		    }
		 }

       limb_upto += limbs_per_coeff;

       if (byte_offset + extra_bytes_per_coeff >= FLINT_BYTES_PER_LIMB)
       {
          limb_upto++;
          byte_offset = byte_offset + extra_bytes_per_coeff - FLINT_BYTES_PER_LIMB;
       } else
       {
          byte_offset = byte_offset + extra_bytes_per_coeff;
       }
       coeff_m++;
   }

   flint_stack_release();
   _F_mpz_poly_normalise(poly_m);
}
