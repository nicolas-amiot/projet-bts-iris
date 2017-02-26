package physique;

import java.util.List;
import metier.Metrologue;

public interface MetrologueDataService {
    Metrologue add(Metrologue metrologue) throws Exception;
    boolean remove(Metrologue metrologue) throws Exception;
    boolean update(Metrologue metrologue) throws Exception;
    List<Metrologue> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Metrologue getById(long id) throws Exception;
    Metrologue getByLogin(String login) throws Exception;
    List<String> getListLogin(int debut, int parPage) throws Exception;
    int getCountListLogin() throws Exception;
}
