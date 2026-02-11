actionCompleted(const string&) {
	if (_answering_guard) {
		_answering_guard = false;
		_dropping_gold = true;
	} else if (_dropping_gold) {
		_dropping_gold = false;
		_following_guard = true;
		_last_saw_guard_turn = World::turn();
	}
}
