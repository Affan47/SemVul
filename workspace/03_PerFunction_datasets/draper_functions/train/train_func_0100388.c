BuildingTypeBaseWidget( PG_Widget* parent, const PG_Point& pos, int width, const BuildingType* buildingType, const Player& player ) : SelectionWidget( parent, PG_Rect( pos.x, pos.y, width, getBuildingHeight(buildingType)+10 )), vt( buildingType ), actplayer(player)
{

   new PG_Label( this, PG_Rect( buildingWidth, 20, Width() - buildingWidth - 10, 25 ), vt->name );

   SetTransparency( 255 );
}
