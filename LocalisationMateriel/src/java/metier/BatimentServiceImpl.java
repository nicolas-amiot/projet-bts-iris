package metier;

import java.util.ArrayList;
import java.util.List;
import physique.BatimentDataService;
import physique.PhysiqueFactory;

public class BatimentServiceImpl implements BatimentService {

    private final BatimentDataService batimentDataSrv;

    BatimentServiceImpl() {
        batimentDataSrv = PhysiqueFactory.getBatimentDataService();
    }

    @Override
    public Batiment add(Batiment batiment) {
        Batiment bat = null;
        try {
            if (!batiment.getNomBatiment().isEmpty() && !batiment.getPlan().isEmpty()) {
                bat = batimentDataSrv.add(batiment);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return bat;
    }

    @Override
    public boolean remove(Batiment batiment) {
        boolean execute = false;
        try {
            if (batiment.getId() > 0) {
                execute = batimentDataSrv.remove(batiment);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Batiment batiment) {
        boolean execute = false;
        try {
            if (batiment.getId() > 0) {
                if (!batiment.getNomBatiment().isEmpty() && !batiment.getPlan().isEmpty()) {
                    execute = batimentDataSrv.update(batiment);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Batiment> getAll(int debut, int parPage) {
        List<Batiment> bat = new ArrayList<Batiment>();
        try {
            bat = batimentDataSrv.getAll(debut, parPage);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return bat;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = batimentDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Batiment getById(long id) {
        Batiment bat = null;
        try {
            if (id > 0) {
                bat = batimentDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return bat;
    }

    @Override
    public Batiment getByNomBatiment(String nomBatiment) {
        Batiment bat = null;
        try {
            if (!nomBatiment.isEmpty()) {
                bat = batimentDataSrv.getByNomBatiment(nomBatiment);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return bat;
    }

    @Override
    public List<String> getListNomBatiment(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = batimentDataSrv.getListNomBatiment(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListNomBatiment() {
        int count = 0;
        try {
            count = batimentDataSrv.getCountListNomBatiment();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Batiment getBySalle(Salle salle) {
        Batiment bat = null;
        try {
            if (salle.getId() > 0) {
                bat = batimentDataSrv.getBySalle(salle);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return bat;
    }

    @Override
    public List<Salle> getListSalle(int debut, int parPage) {
        List<Salle> salles = new ArrayList<Salle>();
        try {
            if (debut >= 0 && parPage > 0) {
                salles = batimentDataSrv.getListSalle(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return salles;
    }

    @Override
    public int getCountListSalle() {
        int count = 0;
        try {
            count = batimentDataSrv.getCountListSalle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Batiment getByPlan(String plan) {
        Batiment bat = null;
        try {
            if (!plan.isEmpty()) {
                bat = batimentDataSrv.getByPlan(plan);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return bat;
    }

    @Override
    public List<String> getListPlan(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = batimentDataSrv.getListPlan(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListPlan() {
        int count = 0;
        try {
            count = batimentDataSrv.getCountListPlan();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
