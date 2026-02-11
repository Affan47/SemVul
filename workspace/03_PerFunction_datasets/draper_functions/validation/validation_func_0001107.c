AddAndSort(vtkPixelListEntry *p)
    {
      assert("pre: p_exists" && p!=0);
      if(this->Size==0)
        {
        p->SetPrevious(0);
        p->SetNext(0);
        this->First=p;
        this->Last=p;
        }
      else
        {
        vtkPixelListEntry *it=this->Last;
        int sorted=0;
        double z=p->GetZview();
        while(!sorted && it!=0)
          {


          const double tolerance = 1.0e-8;
          if (p->GetExitFace())
            {
#ifdef BACK_TO_FRONT
            sorted=it->GetZview() >= z-tolerance;
#else
            sorted=it->GetZview() <= z+tolerance;
#endif
            }
          else
            {
#ifdef BACK_TO_FRONT
            sorted=it->GetZview() > z+tolerance;
#else
            sorted=it->GetZview() < z-tolerance;
#endif
            }
          if(!sorted)
            {
            it=it->GetPrevious();
            }
          }
        if(it==0)
          {
          p->SetPrevious(0);
          p->SetNext(this->First);

          this->First->SetPrevious(p);
          this->First=p;
          }
        else
          {
          if(it->GetNext()==0)
            {
            it->SetNext(p);
            p->SetPrevious(it);
            p->SetNext(0);
            this->Last=p;
            }
          else
            {
            vtkPixelListEntry *q=it->GetNext();
            q->SetPrevious(p);
            p->SetNext(q);
            p->SetPrevious(it);
            it->SetNext(p);
            }
          }
        }
      ++this->Size;
    }
