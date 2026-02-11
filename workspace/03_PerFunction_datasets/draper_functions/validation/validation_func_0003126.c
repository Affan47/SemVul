GetFace(vtkIdType faceIds[3])
    {
      std::list<vtkFace *> *useSet=this->Vector[faceIds[0]];
      vtkFace *result=0;

      if(useSet!=0)
        {
        this->It=(*useSet).begin();
        this->ItEnd=(*useSet).end();
        int found=0;
        while(!found && this->It!=this->ItEnd)
          {
          result=*this->It;
          found=result->IsEqual(faceIds);
          ++this->It;
          }
        if(!found)
          {
          result=0;
          }
        }
      return result;
    }
