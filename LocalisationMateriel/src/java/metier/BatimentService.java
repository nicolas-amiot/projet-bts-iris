package metier;

import java.util.List;

public interface BatimentService {
    Batiment add(Batiment batiment);
    boolean remove(Batiment batiment);
    boolean update(Batiment batiment);
    List<Batiment> getAll(int debut, int parPage);
    int getCount();
    Batiment getById(long id);
    Batiment getByNomBatiment(String nomBatiment);
    List<String> getListNomBatiment(int debut, int parPage);
    int getCountListNomBatiment();
    Batiment getBySalle(Salle salle);
    List<Salle> getListSalle(int debut, int parPage);
    int getCountListSalle();
    Batiment getByPlan(String plan);
    List<String> getListPlan(int debut, int parPage);
    int getCountListPlan();
}
