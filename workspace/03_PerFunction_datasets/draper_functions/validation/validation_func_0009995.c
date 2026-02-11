outProlog( MifOutputByteStream &os ) {

    currentlyOpened = true;
    outSimpleProlog( os );
    CHECK_PROPERTY( PgfTag );
    if( setProperties & fParagraphFormat )
        format().out( os );
}
