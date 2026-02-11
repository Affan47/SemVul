FindName(KeyInfo *info,int key)
{
   static char errmsg[80];

   while (info->ki_key>=0 && info->ki_key != key) info++;

   if (info->ki_key<0)
   {
	   sprintf(errmsg,"Unknown-%d", key );
	   return errmsg;
   }
   return info->ki_name;
}
