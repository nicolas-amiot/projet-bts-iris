package metier;

import java.util.ArrayList;
import java.util.List;
import physique.PhysiqueFactory;
import physique.PortiqueDataService;

public class PortiqueServiceImpl implements PortiqueService {

    private final PortiqueDataService portiqueDataSrv;

    PortiqueServiceImpl() {
        portiqueDataSrv = PhysiqueFactory.getPortiqueDataService();
    }

    @Override
    public Portique add(Portique portique) {
        Portique por = null;
        try {
            if(portique.getLecteurRFID().getId() > 0 && portique.getSalle1().getId() > 0 && portique.getSalle1().getId() != portique.getSalle2().getId() && portique.getX() >= 0 && portique.getY() >= 0){
                por = portiqueDataSrv.add(portique);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return por;
    }

    @Override
    public boolean remove(Portique portique) {
        boolean execute = false;
        try {
            if (portique.getId() > 0) {
                execute = portiqueDataSrv.remove(portique);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Portique portique) {
        boolean execute = false;
        try {
            if (portique.getId() > 0) {
                if(portique.getLecteurRFID().getId() > 0 && portique.getSalle1().getId() > 0 && portique.getSalle1().getId() != portique.getSalle2().getId() && portique.getX() >= 0 && portique.getY() >= 0){
                    execute = portiqueDataSrv.update(portique);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Portique> getAll(int debut, int parPage) {
        List<Portique> por = new ArrayList<Portique>();
        try {
            if (debut >= 0 && parPage > 0) {
                por = portiqueDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return por;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = portiqueDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Portique getById(long id) {
        Portique por = null;
        try {
            if (id > 0) {
                por = portiqueDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return por;
    }

    @Override
    public Portique getByLecteurRFID(LecteurRFID lecteur) {
        Portique por = null;
        try {
            if (lecteur.getId() > 0) {
                por = portiqueDataSrv.getByLecteurRFID(lecteur);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return por;
    }

    @Override
    public List<LecteurRFID> getListLecteurRFID(int debut, int parPage) {
        List<LecteurRFID> lecteurs = new ArrayList<LecteurRFID>();
        try {
            if (debut >= 0 && parPage > 0) {
                lecteurs = portiqueDataSrv.getListLecteurRFID(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lecteurs;
    }

    @Override
    public int getCountListLecteurRFID() {
        int count = 0;
        try {
            count = portiqueDataSrv.getCountListLecteurRFID();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Portique> getBySalle(Salle salle, int debut, int parPage) {
        List<Portique> por = new ArrayList<Portique>();
        try {
            if (salle.getId() > 0) {
                if (debut >= 0 && parPage > 0) {
                    por = portiqueDataSrv.getBySalle(salle, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return por;
    }

    @Override
    public int getCountBySalle(Salle salle) {
        int count = 0;
        try {
            if (salle.getId() > 0) {
                count = portiqueDataSrv.getCountBySalle(salle);
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
                salles = portiqueDataSrv.getListSalle(debut, parPage);
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
            count = portiqueDataSrv.getCountListSalle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
