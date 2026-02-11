findLamp() {
	map<unsigned char, Item>::iterator l = Inventory::items().find(_lamp_key);
	if (l != Inventory::items().end() && (data::Lamp::lamps().find(l->second.name()) != data::Lamp::lamps().end()))
		return;
	for (l = Inventory::items().begin(); l != Inventory::items().end(); ++l) {
		if (data::Lamp::lamps().find(l->second.name()) == data::Lamp::lamps().end())
			continue;

		_lamp_key = l->first;

		if (_seen_oil_lamp && !_seen_magic_lamp && l->second.name() == "lamp") {

			World::queueAction(new action::Call(this, l->first, "magic lamp"));
			_seen_magic_lamp = true;
		} else if (!_seen_oil_lamp && _seen_magic_lamp && l->second.name() == "lamp") {

			World::queueAction(new action::Call(this, l->first, "oil lamp"));
			_seen_oil_lamp = true;
		}
		return;
	}

	_lamp_key = ILLEGAL_ITEM;
}
