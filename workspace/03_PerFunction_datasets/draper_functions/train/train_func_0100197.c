GetInitialObjectArrayStatus( int otyp, ArrayInfoType *objType )
{
  for(unsigned int oidx=0; oidx<this->InitialArrayInfo[otyp].size(); oidx++)
    {
    if(objType->Name == this->InitialArrayInfo[otyp][oidx].Name)
      {
      objType->Status = this->InitialArrayInfo[otyp][oidx].Status;
      break;
      }
    }
}
