Read(ByteBuffer &data)
{
    data >> flags;
    if(_c == CLIENT_WOTLK)
      data >> flags2;
    if(_c == CLIENT_TBC)
    {
      uint8 tempFlags2;
      data >> tempFlags2;
      flags2 = tempFlags2;
    }
    data >> time;
    data >> pos.x;
    data >> pos.y;
    data >> pos.z;
    data >> pos.o;

    if(flags & (MOVEMENTFLAG_ONTRANSPORT))
    {
        if(_c < CLIENT_WOTLK)
          data >> t_guid;
        else
          t_guid =data.readPackGUID();
        data >> t_pos.x;
        data >> t_pos.y;
        data >> t_pos.z;
        data >> t_pos.o;
        if(_c > CLIENT_CLASSIC_WOW)
          data >> t_time;
        if(_c > CLIENT_TBC)
          data >> t_seat;

        if(_c > CLIENT_TBC && flags2 & MOVEMENTFLAG2_INTERP_MOVEMENT)
            data >> t_time2;
    }

    if((flags & (MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_FLYING)) || (flags2 & MOVEMENTFLAG2_ALLOW_PITCHING))
    {
        data >> s_angle;
    }

    data >> fallTime;

    if(flags & (MOVEMENTFLAG_FALLING))
    {
        data >> j_velocity;
        data >> j_sinAngle;
        data >> j_cosAngle;
        data >> j_xyspeed;
    }

    if(flags & (MOVEMENTFLAG_SPLINE_ELEVATION))
    {
        data >> u_unk1;
    }
}
