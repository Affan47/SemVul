setTrackYear(const FXIntList & tracks,FXuint year){
  FXString mrl;
  try {
    for (FXint i=0;i<tracks.no();i++) {
      update_track_year.setParameter(0,(FXint)year);
      update_track_year.setParameter(1,tracks[i]);
      update_track_year.execute();
      update_track_year.reset();
      }
    }
  catch (FXExecuteException &){
     return false;
     }
  return true;
  }
