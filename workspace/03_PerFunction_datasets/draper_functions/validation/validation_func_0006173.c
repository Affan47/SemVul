RunGame()
{
	Awrite("Setting Up Turn...");
	PreProcessTurn();

	Awrite("Reading the Gamemaster File...");
	if(!ReadPlayers()) return(0);

	if(gameStatus == GAME_STATUS_FINISHED) {
		Awrite("This game is finished!");
		return(0);
	}
	gameStatus = GAME_STATUS_RUNNING;

	Awrite("Reading the Orders File...");
	ReadOrders();

	if(Globals->MAX_INACTIVE_TURNS != -1) {
		Awrite("QUITting Inactive Factions...");
		RemoveInactiveFactions();
	}

	Awrite("Running the Turn...");
	RunOrders();

	Awrite("Writing the Report File...");
	WriteReport();
	Awrite("");

	Awrite("Writing order templates...");
	WriteTemplates();
	Awrite("");
	battles.DeleteAll();

	EmptyHell();

	Awrite("Writing Playerinfo File...");
	WritePlayers();

	Awrite("Removing Dead Factions...");
	DeleteDeadFactions();
	Awrite("done");

	return(1);
}
