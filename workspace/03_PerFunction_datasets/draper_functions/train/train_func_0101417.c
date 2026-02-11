countRecords() const
{
  int cnt = 0;
  int i, n = this->blocks.count();
  for (i = 0; i < n; i++)
    cnt += this->blocks[i]->countRecords();
  return cnt + 2;
}
