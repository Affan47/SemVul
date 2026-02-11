printPath(state* current_state, state* goal, bool allowDoubleMoves){

	stack<state> pathStack = *new stack<state>();
	int moveCount = 0;
	while(current_state->getG() != -1){
		pathStack.push(*current_state);
		current_state = current_state->getParent();
		moveCount++;
	}
	for(int i = 0 ; i < moveCount ; i++){
		cout << pathStack.top().getMove();
		cout << endl << endl;
		cout << pathStack.top();
		cout << endl;
		pathStack.pop();

	}
	cout << moveCount << " moves in total.";
	cout << endl << endl;


	list<state*>::iterator delIter;
	list<state*>::iterator deleteiter;
	deleteiter = OPEN.erase(OPEN.begin(),OPEN.end());
	CLOSED.erase(CLOSED.begin(), CLOSED.end());
}
