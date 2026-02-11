constArithLocal(VimosImage *ima_in, double constant, VimosOperator optype)

{
  VimosUlong32    i;
  VimosUlong32    nbpix;
  double          invconst;
  char            modName[] = "constArithLocal";


  if (ima_in == NULL) {
    cpl_msg_error(modName, "NULL input image");
    return 1;
  }

  if ((fabs((double)constant) < MIN_DIVISOR) && (optype == VM_OPER_DIV)) {
    cpl_msg_error(modName, "division by zero");
    return 1;
  }

  nbpix = ima_in->xlen * ima_in->ylen;

  switch(optype) {

  case VM_OPER_ADD:
    for (i=0; i<nbpix; i++)
      ima_in->data[i] = (float)((double)ima_in->data[i] + constant);
    break;

  case VM_OPER_SUB:
    for (i=0; i<nbpix; i++)
      ima_in->data[i] = (float)((double)ima_in->data[i] - constant);
    break;

  case VM_OPER_MUL:
    for (i=0; i<nbpix; i++)
      ima_in->data[i] = (float)((double)ima_in->data[i] * constant);
    break;

  case VM_OPER_DIV:

    invconst = (double)1.0 / constant;
    for (i=0; i<nbpix; i++)
      ima_in->data[i] = (float)((double)ima_in->data[i] * invconst);
     break;

  default:
    cpl_msg_error(modName, "Unrecognized operator");
    return 1;
  }

 return 0;
}
