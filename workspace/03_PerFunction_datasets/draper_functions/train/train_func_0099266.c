updateTurn()
      {
         if ( turn )
            turn->SetText( ASCString::toString( gamemap->time.turn() ));

         if ( currentPlayer ) {
            if ( gamemap->actplayer >= 0 )
               currentPlayer->SetText( gamemap->player[gamemap->actplayer].getName() );
            else
               currentPlayer->SetText( ASCString::toString( gamemap->actplayer ) );
         }
      }
