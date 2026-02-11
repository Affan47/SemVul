coalesce_cost (int frequency, bool optimize_for_size)
{

  int cost = frequency;

  if (!cost)
    cost = 1;

  if (optimize_for_size)
    cost = 1;

  return cost;
}
