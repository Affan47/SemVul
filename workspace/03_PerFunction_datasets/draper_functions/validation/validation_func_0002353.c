isValid( QString &message, PagePolicy::State ) const
{
  if ( mType == InvalidateEmpty && mLineEdit->text().isEmpty() ) {
    message = QObject::tr( "You have to fill out all required fields (%1)" ).arg( name() );
    return false;
  } else
    return true;
}
