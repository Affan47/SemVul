run(void)
{
   tdialogbox::run ();
   pbutton pb = firstbutton;
   while ( pb &&  (pb->id != 3))
      pb = pb->next;

   if ( pb )
      if ( pb->id == 3 )
         execbutton( pb , false );

   do {
      tdialogbox::run();
   }  while (!((taste == ct_esc) || ((action == 1) || (action == 2))));
   if ((action == 2) || (taste == ct_esc)){
       if ( onCancel == ReturnZero )
          text[0] = 0;
       else
           strcpy( text, org.c_str() );
   }
}
