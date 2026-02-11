ExecQuadNot(quadrupla quad) {
  char vallogic1;
  switch (quad->opnd1.tipo) {
    case LOGICOPND:
      vallogic1 = quad->opnd1.atr.vallogic;  break;
    case VAROPND:
      switch (quad->opnd1.atr.simb->tvar) {
        case LOGICO:
          vallogic1 = *(quad->opnd1.atr.simb->vallogic);
          break;
      }
      break;
  }

  *(quad->result.atr.simb->vallogic) = !vallogic1;
}
