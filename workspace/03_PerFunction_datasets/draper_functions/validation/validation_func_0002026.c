checkObject( MapField* fld, ObjectType* objtype, Mode mode )
{
    if ( !objtype || !fld )
       return false;

    Vehicle* veh = getUnit();

    if ( mode == Build ) {
       if ( objtype->getFieldModification(fld->getWeather()).terrainaccess.accessible( fld->bdt ) > 0
            &&  !fld->checkForObject ( objtype )
            && objtype->techDependency.available(getMap()->player[veh->getOwner()].research) ){


          if ( veh->getResource(objtype->buildcost, true) == objtype->buildcost && veh->getMovement() >= objtype->build_movecost )
             return true;
       }
    } else {
       if ( fld->checkForObject ( objtype ) ) {

          Resources r = objtype->removecost;
          for ( int i = 0; i <3; ++i )
             if ( r.resource(i) < 0 )
                r.resource(i) = 0;

          if ( veh->getResource(r, true) == r && veh->getMovement() >= objtype->remove_movecost )
             return true;
       }
    }
    return false;
}
