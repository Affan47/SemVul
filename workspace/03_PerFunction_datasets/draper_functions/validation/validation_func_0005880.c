request_resize(int width, int height){
  gtk_window_resize(GTK_WINDOW(toplevel_window),width,height);
  if(gameboard->resize_timeout)
    gameboard->resize_timeout = time(NULL)+3;
  gameboard->resize_w = width;
  gameboard->resize_h = height;
}
