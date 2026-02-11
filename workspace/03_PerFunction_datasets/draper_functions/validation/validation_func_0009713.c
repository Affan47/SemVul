Emit(const LibraryID lib,
                    const DependencyMap& dep_map,
                    std::set<LibraryID>& emitted,
                    std::set<LibraryID>& visited,
                    DependencyList& link_line )
{

  if( emitted.find(lib) != emitted.end() )
    {
    return;
    }


  if( visited.insert(lib).second )
    {
    if( dep_map.find(lib) != dep_map.end() )
      {
      const DependencyList& dep_on = dep_map.find( lib )->second;
      DependencyList::const_reverse_iterator i;


      std::set<DependencyMap::key_type> emitted_here;
      for( i = dep_on.rbegin(); i != dep_on.rend(); ++i )
        {
        if( emitted_here.find(*i) != emitted_here.end() )
          {

          emitted.insert(*i);
          link_line.push_back( *i );
          }
        else
          {

          if( emitted.find(*i) == emitted.end() )
            {

            Emit( *i, dep_map, emitted, visited, link_line );

            emitted.insert(*i);
            emitted_here.insert(*i);
            link_line.push_back( *i );
            }
          }
        }
      }
    }
}
