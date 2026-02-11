sitesort(long chars, steptr weight)
{


  long gap, i, j, jj, jg, k, itemp;
  boolean flip, tied;

  gap = chars / 2;
  while (gap > 0) {
    for (i = gap + 1; i <= chars; i++) {
      j = i - gap;
      flip = true;
      while (j > 0 && flip) {
        jj = alias[j - 1];
        jg = alias[j + gap - 1];
        tied = true;
        k = 1;
        while (k <= spp && tied) {
          flip = (y[k - 1][jj - 1] > y[k - 1][jg - 1]);
          tied = (tied && y[k - 1][jj - 1] == y[k - 1][jg - 1]);
          k++;
        }
        if (!flip)
          break;
        itemp = alias[j - 1];
        alias[j - 1] = alias[j + gap - 1];
        alias[j + gap - 1] = itemp;
        itemp = weight[j - 1];
        weight[j - 1] = weight[j + gap - 1];
        weight[j + gap - 1] = itemp;
        j -= gap;
      }
    }
    gap /= 2;
  }
}
