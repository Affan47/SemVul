operator<<( std::ostream &out, GraphicsPage const *gp )
{
  out << "<graphicspage currentwindow=\"" << gp->currentWindowNumber_ << "\">\n";
  for( std::size_t i=0; i<gp->graphWindows_.size(); ++i )out << *gp->graphWindows_[i];
  return out << "</graphicspage>\n";
}
