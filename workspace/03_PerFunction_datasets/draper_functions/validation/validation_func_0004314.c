itemType( const QString &type )
{
  QString t;

  t = type;
  t.replace( 0, 1, t.left( 1 ).toUpper() );

  return t;
}
