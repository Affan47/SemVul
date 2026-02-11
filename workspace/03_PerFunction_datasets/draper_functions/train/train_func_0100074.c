findFrame( const QString &f )
{
  khtml::ChildFrame *childFrame;
  KHTMLPart *parentFrame = findFrameParent(this, f, &childFrame);
  if (parentFrame)
     return qobject_cast<KHTMLPart*>(childFrame->m_part.data());

  return 0;
}
