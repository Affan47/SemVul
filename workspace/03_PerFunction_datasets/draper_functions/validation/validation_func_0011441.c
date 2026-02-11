operator> ( const AStar3D::Node& a, const AStar3D::Node& b )
{
    if ( a.hval >= AStar3D::longestPath || b.hval >= AStar3D::longestPath )
       return a.gval > b.gval;
    else
       return (a.gval+a.hval) > (b.gval+b.hval);
}
