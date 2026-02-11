operator<<( std::ostream &out, GRA_boxPlot const &bp )
{
  out << "<boxplot nrow=\"" << bp.nrow_ << "\" fmin=\"" << bp.fmin_
      << "\" fmax=\"" << bp.fmax_ << "\" gmin=\"" << bp.gmin_ << "\" gmax=\""
      << bp.gmax_ << "\" xprofile=\"" << bp.xProfile_ << "\" yprofile=\""
      << bp.yProfile_ << "\" border=\"" << bp.border_ << "\" zoom=\""
      << bp.zoom_ << "\" axes=\"" << bp.drawAxes_ << "\" reset=\"" << bp.resetAxes_
      << "\" bscale=\"" << bp.bscale_ << "\">\n";
  int size = bp.x_.size();
  out << "<data size=\"" << size << "\">";
  for( int i=0; i<size; ++i )out << bp.x_[i] << " ";
  out << "</data>\n";
  size = bp.y_.size();
  out << "<data size=\"" << size << "\">";
  for( int i=0; i<size; ++i )out << bp.y_[i] << " ";
  out << "</data>\n";
  size = bp.z_.size();
  out << "<data size=\"" << size << "\">";
  for( int i=0; i<size; ++i )out << bp.z_[i] << " ";
  return out << "</data>\n</boxplot>\n";
}
