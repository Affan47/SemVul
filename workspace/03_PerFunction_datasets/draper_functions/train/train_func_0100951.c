on_draw_game()
{
    if(board->is_fight_to_robot()){
		board->draw_move();
    }
	else if(board->is_network_game()){
		if(board->is_human_player()){
			board->send_to_socket("draw");
		}else{
			Gtk::MessageDialog dialog(*this, _("Warning"), false);
			Glib::ustring msg =_("Only ask rue game when you are going,so wait a minute!");
			dialog.set_secondary_text(msg);
			dialog.run();
		}
	}

}
