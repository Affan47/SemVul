DisconnectSource(ProcessObject *arg, const DataObjectIdentifierType & name)
{
  if ( m_Source == arg && m_SourceOutputName == name )
    {
    itkDebugMacro("disconnecting source  " << arg
                                           << ", source output name " << name);

    m_Source = ITK_NULLPTR;
    m_SourceOutputName = "";
    this->Modified();
    return true;
    }
  else
    {
    itkDebugMacro("could not disconnect source  " << arg
                                                  << ", source output name " << name);
    return false;
    }
}
