multi_pxo_chat_process()
{
	char *remainder;
	char *result;
	char msg[512];
	int msg_pixel_width;


	memset(msg, 0, 512);
	Multi_pxo_chat_input.get_text(msg);
	remainder = "";


	gr_get_string_size(&msg_pixel_width, NULL, msg);
	if ( msg_pixel_width >= (Multi_pxo_input_coords[gr_screen.res][2])) {
		remainder = strrchr(msg, ' ');
		if ( remainder ) {
			*remainder = '\0';
			remainder++;
		} else {
			remainder = "";
		}


		if(ON_CHANNEL()){
			result = SendChatString(msg,1);
			if(result != NULL){
				multi_pxo_chat_process_incoming(result);
			}


			Multi_pxo_chat_input.set_text(remainder);
		} else {
			Multi_pxo_chat_input.set_text("");
		}
	} else if((Multi_pxo_chat_input.pressed() && (msg[0] != '\0')) || (strlen(msg) >= MAX_CHAT_LINE_LEN)) {

		int x = strlen(msg);
		if(x >= MAX_CHAT_LINE_LEN){
			msg[MAX_CHAT_LINE_LEN-1] = '\0';
		}


		if(multi_pxo_is_nick_command(msg)){
			Multi_pxo_chat_input.set_text("");
			return;
		}


		if(ON_CHANNEL()){
			result = SendChatString(msg,1);
			if(result != NULL){
				multi_pxo_chat_process_incoming(result);
			}


			Multi_pxo_chat_input.set_text(remainder);
		} else {
			Multi_pxo_chat_input.set_text("");
		}
	}
}
