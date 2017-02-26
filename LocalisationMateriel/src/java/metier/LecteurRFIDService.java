package metier;

import java.util.List;

public interface LecteurRFIDService {
    LecteurRFID add(LecteurRFID lecteur);
    boolean remove(LecteurRFID lecteur);
    boolean update(LecteurRFID lecteur);
    List<LecteurRFID> getAll(int debut, int parPage);
    int getCount();
    LecteurRFID getById(long id);
    LecteurRFID getByIp(String ip);
    List<String> getListIp(int debut, int parPage);
    int getCountListIp();
    List<LecteurRFID> getByModele(String modele, int debut, int parPage);
    int getCountByModele(String modele);
    List<String> getListModele(int debut, int parPage);
    int getCountListModele();
    List<LecteurRFID> getByEtatOn(boolean etatOn, int debut, int parPage);
    int getCountByEtatOn(boolean etatOn);
}
