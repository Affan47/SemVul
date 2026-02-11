static_conventional_hR (gamgi_cell *cell, int *index)
{
int n1, n2, n3;
int i, j, k;
int n;


n1 = cell->n1;
n2 = cell->n2;
n3 = cell->n3;
n = 0;


for (i = 0; i <= n3; i++)
  {
  for (j = 0; j <= n2; j++)
    {
    for (k = 0; k <= n1; k++)
      {
      index[3*n + 0] = 2 * k - j;
      index[3*n + 1] = 2 * j - k;
      index[3*n + 2] = 3 * i;
      n++;
      }
    }
  }


for (i = 0; i < n3; i++)
  {


  for (j = 0; j < n2; j++)
    {
    for (k = 0; k < n1; k++)
      {
      index[3*n + 0] = 2 * k - j + 1;
      index[3*n + 1] = 2 * j - k;
      index[3*n + 2] = 3 * i + 1;
      n++;
      }
    }


  for (j = 0; j < n2; j++)
    {
    for (k = 0; k < n1; k++)
      {
      index[3*n + 0] = 2 * k - j;
      index[3*n + 1] = 2 * j - k + 1;
      index[3*n + 2] = 3 * i + 2;
      n++;
      }
    }

  }
}
