Clear()
{
  if (this->Managed)
    {
    switch (this->Superclass::Type)
      {
      case LABELLIST:
      case SCALARLIST:
      case VECTORLIST:
      case STRINGLIST:
        this->VtkObjectPtr->Delete();
        break;
      case LABELLISTLIST:
        delete this->LabelListListPtr;
        break;
      case ENTRYVALUELIST:
        for (size_t valueI = 0; valueI < this->EntryValuePtrs->size() ; valueI++)
          {
          delete this->EntryValuePtrs->operator[](valueI);
          }
        delete this->EntryValuePtrs;
        break;
      case DICTIONARY:
        delete this->DictPtr;
        break;


      default:
        break;
      }
    }
}
