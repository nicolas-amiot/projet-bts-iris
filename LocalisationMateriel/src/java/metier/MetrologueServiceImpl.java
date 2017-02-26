package metier;

import java.util.ArrayList;
import java.util.List;
import physique.MetrologueDataService;
import physique.PhysiqueFactory;

public class MetrologueServiceImpl implements MetrologueService {

    private final MetrologueDataService metrologueDataSrv;

    MetrologueServiceImpl() {
        metrologueDataSrv = PhysiqueFactory.getMetrologueDataService();
    }

    @Override
    public Metrologue add(Metrologue metrologue) {
        Metrologue met = null;
        try {
            if (!metrologue.getLogin().isEmpty() && !metrologue.getPassword().isEmpty()) {
                met = metrologueDataSrv.add(metrologue);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return met;
    }

    @Override
    public boolean remove(Metrologue metrologue) {
        boolean execute = false;
        try {
            if (metrologue.getId() > 0) {
                execute = metrologueDataSrv.remove(metrologue);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Metrologue metrologue) {
        boolean execute = false;
        try {
            if (metrologue.getId() > 0) {
                if (!metrologue.getLogin().isEmpty() && !metrologue.getPassword().isEmpty()) {
                    execute = metrologueDataSrv.update(metrologue);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Metrologue> getAll(int debut, int parPage) {
        List<Metrologue> met = new ArrayList<Metrologue>();
        try {
            if (debut >= 0 && parPage > 0) {
                met = metrologueDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return met;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = metrologueDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Metrologue getById(long id) {
        Metrologue met = null;
        try {
            if (id > 0) {
                met = metrologueDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return met;
    }

    @Override
    public Metrologue getByLogin(String login) {
        Metrologue met = null;
        try {
            if (!login.isEmpty()) {
                met = metrologueDataSrv.getByLogin(login);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return met;
    }

    @Override
    public List<String> getListLogin(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = metrologueDataSrv.getListLogin(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListLogin() {
        int count = 0;
        try {
            count = metrologueDataSrv.getCountListLogin();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
