cbf_mpint_add_acc(unsigned int * acc, size_t acsize, unsigned int * add, size_t addsize) {

  int iint;

  unsigned int carry;

  unsigned int precarry;

  unsigned int sign;

  carry = 0; precarry=0;

  sign = 1 << (sizeof(unsigned int)*CHAR_BIT-1);

  for (iint = 0; iint < acsize && iint < addsize; iint++) {

    if (carry) {

      cbf_failnez(cbf_mpint_increment_acc(acc+iint,acsize-iint));

    }

    if ( acc[iint] & sign ) precarry++;

    if ( add[iint] & sign ) precarry++;

    acc[iint] += add[iint];

    carry = 0;

    if (precarry == 2 || (precarry == 1 && !(acc[iint]&sign) ) ) carry = 1;

    precarry = 0;

  }

  if (addsize > acsize) {

    if (add[acsize-1] &sign ) {

      for (iint = acsize; iint < acsize; iint++)

        if ( add[iint] != -1) return CBF_ARGUMENT;

    } else {

      for (iint = acsize; iint < acsize; iint++)

        if ( add[iint] != 0) return CBF_ARGUMENT;

    }

  } else if (acsize > addsize){

    for (iint = addsize; iint < acsize; iint++) {

      if (carry) {

        cbf_failnez(cbf_mpint_increment_acc(acc+iint,acsize-iint));

      }

      if ( acc[iint] & sign ) precarry++;

      carry = 0;

      if (precarry == 1 && !(acc[iint] &sign) ) carry = 1;

      precarry = 0;

    }

  }

  return 0;

}
