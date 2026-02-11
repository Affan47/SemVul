sg_EnemyExists( int team )
{

    for ( int i = eTeam::teams.Len()-1; i>= 0; --i )
    {
        if ( i != team && eTeam::Enemies( eTeam::teams[i], eTeam::teams[team] ) )
            return true;
    }

    return false;
}
