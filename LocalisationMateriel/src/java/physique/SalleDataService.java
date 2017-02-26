package physique;

import java.util.List;
import metier.Salle;

public interface SalleDataService {
    Salle add(Salle salle) throws Exception;
    boolean remove(Salle salle) throws Exception;
    boolean update(Salle salle) throws Exception;
    List<Salle> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Salle getById(long id) throws Exception;
    List<Salle> getByNomSalle(String nomSalle, int debut, int parPage) throws Exception;
    int getCountByNomSalle(String nomSalle) throws Exception;
    List<String> getListNomSalle(int debut, int parPage) throws Exception;
    int getCountListNomSalle() throws Exception;
    Salle getByNumSalle(int numSalle) throws Exception;
    List<Integer> getListNumSalle(int debut, int parPage) throws Exception;
    int getCountListNumSalle() throws Exception;
    List<Salle> getByNomAtelier(String nomAtelier, int debut, int parPage) throws Exception;
    int getCountByNomAtelier(String nomAtelier) throws Exception;
    List<String> getListNomAtelier(int debut, int parPage) throws Exception;
    int getCountListNomAtelier() throws Exception;
}
