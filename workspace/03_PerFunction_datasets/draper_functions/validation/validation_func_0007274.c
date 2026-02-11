tile() {
    client *c;
    int n = 0;
    int y = 0;


    if(head != NULL && head->next == NULL) {
        XMoveResizeWindow(dis,head->win,0,0,sw-2,sh-2);
    }
    else if(head != NULL) {
        switch(mode) {
            case 0:

                XMoveResizeWindow(dis,head->win,0,0,master_size-2,sh-2);


                for(c=head->next;c;c=c->next) ++n;
                for(c=head->next;c;c=c->next) {
                    XMoveResizeWindow(dis,c->win,master_size,y,sw-master_size-2,(sh/n)-2);
                    y += sh/n;
                }
                break;
            case 1:
                for(c=head;c;c=c->next) {
                    XMoveResizeWindow(dis,c->win,0,0,sw,sh);
                }
                break;
            default:
                break;
        }
    }
}
