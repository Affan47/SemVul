dJointGetHinge2Angle1( dJointID j )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[0].body ) return joint->measureAngle();
    else return 0;
}
