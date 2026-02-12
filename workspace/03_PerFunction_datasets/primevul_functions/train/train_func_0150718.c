void CClient::EnterGame()
{
	if(State() == IClient::STATE_DEMOPLAYBACK)
		return;


	SendEnterGame();
	OnEnterGame();
}
