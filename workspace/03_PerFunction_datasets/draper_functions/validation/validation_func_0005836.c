setText( const QString& text )
{
  FormWidgetText* fwt = static_cast<FormWidgetText*>(m_formData->fm);
  GooString * goo = QStringToUnicodeGooString( text );
  fwt->setContent( goo );
  delete goo;
}
