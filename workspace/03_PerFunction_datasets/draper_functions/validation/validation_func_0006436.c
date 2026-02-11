operator<<(ostream& out, TFQDN& fqdn) {
  out << "<fqdn";
  if (fqdn.Duid) {
    out << " duid=\"" << fqdn.Duid->getPlain() << "\"";
  }
  if (fqdn.Addr) {
    out << " addr=\"" << fqdn.Addr->getPlain() << "\"";
  }

  out << " used=\"" << (fqdn.used?"TRUE":"FALSE") << "\">" << fqdn.getName() << "</fqdn>" << endl;
  return out;
}
