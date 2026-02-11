_pullNixTheNixed(pullContext *pctx) {
  unsigned int binIdx;

  pctx->nixNum = 0;
  for (binIdx=0; binIdx<pctx->binNum; binIdx++) {
    pullBin *bin;
    unsigned int pointIdx;
    bin = pctx->bin + binIdx;
    pointIdx = 0;
    while (pointIdx < bin->pointNum) {
      pullPoint *point;
      point = bin->point[pointIdx];
      if (pctx->flag.nixAtVolumeEdgeSpace
          && (point->status & PULL_STATUS_EDGE_BIT)) {
        point->status |= PULL_STATUS_NIXME_BIT;
      }
      if (point->status & PULL_STATUS_NIXME_BIT) {
        pullPointNix(point);

        bin->point[pointIdx] = bin->point[bin->pointNum-1];
        airArrayLenIncr(bin->pointArr, -1);
        pctx->nixNum++;
      } else {
        pointIdx++;
      }
    }
  }
  return;
}
