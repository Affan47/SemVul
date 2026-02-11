WriteMolecule(OBBase* pOb, OBConversion* pConv)
{


  OBReaction* pReact = dynamic_cast<OBReaction*>(pOb);
  if(pReact==NULL)
      return false;


  if(pConv->GetOutputIndex()==1)
  {
    OMols.clear();
    ss.str("");
  }

  WriteReactionLine(pReact, pConv);


  if(pConv->IsLast())
  {
    ostream& ofs = *pConv->GetOutStream();
    if(!pConv->IsOption("s"))
    {
      if(!WriteHeader(pConv))
        return false;
      ofs << "REACTIONS\n";
    }
    ofs  << ss.rdbuf() << endl;
    if(!pConv->IsOption("s"))
      ofs << "END" << endl;
  }
  return true;
}
