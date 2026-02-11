GetEffectDescription(){

   return wxString::Format(_("Applied effect: %s stretch factor = %f times, time resolution = %f seconds"),
         this->GetEffectName().c_str(), amount,time_resolution);

}
