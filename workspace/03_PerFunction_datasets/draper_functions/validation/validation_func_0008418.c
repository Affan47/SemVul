setCurrentItem(FXint index,FXbool notify){
  if(index<-1 || items.no()<=index){ fxerror("%s::setCurrentItem: index out of range.\n",getClassName()); }
  if(index!=current){


    if(0<=current){


      if(hasFocus()){
        items[current]->setFocus(false);
        updateItem(current);
        }
      }

    current=index;


    if(0<=current){


      if(hasFocus()){
        items[current]->setFocus(true);
        updateItem(current);
        }
      }


    if(notify && target){target->tryHandle(this,FXSEL(SEL_CHANGED,message),(void*)(FXival)current);}
    }


  if((options&SELECT_MASK)==TRACKLIST_BROWSESELECT && 0<=current ){
    selectItem(current,notify);
    }
  }
