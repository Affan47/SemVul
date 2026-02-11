mapeditorMainThread ( void* _mapname )
{
   const char* mapname = (const char*) _mapname;
   loadpalette();

   try {
      StartupScreen sus( "title_mapeditor.jpg", dataLoaderTicker );

      GraphicSetManager::Instance().loadData();
      loadEditordata();

      if ( mapname && mapname[0] ) {


            if( patimat ( mapextension, mapname ))
               actmap = mapLoadingExceptionChecker( mapname, MapLoadingFunction( tmaploaders::loadmap ));
            else
               fatalError ( "%s is not an accepted file format", mapname );
      } else
         buildemptymap();

      mapSwitcher.toggle();
      if ( exist ( "palette.map" ))
         actmap = mapLoadingExceptionChecker( "palette.map", MapLoadingFunction( tmaploaders::loadmap ));

      if (!actmap )
         buildemptymap();

      actmap->preferredFileNames.mapname[0] = "";

      mapSwitcher.toggle();

   }
   catch ( ParsingError err ) {
      fatalError ( "Error parsing text file " + err.getMessage() );
   }
   catch ( tfileerror err ) {
      fatalError ( "Error loading file " + err.getFileName() );
   }
   catch ( ASCmsgException err ) {
      fatalError( "Error loading file " + err.getMessage() );
   }

   activefontsettings.font = schriften.arial8;
   activefontsettings.color =lightblue ;
   activefontsettings.background =3;
   activefontsettings.length =100;
   activefontsettings.justify =lefttext;


   setstartvariables();

   mainScreenWidget = new Maped_MainScreenWidget( getPGApplication());
   mainScreenWidget->Show();

   mousevisible(true);

   getPGApplication().Run();

   if (mapsaved == false )
      if (choice_dlg("You have unsaved changes! Save?","~y~es","~n~o") == 1)
         k_savemap(false);

   if ( actmap ) {
      delete actmap;
      actmap = NULL;
   }
   return 0;
}
