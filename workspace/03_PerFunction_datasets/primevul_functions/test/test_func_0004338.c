bool SingleComponentLSScan::WriteMCU(void)
{
#if ACCUSOFT_CODE
  int lines             = m_ulRemaining[0];
  UBYTE preshift        = m_ucLowBit + FractionalColorBitsOf();
  struct Line *line     = CurrentLine(0);

  assert(m_ucCount == 1);


  if (lines > 8) {
    lines = 8;
  }
  m_ulRemaining[0] -= lines;
  assert(lines > 0);


  do {
    LONG length = m_ulWidth[0];
    LONG *lp    = line->m_pData;

    BeginWriteMCU(m_Stream.ByteStreamOf());
    StartLine(0);
    do {
      LONG a,b,c,d,x;
      LONG d1,d2,d3;

      GetContext(0,a,b,c,d);
      x   = *lp >> preshift;

      d1  = d - b;
      d2  = b - c;
      d3  = c - a;

      if (isRunMode(d1,d2,d3)) {
        LONG runval = a;
        LONG runcnt = 0;
        do {
          x  = *lp >> preshift;
          if (x - runval < -m_lNear || x - runval > m_lNear)
            break;


          UpdateContext(0,runval);
        } while(lp++,runcnt++,--length);


        EncodeRun(runcnt,length == 0,m_lRunIndex[0]);


        if (length) {
          bool negative;
          bool rtype;
          LONG errval;
          LONG merr;
          LONG rx;
          UBYTE k;

          GetContext(0,a,b,c,d);

          rtype  = InterruptedPredictionMode(negative,a,b);

          errval = x - ((rtype)?(a):(b));
          if (negative)
            errval = -errval;

          errval = QuantizePredictionError(errval);

          rx     = Reconstruct(negative,rtype?a:b,errval);

          UpdateContext(0,rx);

          k      = GolombParameter(rtype);

          merr   = ErrorMapping(errval,ErrorMappingOffset(rtype,errval != 0,k)) - rtype;

          GolombCode(k,merr,m_lLimit - m_lJ[m_lRunIndex[0]] - 1);

          UpdateState(rtype,errval);


          if (m_lRunIndex[0] > 0)
            m_lRunIndex[0]--;
        } else break;
      } else {
        UWORD ctxt;
        bool  negative;
        LONG  px;
        LONG  rx;
        LONG  errval;
        LONG  merr;
        UBYTE k;

        d1     = QuantizedGradient(d1);
        d2     = QuantizedGradient(d2);
        d3     = QuantizedGradient(d3);

        ctxt   = Context(negative,d1,d2,d3);

        px     = Predict(a,b,c);

        px     = CorrectPrediction(ctxt,negative,px);

        errval = x - px;
        if (negative)
          errval = -errval;

        errval = QuantizePredictionError(errval);

        rx     = Reconstruct(negative,px,errval);

        UpdateContext(0,rx);

        k      = GolombParameter(ctxt);

        merr   = ErrorMapping(errval,ErrorMappingOffset(ctxt,k));

        GolombCode(k,merr,m_lLimit);

        UpdateState(ctxt,errval);
      }
    } while(++lp,--length);
    EndLine(0);
    line = line->m_pNext;
  } while(--lines);
#endif
  return false;
}
