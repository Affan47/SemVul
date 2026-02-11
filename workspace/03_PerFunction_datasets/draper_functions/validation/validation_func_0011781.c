multi_free_server_list()
{
	server_item *moveup,*backup;

	moveup = Game_server_head;
	backup = NULL;
	if(moveup != NULL){
		do {
			backup = moveup;
			moveup = moveup->next;

			vm_free(backup);
			backup = NULL;
		} while(moveup != Game_server_head);
		Game_server_head = NULL;
	}
}
