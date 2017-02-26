package physique;

import java.util.List;
import metier.LecteurRFID;

public interface LecteurRFIDDataService {
    LecteurRFID add(LecteurRFID lecteur) throws Exception;
    boolean remove(LecteurRFID lecteur) throws Exception;
    boolean update(LecteurRFID lecteur) throws Exception;
    List<LecteurRFID> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    LecteurRFID getById(long id) throws Exception;
    LecteurRFID getByIp(String ip) throws Exception;
    List<String> getListIp(int debut, int parPage) throws Exception;
    int getCountListIp() throws Exception;
    List<LecteurRFID> getByModele(String modele, int debut, int parPage) throws Exception;
    int getCountByModele(String modele) throws Exception;
    List<String> getListModele(int debut, int parPage) throws Exception;
    int getCountListModele() throws Exception;
    List<LecteurRFID> getByEtatOn(boolean etatOn, int debut, int parPage) throws Exception;
    int getCountByEtatOn(boolean etatOn) throws Exception;
}
