package physique;

import java.util.List;
import metier.LecteurRFID;
import metier.Portique;
import metier.Salle;

public interface PortiqueDataService {
    Portique add(Portique portique) throws Exception;
    boolean remove(Portique portique) throws Exception;
    boolean update(Portique portique) throws Exception;
    List<Portique> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Portique getById(long id) throws Exception;
    Portique getByLecteurRFID(LecteurRFID lecteur) throws Exception;
    List<LecteurRFID> getListLecteurRFID(int debut, int parPage) throws Exception;
    int getCountListLecteurRFID() throws Exception;
    List<Portique> getBySalle(Salle salle, int debut, int parPage) throws Exception;
    int getCountBySalle(Salle salle) throws Exception;
    List<Salle> getListSalle(int debut, int parPage) throws Exception;
    int getCountListSalle() throws Exception;
}
