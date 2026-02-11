validerDate( int jour, int mois, int annee){
	return (!(mois < 0 || mois > 12 || jour < 0 || jour > nbJours(mois,annee)));
}
