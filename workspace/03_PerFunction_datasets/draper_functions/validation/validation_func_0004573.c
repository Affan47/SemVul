internalAddAsIs(const char *str, int position)
{
  size_t k = 0;

  bool addAtEnd;
  if (position < 0 || (size_t)position > myArgc)
    addAtEnd = true;
  else
    addAtEnd = false;


  if (addAtEnd)
  {
    myArgv[myArgc] = new char[strlen(str) + 1];
    strcpy(myArgv[myArgc], str);
    myArgv[myArgc][strlen(str)] = '\0';


    if (!myFirstAdd && myExtraSpace == '\0')
      myFullString += " ";
    else if (!myFirstAdd)
      myFullString += myExtraSpace;

    myFullString += myArgv[myArgc];
    myFirstAdd = false;

    myArgc++;
    myOrigArgc = myArgc;
  }
  else
  {

    for (k = myArgc + 1; k > (size_t)position; k--)
    {
      myArgv[k] = myArgv[k - 1];
    }
    myArgc++;
    myOrigArgc = myArgc;

    myArgv[position] = new char[strlen(str) + 1];
    strcpy(myArgv[position], str);
    myArgv[position][strlen(str)] = '\0';

    rebuildFullString();
    myFirstAdd = false;
  }


}
