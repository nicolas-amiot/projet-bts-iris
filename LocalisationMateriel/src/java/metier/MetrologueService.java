package metier;

import java.util.List;

public interface MetrologueService {
    Metrologue add(Metrologue metrologue);
    boolean remove(Metrologue metrologue);
    boolean update(Metrologue metrologue);
    List<Metrologue> getAll(int debut, int parPage);
    int getCount();
    Metrologue getById(long id);
    Metrologue getByLogin(String login);
    List<String> getListLogin(int debut, int parPage);
    int getCountListLogin();
}
