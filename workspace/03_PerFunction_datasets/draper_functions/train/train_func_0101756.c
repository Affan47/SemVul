out( MifOutputByteStream &os ) {

    os << '\n' << MifOutputByteStream::INDENT << "<TblFormat ";
    os.indent();

    CHECK_PROPERTY( TblTag );
    CHECK_PROPERTY( TblLIndent );
    CHECK_PROPERTY( TblRIndent );
    CHECK_PROPERTY( TblSpBefore );
    CHECK_PROPERTY( TblSpAfter );
    CHECK_PROPERTY( TblAlignment );
    CHECK_PROPERTY( TblCellMargins );
    CHECK_PROPERTY( TblTitlePlacement );
    CHECK_PROPERTY( TblWidth );
    for( size_t i = 0; i < TblColumns.size(); i++ ) TblColumns[i].out( os );

    os.undent();
    os << '\n' << MifOutputByteStream::INDENT << ">";
}
