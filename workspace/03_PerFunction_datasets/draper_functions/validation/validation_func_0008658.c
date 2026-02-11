UTMUPSString(int zone, real easting, real northing, int prec,
                               std::string& utm) const {
    ostringstream os;
    prec = max(-5, min(9, prec));
    real scale = prec < 0 ? pow(real(10), -prec) : real(1);
    os << UTMUPS::EncodeZone(zone, _northp) << fixed << setfill('0');
    if (Math::isfinite(easting)) {
      os << " " << setprecision(max(0, prec)) << easting / scale;
      if (prec < 0 && abs(easting / scale) > real(0.5))
        os << setw(-prec) << 0;
    } else
      os << " nan";
    if (Math::isfinite(northing)) {
      os << " " << setprecision(max(0, prec)) << northing / scale;
      if (prec < 0 && abs(northing / scale) > real(0.5))
        os << setw(-prec) << 0;
    } else
      os << " nan";
    utm = os.str();
  }
