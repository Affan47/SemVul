paintSingleField( const MapRenderer::FieldRenderInfo& fieldInfo,  int layer, const SPoint& pos )
   {
      if ( fieldInfo.gamemap != gamemap && gamemap) {
         reset();
         gamemap = NULL;
         return;
      }

      if ( fieldInfo.visibility >= visible_ago) {
         if ( fields.find( fieldInfo.pos ) != fields.end() ) {
            int p = fields[fieldInfo.pos];
            if ( p & 1 )
               fieldInfo.surface.Blit( icon1, pos );
            if ( p & 2 )
               fieldInfo.surface.Blit( icon2, pos );
         }
      }
   }
