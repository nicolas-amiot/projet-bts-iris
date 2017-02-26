package metier;

import java.util.List;

public interface LocalisationService {
    Localisation add(Localisation localisation);
    boolean remove(Localisation localisation);
    boolean update(Localisation localisation);
    List<Localisation> getAll(int debut, int parPage);
    int getCount();
    Localisation getById(long id);
    List<Localisation> getBySalle(Salle salle, int debut, int parPage);
    int getCountBySalle(Salle salle);
    List<Salle> getListSalle(int debut, int parPage);
    int getCountListSalle();
    Localisation getByMateriel(Materiel materiel);
    List<Materiel> getListMateriel(int debut, int parPage);
    int getCountListMateriel();
    List<Localisation> getBySortie(boolean sortie, int debut, int parPage);
    int getCountBySortie(boolean sortie);
}
