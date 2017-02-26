package physique;

import java.util.List;
import metier.Batiment;
import metier.Salle;

public interface BatimentDataService {
    Batiment add(Batiment batiment) throws Exception;
    boolean remove(Batiment batiment) throws Exception;
    boolean update(Batiment batiment) throws Exception;
    List<Batiment> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Batiment getById(long id) throws Exception;
    Batiment getByNomBatiment(String nomBatiment) throws Exception;
    List<String> getListNomBatiment(int debut, int parPage) throws Exception;
    int getCountListNomBatiment() throws Exception;
    Batiment getBySalle(Salle salle) throws Exception;
    List<Salle> getListSalle(int debut, int parPage) throws Exception;
    int getCountListSalle() throws Exception;
    Batiment getByPlan(String plan) throws Exception;
    List<String> getListPlan(int debut, int parPage) throws Exception;
    int getCountListPlan() throws Exception;
}
