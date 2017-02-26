package metier;

import java.util.List;

public interface PortiqueService {
    Portique add(Portique portique);
    boolean remove(Portique portique);
    boolean update(Portique portique);
    List<Portique> getAll(int debut, int parPage);
    int getCount();
    Portique getById(long id);
    Portique getByLecteurRFID(LecteurRFID lecteur);
    List<LecteurRFID> getListLecteurRFID(int debut, int parPage);
    int getCountListLecteurRFID();
    List<Portique> getBySalle(Salle salle, int debut, int parPage);
    int getCountBySalle(Salle salle);
    List<Salle> getListSalle(int debut, int parPage);
    int getCountListSalle();
}
