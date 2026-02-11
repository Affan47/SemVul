operator== (const state& otherState) const{
	if(otherState.boardMemoryAllocated == false) return false;
	if(this->getBoard()[0][0] != otherState.getBoard()[0][0])return false;
	if(this->getBoard()[0][1] != otherState.getBoard()[0][1])return false;
	if(this->getBoard()[0][2] != otherState.getBoard()[0][2])return false;
	if(this->getBoard()[1][0] != otherState.getBoard()[1][0])return false;
	if(this->getBoard()[1][1] != otherState.getBoard()[1][1])return false;
	if(this->getBoard()[1][2] != otherState.getBoard()[1][2])return false;
	if(this->getBoard()[2][0] != otherState.getBoard()[2][0])return false;
	if(this->getBoard()[2][1] != otherState.getBoard()[2][1])return false;
	if(this->getBoard()[2][2] != otherState.getBoard()[2][2])return false;
	return true;
}
