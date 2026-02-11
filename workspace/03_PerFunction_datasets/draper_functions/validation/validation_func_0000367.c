Show(const char *op,const ArrayOfaType & at,ostream &f)  const
    {
    const_iterator i=m.find(op);
    if (i==m.end()) f << " unknow " << op << " operator " << endl;
    else i->second->Show(at,f);
  }
