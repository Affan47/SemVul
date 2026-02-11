_gageNeedKUpdate(gageContext *ctx) {
  static const char me[]="_gageNeedKUpdate";
  int kernIdx, needK[GAGE_KERNEL_MAX+1], change;
  unsigned int di;

  if (ctx->verbose) fprintf(stderr, "%s: hello\n", me);
  for (kernIdx=gageKernelUnknown+1; kernIdx<gageKernelLast; kernIdx++) {
    needK[kernIdx] = AIR_FALSE;
  }
  if (!ctx->parm.k3pack) {
    biffAddf(GAGE, "%s: sorry, only 3-pack filtering implemented now", me);
    return 1;
  }
  di = 0;
  if (ctx->needD[di]) {
    needK[gageKernel00] = AIR_TRUE;
  }
  di += 1;
  if (ctx->needD[di]) {
    needK[gageKernel00] = needK[gageKernel11] = AIR_TRUE;
  }
  di += 1;
  if (ctx->needD[di]) {
    needK[gageKernel00] = needK[gageKernel11] =
      needK[gageKernel22] = AIR_TRUE;
  }
  if (GAGE_DERIV_MAX != di) {
    biffAddf(GAGE, "%s: sorry, code needs updating for GAGE_DERIV_MAX %u",
             me, GAGE_DERIV_MAX);
    return 1;
  }
  change = AIR_FALSE;
  for (kernIdx=gageKernelUnknown+1; kernIdx<gageKernelLast; kernIdx++) {
    change |= (needK[kernIdx] != ctx->needK[kernIdx]);
  }
  if (change) {
    if (ctx->verbose) {
      fprintf(stderr, "%s: changing needK to (", me);
      for (kernIdx=gageKernelUnknown+1; kernIdx<gageKernelLast; kernIdx++) {
        fprintf(stderr, "%s%d", kernIdx > gageKernelUnknown+1 ? "," : "",
                needK[kernIdx]);
      }
      fprintf(stderr, ")\n");
    }
    for (kernIdx=gageKernelUnknown+1; kernIdx<gageKernelLast; kernIdx++) {
      ctx->needK[kernIdx] = needK[kernIdx];
    }
    ctx->flag[gageCtxFlagNeedK] = AIR_TRUE;
  }
  if (ctx->verbose) fprintf(stderr, "%s: bye\n", me);

  return 0;
}
