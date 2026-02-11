onEvent(Event* const event) {
	if (event->id() == WantItems::ID) {

		WantItems* e = static_cast<WantItems*> (event);
		for (map<unsigned char, Item>::iterator i = e->items().begin(); i != e->items().end(); ++i) {
			if (i->second.name() == "gold piece")
				i->second.want(i->second.count());
		}
	}
}
