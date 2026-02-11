_pullTaskNix(pullTask *task) {
  unsigned int ii;

  if (task) {
    for (ii=0; ii<task->pctx->volNum; ii++) {
      task->vol[ii] = pullVolumeNix(task->vol[ii]);
    }
    if (task->pctx->threadNum > 1) {
      task->thread = airThreadNix(task->thread);
    }
    task->rng = airRandMTStateNix(task->rng);
    task->pointBuffer = pullPointNix(task->pointBuffer);
    airFree(task->neighPoint);
    task->addPointArr = airArrayNuke(task->addPointArr);
    task->nixPointArr = airArrayNuke(task->nixPointArr);
    airFree(task);
  }
  return NULL;
}
