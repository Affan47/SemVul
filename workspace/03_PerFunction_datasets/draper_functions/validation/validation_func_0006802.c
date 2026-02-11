selectVehicle( vector<Vehicle*> targets )
{
   Vehicle* target = NULL;
   VehicleSelectionFactory* vsf = new VehicleSelectionFactory( targets );
   ItemSelectorWindow isw ( NULL, PG_Rect( 50, 50, 300, 400), "Please choose target unit", vsf );
   isw.Show();
   isw.RunModal();
   target = vsf->selected;
   return target;
}
