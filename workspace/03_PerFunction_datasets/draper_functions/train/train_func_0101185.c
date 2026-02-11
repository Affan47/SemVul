LookupTag(const string &Message,const char *Tag,const char *Default)
{

   int Length = strlen(Tag);
   for (string::const_iterator I = Message.begin(); I + Length < Message.end(); ++I)
   {

      if (I[Length] == ':' && stringcasecmp(I,I+Length,Tag) == 0)
      {

	 string::const_iterator J;
	 I += Length + 1;
	 for (; isspace(*I) != 0 && I < Message.end(); ++I);
	 for (J = I; *J != '\n' && J < Message.end(); ++J);
	 for (; J > I && isspace(J[-1]) != 0; --J);

	 return string(I,J);
      }

      for (; *I != '\n' && I < Message.end(); ++I);
   }


   if (Default == 0)
      return string();
   return Default;
}
