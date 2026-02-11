clientSelect (const QString & path, bool examine)
{
  Q_UNUSED( examine );


  return CommandPtr( new imapCommand( "SELECT",
                          QString( "\"" ) + KIMAP::encodeImapFolderName( path ) + "\"" ) );
}
