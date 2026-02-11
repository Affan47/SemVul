FuzzyHostParse(char *arg1,char *arg2)

{
  long start = -1, end = -1, where = -1;
  int n;

n = sscanf(arg2,"%ld-%ld%n",&start,&end,&where);

if (n != 2)
   {
   CfOut(cf_error,"","HostRange syntax error: second arg should have X-Y format where X and Y are decimal numbers");
   return false;
   }

return true;
}
