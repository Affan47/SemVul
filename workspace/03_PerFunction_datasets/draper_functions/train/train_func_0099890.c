checkModificationConstraints( const ContainerBase* container )
{
   if ( container->getMap()->actplayer == container->getOwner() || container->getMap()->actplayer==-1 )
      return true;
   return false;
}
