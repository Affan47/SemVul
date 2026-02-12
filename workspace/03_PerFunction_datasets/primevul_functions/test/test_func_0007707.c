bool alloc_and_init_significant_coeff_ctxIdx_lookupTable_OLD()
{
  int tableSize = 2*2*4*(4*4 + 8*8 + 16*16 + 32*32);
  uint8_t* p = (uint8_t*)malloc(tableSize);
  if (p==NULL) {
    return false;
  }

  for (int log2w=2; log2w<=5 ; log2w++)
    for (int cIdx=0;cIdx<2;cIdx++)
      for (int scanIdx=0;scanIdx<2;scanIdx++)
        for (int prevCsbf=0;prevCsbf<4;prevCsbf++)
          {


            ctxIdxLookup[log2w-2][cIdx][scanIdx][prevCsbf] = p;
            p += (1<<log2w)*(1<<log2w);

            const position* ScanOrderSub = get_scan_order(log2w-2, scanIdx);
            const position* ScanOrderPos = get_scan_order(2, scanIdx);


            for (int s=0;s<(1<<log2w)*(1<<log2w);s++)
              {
                position S = ScanOrderSub[s>>4];
                int x0 = S.x<<2;
                int y0 = S.y<<2;

                int subX = ScanOrderPos[s & 0xF].x;
                int subY = ScanOrderPos[s & 0xF].y;
                int xC = x0 + subX;
                int yC = y0 + subY;


                int w = 1<<log2w;
                int sbWidth = w>>2;

                int sigCtx;


                if (sbWidth==1) {
                  sigCtx = ctxIdxMap[(yC<<2) + xC];
                }
                else if (xC+yC==0) {
                  sigCtx = 0;
                }
                else {
                  int xS = xC>>2;
                  int yS = yC>>2;


                  int xP = xC & 3;
                  int yP = yC & 3;

                  logtrace(LogSlice,"posInSubset: %d,%d\n",xP,yP);
                  logtrace(LogSlice,"prevCsbf: %d\n",prevCsbf);


                  switch (prevCsbf) {
                  case 0:

                    sigCtx = (xP+yP>=3) ? 0 : (xP+yP>0) ? 1 : 2;
                    break;
                  case 1:
                    sigCtx = (yP==0) ? 2 : (yP==1) ? 1 : 0;
                    break;
                  case 2:
                    sigCtx = (xP==0) ? 2 : (xP==1) ? 1 : 0;
                    break;
                  default:
                    sigCtx = 2;
                    break;
                  }

                  logtrace(LogSlice,"a) sigCtx=%d\n",sigCtx);

                  if (cIdx==0) {
                    if (xS+yS > 0) sigCtx+=3;

                    logtrace(LogSlice,"b) sigCtx=%d\n",sigCtx);


                    if (sbWidth==2) {
                      sigCtx += (scanIdx==0) ? 9 : 15;
                    } else {
                      sigCtx += 21;
                    }

                    logtrace(LogSlice,"c) sigCtx=%d\n",sigCtx);
                  }
                  else {

                    if (sbWidth==2) {
                      sigCtx+=9;
                    }
                    else {
                      sigCtx+=12;
                    }
                  }
                }

                int ctxIdxInc;
                if (cIdx==0) { ctxIdxInc=sigCtx; }
                else         { ctxIdxInc=27+sigCtx; }


                ctxIdxLookup[log2w-2][cIdx][scanIdx][prevCsbf][xC+(yC<<log2w)] = ctxIdxInc;


              }
          }

  return true;
}
