void EbmlElement::Read(EbmlStream & inDataStream, const EbmlSemanticContext & , int & , EbmlElement * & , bool , ScopeMode ReadFully)
{
  ReadData(inDataStream.I_O(), ReadFully);
}
