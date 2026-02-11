setLabelText ( const ASCString& widgetName, const ASCString& text, PG_Widget* parent )
{
   if ( !parent )
      parent = this;

   PG_Label* l = dynamic_cast<PG_Label*>( parent->FindChild( widgetName, true ) );
   if ( l )
      l->SetText( text );
   else {
      PG_LineEdit* l = dynamic_cast<PG_LineEdit*>( parent->FindChild( widgetName, true ) );
      if ( l )
         l->SetText( text );
      else {
         PG_MultiLineEdit* l = dynamic_cast<PG_MultiLineEdit*>( parent->FindChild( widgetName, true ) );
         if ( l )
            l->SetText( text );
         else {
            TextRenderer* l = dynamic_cast<TextRenderer*>( parent->FindChild( widgetName, true ) );
            if ( l )
               l->SetText( text );
         }
      }
   }
}
