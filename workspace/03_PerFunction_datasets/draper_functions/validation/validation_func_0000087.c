DocState(int s)
{

  switch(s)
    {
      case 0:
	docState = Reference_normal;
	break;
      case 1:
	docState = Reference_not_found;
	break;
      case 2:
	docState = Reference_noindex;
	break;
      case 3:
	docState = Reference_obsolete;
	break;
    }
}
