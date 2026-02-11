FirstIs(Expect::expect_t cc) const
{
   if(first && first->check_case==cc)
      return true;
   return false;
}
