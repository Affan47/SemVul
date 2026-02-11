cargoChanged() {

         if ( cargoWidget ) {
            cargoWidget->redrawAll();
            if ( mainScreenWidget && mainScreenWidget->getUnitInfoPanel() )
               mainScreenWidget->getUnitInfoPanel()->showUnitData( cargoWidget->getMarkedUnit(), NULL, NULL, true );

            checkStoringPosition( cargoWidget->getMarkedUnit() );
         }
         sigCargoChanged();
         updateResourceDisplay();
         showAmmo();
         updateLoadMeter();
      }
