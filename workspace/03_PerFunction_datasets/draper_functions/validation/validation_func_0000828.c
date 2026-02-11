on_mouse_move(GdkEventMotion* event){
  if(press){
    int x,y;
    get_pointer(x, y);
    set_value(x,y);
   }
  return true;
}
