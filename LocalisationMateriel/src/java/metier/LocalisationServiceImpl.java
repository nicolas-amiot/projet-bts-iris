package metier;

import java.util.ArrayList;
import java.util.List;
import physique.LocalisationDataService;
import physique.PhysiqueFactory;

public class LocalisationServiceImpl implements LocalisationService {

    private final LocalisationDataService localisationDataSrv;

    LocalisationServiceImpl() {
        localisationDataSrv = PhysiqueFactory.getLocalisationDataService();
    }

    @Override
    public Localisation add(Localisation localisation) {
        Localisation loc = null;
        try {
            if (localisation.getMateriel().getId() > 0 && localisation.getSalle().getId() > 0) {
                loc = localisationDataSrv.add(localisation);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return loc;
    }

    @Override
    public boolean remove(Localisation localisation) {
        boolean execute = false;
        try {
            if (localisation.getId() > 0) {
                execute = localisationDataSrv.remove(localisation);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Localisation localisation) {
        boolean execute = false;
        try {
            if (localisation.getId() > 0) {
                if (localisation.getMateriel().getId() > 0 && localisation.getSalle().getId() > 0) {
                    execute = localisationDataSrv.update(localisation);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Localisation> getAll(int debut, int parPage) {
        List<Localisation> loc = null;
        try {
            if (debut >= 0 && parPage > 0) {
                loc = localisationDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return loc;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = localisationDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Localisation getById(long id) {
        Localisation loc = null;
        try {
            if (id > 0) {
                loc = localisationDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return loc;
    }

    @Override
    public List<Localisation> getBySalle(Salle salle, int debut, int parPage) {
        List<Localisation> loc = null;
        try {
            if (salle.getId() > 0) {
                if (debut >= 0 && parPage > 0) {
                    loc = localisationDataSrv.getBySalle(salle, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return loc;
    }

    @Override
    public int getCountBySalle(Salle salle) {
        int count = 0;
        try {
            if (salle.getId() > 0) {
                count = localisationDataSrv.getCountBySalle(salle);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Salle> getListSalle(int debut, int parPage) {
        List<Salle> salles = new ArrayList<Salle>();
        try {
            if (debut >= 0 && parPage > 0) {
                salles = localisationDataSrv.getListSalle(debut, parPage);
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
            count = localisationDataSrv.getCountListSalle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Localisation getByMateriel(Materiel materiel) {
        Localisation loc = null;
        try {
            if (materiel.getId() > 0) {
                loc = localisationDataSrv.getByMateriel(materiel);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return loc;
    }

    @Override
    public List<Materiel> getListMateriel(int debut, int parPage) {
        List<Materiel> materiels = new ArrayList<Materiel>();
        try {
            if (debut >= 0 && parPage > 0) {
                materiels = localisationDataSrv.getListMateriel(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return materiels;
    }

    @Override
    public int getCountListMateriel() {
        int count = 0;
        try {
            count = localisationDataSrv.getCountListMateriel();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Localisation> getBySortie(boolean sortie, int debut, int parPage) {
        List<Localisation> loc = new ArrayList<Localisation>();
        try {
            loc = localisationDataSrv.getBySortie(sortie, debut, parPage);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return loc;
    }

    @Override
    public int getCountBySortie(boolean sortie) {
        int count = 0;
        try {
            count = localisationDataSrv.getCountBySortie(sortie);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
