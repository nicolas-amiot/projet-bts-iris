package metier;

import java.util.List;

public interface SalleService {
    Salle add(Salle salle);
    boolean remove(Salle salle);
    boolean update(Salle salle);
    List<Salle> getAll(int debut, int parPage);
    int getCount();
    Salle getById(long id);
    List<Salle> getByNomSalle(String nomSalle, int debut, int parPage);
    int getCountByNomSalle(String nomSalle);
    List<String> getListNomSalle(int debut, int parPage);
    int getCountListNomSalle();
    Salle getByNumSalle(int numSalle);
    List<Integer> getListNumSalle(int debut, int parPage);
    int getCountListNumSalle();
    List<Salle> getByNomAtelier(String nomAtelier, int debut, int parPage);
    int getCountByNomAtelier(String nomAtelier);
    List<String> getListNomAtelier(int debut, int parPage);
    int getCountListNomAtelier();
}
