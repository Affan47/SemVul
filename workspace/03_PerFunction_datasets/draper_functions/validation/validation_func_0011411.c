hash_function(xstr *xs)
{
  if (xs->len) {
    return xs->str[0]% HASH_SIZE;
  }
  return 0;
}
