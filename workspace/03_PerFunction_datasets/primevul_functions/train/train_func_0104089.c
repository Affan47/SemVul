void Server::handleCommand_InventoryAction(NetworkPacket* pkt)
{
	session_t peer_id = pkt->getPeerId();
	RemotePlayer *player = m_env->getPlayer(peer_id);

	if (player == NULL) {
		errorstream <<
			"Server::ProcessData(): Canceling: No player for peer_id=" <<
			peer_id << " disconnecting peer!" << std::endl;
		DisconnectPeer(peer_id);
		return;
	}

	PlayerSAO *playersao = player->getPlayerSAO();
	if (playersao == NULL) {
		errorstream <<
			"Server::ProcessData(): Canceling: No player object for peer_id=" <<
			peer_id << " disconnecting peer!" << std::endl;
		DisconnectPeer(peer_id);
		return;
	}


	std::string datastring(pkt->getString(0), pkt->getSize());
	verbosestream << "TOSERVER_INVENTORY_ACTION: data=" << datastring
		<< std::endl;
	std::istringstream is(datastring, std::ios_base::binary);

	InventoryAction *a = InventoryAction::deSerialize(is);
	if (!a) {
		infostream << "TOSERVER_INVENTORY_ACTION: "
				<< "InventoryAction::deSerialize() returned NULL"
				<< std::endl;
		return;
	}


	RollbackScopeActor rollback_scope(m_rollback,
			std::string("player:")+player->getName());


	if (a->getType() == IAction::Move) {
		IMoveAction *ma = (IMoveAction*)a;

		ma->from_inv.applyCurrentPlayer(player->getName());
		ma->to_inv.applyCurrentPlayer(player->getName());

		m_inventory_mgr->setInventoryModified(ma->from_inv);
		if (ma->from_inv != ma->to_inv)
			m_inventory_mgr->setInventoryModified(ma->to_inv);

		bool from_inv_is_current_player = false;
		if (ma->from_inv.type == InventoryLocation::PLAYER) {
			if (ma->from_inv.name != player->getName())
				return;
			from_inv_is_current_player = true;
		}

		bool to_inv_is_current_player = false;
		if (ma->to_inv.type == InventoryLocation::PLAYER) {
			if (ma->to_inv.name != player->getName())
				return;
			to_inv_is_current_player = true;
		}

		InventoryLocation *remote = from_inv_is_current_player ?
			&ma->to_inv : &ma->from_inv;


		if (remote->type == InventoryLocation::NODEMETA) {
			v3f node_pos   = intToFloat(remote->p, BS);
			v3f player_pos = player->getPlayerSAO()->getEyePosition();
			f32 d = player_pos.getDistanceFrom(node_pos);
			if (!checkInteractDistance(player, d, "inventory"))
				return;
		}


		if (ma->from_list == "craftpreview") {
			infostream << "Ignoring IMoveAction from "
					<< (ma->from_inv.dump()) << ":" << ma->from_list
					<< " to " << (ma->to_inv.dump()) << ":" << ma->to_list
					<< " because src is " << ma->from_list << std::endl;
			delete a;
			return;
		}


		if (ma->to_list == "craftpreview" || ma->to_list == "craftresult") {
			infostream << "Ignoring IMoveAction from "
					<< (ma->from_inv.dump()) << ":" << ma->from_list
					<< " to " << (ma->to_inv.dump()) << ":" << ma->to_list
					<< " because dst is " << ma->to_list << std::endl;
			delete a;
			return;
		}


		if (!checkPriv(player->getName(), "interact") &&
				(!from_inv_is_current_player ||
				!to_inv_is_current_player)) {
			infostream << "Cannot move outside of player's inventory: "
					<< "No interact privilege" << std::endl;
			delete a;
			return;
		}
	}


	else if (a->getType() == IAction::Drop) {
		IDropAction *da = (IDropAction*)a;

		da->from_inv.applyCurrentPlayer(player->getName());

		m_inventory_mgr->setInventoryModified(da->from_inv);


		if (da->from_list == "craftpreview") {
			infostream << "Ignoring IDropAction from "
					<< (da->from_inv.dump()) << ":" << da->from_list
					<< " because src is " << da->from_list << std::endl;
			delete a;
			return;
		}


		if (!checkPriv(player->getName(), "interact")) {
			delete a;
			return;
		}


		if (playersao->isDead()) {
			infostream << "Ignoring IDropAction from "
					<< (da->from_inv.dump()) << ":" << da->from_list
					<< " because player is dead." << std::endl;
			delete a;
			return;
		}
	}


	else if (a->getType() == IAction::Craft) {
		ICraftAction *ca = (ICraftAction*)a;

		ca->craft_inv.applyCurrentPlayer(player->getName());

		m_inventory_mgr->setInventoryModified(ca->craft_inv);


		if (!checkPriv(player->getName(), "interact")) {
			infostream << "Cannot craft: "
					<< "No interact privilege" << std::endl;
			delete a;
			return;
		}
	}


	a->apply(m_inventory_mgr.get(), playersao, this);

	delete a;
}
