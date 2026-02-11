_findNodes(const Ray &t,
                            PCZSceneNodeList &list,
                            PCZSceneNode *exclude,
                            bool includeVisitors,
                            bool full )
    {
        if ( !full )
        {
            AxisAlignedBox obox;
            _getCullBounds( &obox );

            Intersection isect = intersect( t, obox );

            if ( isect == OUTSIDE )
                return ;

            full = ( isect == INSIDE );
        }


        PCZSceneNodeList::iterator it = mNodes.begin();

        while ( it != mNodes.end() )
        {
            PCZSceneNode * on = ( *it );

            if ( on != exclude && (on->getHomeZone() == mZone || includeVisitors ))
            {
                if ( full )
                {

                    list.insert( on );
                }

                else
                {
                    Intersection nsect = intersect( t, on -> _getWorldAABB() );

                    if ( nsect != OUTSIDE )
                    {

                        list.insert( on );
                    }
                }

            }
            ++it;
        }

        Octree* child;

        if ( (child=mChildren[ 0 ][ 0 ][ 0 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 1 ][ 0 ][ 0 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 0 ][ 1 ][ 0 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 1 ][ 1 ][ 0 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 0 ][ 0 ][ 1 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 1 ][ 0 ][ 1 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 0 ][ 1 ][ 1 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

        if ( (child=mChildren[ 1 ][ 1 ][ 1 ]) != 0 )
            child->_findNodes( t, list, exclude, includeVisitors, full );

    }
