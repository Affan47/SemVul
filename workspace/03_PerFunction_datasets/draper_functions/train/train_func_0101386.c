send_turret_fired_packet( int ship_objnum, int subsys_index, int weapon_objnum )
{
	int packet_size;
	ushort pnet_signature;
	ubyte data[MAX_PACKET_SIZE], cindex;
	object *objp;
	ubyte has_sig = 0;
	ship_subsys *ssp;
	short val;


	if((weapon_objnum < 0) || (Objects[weapon_objnum].type != OBJ_WEAPON) || (Objects[weapon_objnum].instance < 0) || (Weapons[Objects[weapon_objnum].instance].weapon_info_index < 0)){
		return;
	}


	objp = &Objects[weapon_objnum];
	Assert ( objp->type == OBJ_WEAPON );
	if(Weapon_info[Weapons[objp->instance].weapon_info_index].subtype == WP_MISSILE){
		has_sig = 1;
	}

	pnet_signature = Objects[ship_objnum].net_signature;

	Assert( subsys_index < UCHAR_MAX );
	cindex = (ubyte)subsys_index;

	ssp = ship_get_indexed_subsys( &Ships[Objects[ship_objnum].instance], subsys_index, NULL );
	if(ssp == NULL){
		return;
	}


	BUILD_HEADER(FIRE_TURRET_WEAPON);
	packet_size += multi_pack_unpack_position(1, data + packet_size, &objp->orient.vec.fvec);
	ADD_DATA( has_sig );
	ADD_USHORT( pnet_signature );
	if(has_sig){
		ADD_USHORT( objp->net_signature );
	}
	ADD_DATA( cindex );
	val = (short)ssp->submodel_info_1.angs.h;
	ADD_SHORT( val );
	val = (short)ssp->submodel_info_2.angs.p;
	ADD_SHORT( val );

	multi_io_send_to_all(data, packet_size);

	multi_rate_add(1, "tur", packet_size);
}
