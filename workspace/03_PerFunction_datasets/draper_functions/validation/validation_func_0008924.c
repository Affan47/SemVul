setSelection( int s )
{
   for ( int i = 0; i < getListBox()->GetWidgetCount(); ++i ) {
      Item* bi = dynamic_cast< Item* >( getListBox()->FindWidget(i) );
      if ( bi )
         bi->Select ( s & (1 << bi->getData()));

    }
}
