data( const QModelIndex &index, int role ) const
{
  if ( !index.isValid() )
    return QVariant();

  const QLdapEntry entry = mData.entries()[ index.row() ];

  if ( role == Qt::DisplayRole ) {
    switch ( index.column() ) {
      case 0:
        return QString( "%1" ).arg( entry.value( "cn" ) );
        break;
      case 1:
        return entry.value( "uid" );
        break;
      default:
        return QVariant();
    }
  } else if ( role == HasModifyActionRole ) {
    return true;
  } else if ( role == HasDeleteActionRole ) {
    if ( entry.values( "kolabDeleteflag" ).isEmpty() )
      return true;
    else
      return false;
  } else if ( role == ModifyActionLabelRole ) {
    if ( entry.values( "kolabDeleteflag" ).isEmpty() )
      return tr( "Modify" );
    else
      return tr( "Administrator deleted, awaiting cleanup..." );
  } else if ( role == DeleteActionLabelRole ) {
    return tr( "Delete" );
  } else if ( role == ModifyActionIdRole ) {
    if ( entry.values( "kolabDeleteflag" ).isEmpty() )
      return mData.entries()[ index.row() ].dn();
    else
      return QString();
  } else if ( role == DeleteActionIdRole ) {
    return mData.entries()[ index.row() ].dn();
  }

  return QVariant();
}
