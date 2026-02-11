lastIndexOf(const char *pSearchString,unsigned searchLen,unsigned startPos) const
{
  startPos=startBackwardsSearch(startPos,searchLen);
  if (startPos<length())
   {
     switch(searchLen)
      {
        case 0:
          break;
        case 1:
          while (startPos<length())
           {
             if (contents()[startPos]==pSearchString[0]) return startPos;
             else startPos--;
	   }
          break;
        default:
          while (startPos<length())
           {
             if (memcmp(contents()+startPos,pSearchString,searchLen)==0) return startPos;
             else startPos--;
	   }
      }
   }
  return length();
}
