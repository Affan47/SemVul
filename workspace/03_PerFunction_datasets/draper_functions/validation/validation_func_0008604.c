handlemsg(htmsg *msg)
{
	if (msg->msg==msg_keypressed) {
		switch (msg->data1.integer) {
			case K_Left:
				sel-=size.h;
				if (sel<0) sel=0;
				dirtyview();
				clearmsg(msg);
				return;
			case K_Right:
				sel+=size.h;
				if (sel>=scount) sel=scount-1;
				dirtyview();
				clearmsg(msg);
				return;
			case K_Up:
				sel--;
				if (sel<0) sel=0;
				dirtyview();
				clearmsg(msg);
				return;
			case K_Down:
				sel++;
				if (sel>=scount) sel=scount-1;
				dirtyview();
				clearmsg(msg);
				return;


		}
	}
	ht_cluster::handlemsg(msg);
}
