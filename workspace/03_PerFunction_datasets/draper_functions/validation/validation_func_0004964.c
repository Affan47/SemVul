WriteChemObjectImpl(OBConversion* pConv, OBFormat* pFormat)
  {
    if(pConv->IsOption("C",OBConversion::GENOPTIONS))
      return OutputDeferredMols(pConv);
    if(pConv->IsOption("j",OBConversion::GENOPTIONS)
        || pConv->IsOption("join",OBConversion::GENOPTIONS))
      {

        if(!pConv->IsLast())
          return true;
        bool ret=pFormat->WriteMolecule(_jmol,pConv);
        pConv->SetOutputIndex(1);
        delete _jmol;
        return ret;
      }


    OBBase* pOb = pConv->GetChemObject();

    OBMol* pmol = dynamic_cast<OBMol*> (pOb);
    bool ret=false;
    if(pmol)
      {
        if(pmol->NumAtoms()==0)
          {
            std::string auditMsg = "OpenBabel::Molecule ";
            auditMsg += pmol->GetTitle();
            auditMsg += " has 0 atoms";
            obErrorLog.ThrowError(__FUNCTION__,
                                  auditMsg,
                                  obInfo);
          }
        ret=true;

        std::string auditMsg = "OpenBabel::Write molecule ";
        std::string description(pFormat->Description());
        auditMsg += description.substr(0,description.find('\n'));
        obErrorLog.ThrowError(__FUNCTION__,
                              auditMsg,
                              obAuditMsg);

        ret = DoOutputOptions(pOb, pConv);

        if(ret)
          ret = pFormat->WriteMolecule(pmol,pConv);
    }

#ifdef HAVE_SHARED_POINTER

    OBReaction* pReact = dynamic_cast<OBReaction*> (pOb);
    if(pReact)
      ret = OutputMolsFromReaction(pReact, pConv, pFormat);
#endif
    delete pOb;
    return ret;
  }
