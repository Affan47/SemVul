setPixelPerTick(FXdouble space,FXbool notify){
  if(space<=0.0){ fxerror("%s::setPixelPerTick: illegal pixel per tick value.\n",getClassName()); }
  if(pixelPerTick!=space){
    pixelPerTick=space;
    recalc();
    update();
    if(notify && target) target->tryHandle(this,FXSEL(SEL_CHANGED,message),NULL);
    }
  }
