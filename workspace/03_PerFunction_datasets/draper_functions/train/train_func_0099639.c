WriteCreate(nMessage &m, unsigned short cycle_id ){
    m << position;
    m << direction;
    m << distance;

    unsigned short flags = 0;
    if ( braking )
        flags |= 0x01;
    if ( chatting )
        flags |= 0x02;
    m << flags;


    messageID = m.MessageID();

    m.Write( cycle_id );
    m << gameTime;
    m.Write( turns );
}
