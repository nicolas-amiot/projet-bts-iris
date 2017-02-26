package physique;

import java.util.List;
import metier.Localisation;
import metier.Materiel;
import metier.Salle;

public interface LocalisationDataService {
    Localisation add(Localisation localisation) throws Exception;
    boolean remove(Localisation localisation) throws Exception;
    boolean update(Localisation localisation) throws Exception;
    List<Localisation> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Localisation getById(long id) throws Exception;
    List<Localisation> getBySalle(Salle salle, int debut, int parPage) throws Exception;
    int getCountBySalle(Salle salle) throws Exception;
    List<Salle> getListSalle(int debut, int parPage) throws Exception;
    int getCountListSalle() throws Exception;
    Localisation getByMateriel(Materiel materiel) throws Exception;
    List<Materiel> getListMateriel(int debut, int parPage) throws Exception;
    int getCountListMateriel() throws Exception;
    List<Localisation> getBySortie(boolean sortie, int debut, int parPage) throws Exception;
    int getCountBySortie(boolean sortie) throws Exception;
}
