SetNodeSetArrayStatus(const char* name, int flag)
{
  if(this->MetaData->GetNumberOfNodeSets()==0)
    {


    this->MetaData->SetNodeSetInitStatus(name,flag);
    }

  if (this->MetaData->GetNodeSetStatus(name) != flag)
    {
    this->MetaData->SetNodeSetStatus(name, flag);


    this->RemakeDataCacheFlag = 1;
    this->Modified();
    }
}
