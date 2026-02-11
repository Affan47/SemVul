FillHierarchyRoot( LabelSet& anchors )
{
  LabelSet::iterator endRootAnchors;
  if ( static_cast<int>( anchors.size() ) < this->Husk->GetTargetLabelCount() )
    {
    endRootAnchors = anchors.end();
    }
  else
    {
    endRootAnchors = anchors.begin();
    for ( int i = 0; i < this->Husk->GetTargetLabelCount(); ++ i )
      {
      ++ endRootAnchors;
      }
    }
  #if ! ( defined(_MSC_VER) && (_MSC_VER < 1300) )
    this->Hierarchy3->root()->value().insert( anchors.begin(), endRootAnchors );
  #else
    for ( LabelSet::iterator it = anchors.begin(); it != endRootAnchors; ++ it )
      {
      this->Hierarchy3->root()->value().insert( *it );
      }
  #endif
  anchors.erase( anchors.begin(), endRootAnchors );
}
