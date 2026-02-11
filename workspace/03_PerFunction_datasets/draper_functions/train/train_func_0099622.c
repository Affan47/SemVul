s48_integer_or_floanum_G(long x_734X, long y_735X)
{
  long v_738X;
  long v_737X;
  long v_736X;
 {  if ((3 == (3 & x_734X))) {
    if ((18 == (31 & ((((*((long *) ((((char *) (-3 + x_734X))) + -8))))>>2))))) {
      if (((*((double *) (((char *) (-3 + y_735X))))) < (*((double *) (((char *) (-3 + x_734X))))))) {
        return 5;}
      else {
        return 1;}}
    else {
      goto L21313;}}
  else {
    goto L21313;}}
 L21313: {
  if ((0 == (3 & y_735X))) {
    if ((0 == (3 & x_734X))) {
      if ((y_735X < x_734X)) {
        return 5;}
      else {
        return 1;}}
    else {
      v_736X = s48_bignum_test((((char *) (-3 + x_734X))));
      if ((1 == v_736X)) {
        return 5;}
      else {
        return 1;}}}
  else {
    if ((0 == (3 & x_734X))) {
      v_737X = s48_bignum_test((((char *) (-3 + y_735X))));
      if ((1 == v_737X)) {
        return 1;}
      else {
        return 5;}}
    else {
      v_738X = s48_bignum_compare((((char *) (-3 + y_735X))), (((char *) (-3 + x_734X))));
      if ((-1 == v_738X)) {
        return 5;}
      else {
        return 1;}}}}
}
