picksplit(const S *ego, const tensor *sz, int *rp)
{
     A(sz->rnk > 1);
     if (!X(pickdim)(ego->spltrnk, ego->buddies, ego->nbuddies, sz, 1, rp))
	  return 0;
     *rp += 1;
     if (*rp >= sz->rnk)
	  return 0;
     return 1;
}
