ai_abort_rearm_request(object *requester_objp)
{
	ship		*requester_shipp;
	ai_info	*requester_aip;

	Assert(requester_objp->type == OBJ_SHIP);
	if(requester_objp->type != OBJ_SHIP){
		return 0;
	}
	Assert((requester_objp->instance >= 0) && (requester_objp->instance < MAX_SHIPS));
	if((requester_objp->instance < 0) || (requester_objp->instance >= MAX_SHIPS)){
		return 0;
	}
	requester_shipp = &Ships[requester_objp->instance];
	Assert((requester_shipp->ai_index >= 0) && (requester_shipp->ai_index < MAX_AI_INFO));
	if((requester_shipp->ai_index < 0) || (requester_shipp->ai_index >= MAX_AI_INFO)){
		return 0;
	}
	requester_aip = &Ai_info[requester_shipp->ai_index];

	if (requester_aip->ai_flags & (AIF_AWAITING_REPAIR | AIF_BEING_REPAIRED)){


		if (requester_aip->support_ship_objnum != -1) {
			object	*repair_objp;
			ai_info	*repair_aip;

			repair_objp = &Objects[requester_aip->support_ship_objnum];
			repair_aip = &Ai_info[Ships[repair_objp->instance].ai_index];


			if (repair_objp->signature == requester_aip->support_ship_signature) {

				Assert( repair_objp->type == OBJ_SHIP );


				if ( repair_aip->submode < AIS_UNDOCK_0 ) {
					ai_do_objects_repairing_stuff( requester_objp, repair_objp, REPAIR_INFO_ABORT );

					if ( repair_aip->submode == AIS_DOCK_4 )
					{
						repair_aip->submode = AIS_UNDOCK_0;
						repair_aip->submode_start_time = Missiontime;
					}
					else
					{

						ai_cleanup_dock_mode_subjective(repair_objp);
					}
				} else {
					nprintf(("AI", "Not aborting rearm since already undocking\n"));
				}
			}
		} else {


			ai_do_objects_repairing_stuff( requester_objp, NULL, REPAIR_INFO_ABORT );


			mission_remove_scheduled_repair(requester_objp);
		}

		return 1;
	} else if ( requester_aip->ai_flags & AIF_REPAIRING ) {


		if ( requester_aip->goal_objnum != -1 ) {
			int val;

			val = ai_abort_rearm_request( &Objects[requester_aip->goal_objnum] );
			return val;
		}
	}

	return 0;
}
