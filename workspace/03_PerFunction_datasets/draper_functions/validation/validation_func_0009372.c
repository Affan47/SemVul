LookupInMolMap(CDXObjectID id)
{
  std::map<CDXObjectID, OBMol*>::iterator mapiter;
  mapiter = _molmap.find(id);
  if(mapiter!=_molmap.end())
  {

    mapiter->second->SetFlags(mapiter->second->GetFlags() | usedFlag);
    return mapiter->second;
  }
  else
  {
    stringstream ss;
    ss << "Reactant or product mol not found id = " << hex << showbase << id;
    obErrorLog.ThrowError(__FUNCTION__, ss.str(), obError);
    return NULL;
  }
}
