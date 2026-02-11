beginEdit() {
  update_track_genre_id.compile(db,"UPDATE tracks SET genre = ? WHERE id == ?;");
  update_mrl.compile(db,"UPDATE tracks SET path = ?, mrl = ? WHERE id == ?;");
  update_artist_album_id.compile(db,"UPDATE albums SET artist = ? WHERE id == ?;");
  update_track_title.compile(db,"UPDATE tracks SET title = ? WHERE id == ?;");
  update_track_album_id.compile(db,"UPDATE tracks SET album = ? WHERE id == ?;");
  update_track_genre.compile(db,"UPDATE tracks SET genre = ? WHERE genre == ?;");
  update_track_artist.compile(db,"UPDATE tracks SET artist = ? WHERE id == ?;");
  update_track_no.compile(db,"UPDATE tracks SET no = ? WHERE id == ?;");
  update_track_disc.compile(db,"UPDATE tracks SET no = ((no&65535)|(?<<16)) WHERE id == ?;");
  update_track_track.compile(db,"UPDATE tracks SET no = ((no&1048560)|?) WHERE id == ?;");
  update_track_importdate.compile(db,"UPDATE tracks SET importdate = ? WHERE id == ?;");


  update_track_year.compile(db,"UPDATE tracks SET year = ? WHERE id == ?;");
  update_track.compile(db,"UPDATE tracks SET title = ?, time = ?, no = ?, year = ?, album = ?, genre = ?, artist = ?, replay_gain = ?, replay_peak = ?, importdate = ? WHERE id == ?;");
  update_album.compile(db,"UPDATE albums SET year = ?, replay_gain = ?, replay_peak = ? WHERE id == ?;");

  query_track_no.compile(db,"SELECT no FROM tracks WHERE id == ?;");

  query_album_existing.compile(db,"SELECT id FROM albums WHERE artist == ? AND name == (SELECT albums.name FROM albums WHERE albums.id == (SELECT album FROM tracks WHERE id == ? ));");
  insert_album_existing.compile(db,"INSERT INTO albums ( name, artist, year, replay_gain, replay_peak) SELECT ?, ?, year,replay_gain,replay_peak FROM albums WHERE id == (SELECT album FROM tracks WHERE id == ? ) ;");
  insert_album_existing_name.compile(db,"INSERT INTO albums ( name, artist, year, replay_gain, replay_peak) SELECT name, ?, year,replay_gain,replay_peak FROM albums WHERE id == (SELECT album FROM tracks WHERE id == ? ) ;");
  query_artist_album.compile(db,"SELECT artist FROM albums WHERE id == (SELECT album FROM tracks WHERE id == ?);");


  }
