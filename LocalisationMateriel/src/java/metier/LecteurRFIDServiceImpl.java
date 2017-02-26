package metier;

import java.util.ArrayList;
import java.util.List;
import physique.LecteurRFIDDataService;
import physique.PhysiqueFactory;

public class LecteurRFIDServiceImpl implements LecteurRFIDService {

    private final LecteurRFIDDataService lecteurRFIDDataSrv;
    private final PortiqueService portiqueSrv;

    LecteurRFIDServiceImpl() {
        lecteurRFIDDataSrv = PhysiqueFactory.getLecteurRFIDDataService();
        portiqueSrv = MetierFactory.getPortiqueService();
    }

    @Override
    public LecteurRFID add(LecteurRFID lecteur) {
        LecteurRFID lec = null;
        try {
            if (!lecteur.getIp().isEmpty() && !lecteur.getModele().isEmpty()) {
                lec = lecteurRFIDDataSrv.add(lecteur);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lec;
    }

    @Override
    public boolean remove(LecteurRFID lecteur) {
        boolean execute = false;
        try {
            if (lecteur.getId() > 0) {
                Portique portique = portiqueSrv.getByLecteurRFID(lecteur);
                if(portique.getId() > 0){
                    portiqueSrv.remove(portique);
                }
                execute = lecteurRFIDDataSrv.remove(lecteur);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(LecteurRFID lecteur) {
        boolean execute = false;
        try {
            if (lecteur.getId() > 0) {
                if (!lecteur.getIp().isEmpty() && !lecteur.getModele().isEmpty()) {
                    return lecteurRFIDDataSrv.update(lecteur);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<LecteurRFID> getAll(int debut, int parPage) {
        List<LecteurRFID> lec = new ArrayList<LecteurRFID>();
        try {
            if (debut >= 0 && parPage > 0) {
                lec = lecteurRFIDDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lec;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = lecteurRFIDDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public LecteurRFID getById(long id) {
        LecteurRFID lec = null;
        try {
            if (id > 0) {
                lec = lecteurRFIDDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lec;
    }

    @Override
    public LecteurRFID getByIp(String ip) {
        LecteurRFID lec = null;
        try {
            if (!ip.isEmpty()) {
                lec = lecteurRFIDDataSrv.getByIp(ip);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lec;
    }

    @Override
    public List<String> getListIp(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = lecteurRFIDDataSrv.getListIp(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListIp() {
        int count = 0;
        try {
            count = lecteurRFIDDataSrv.getCountListIp();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<LecteurRFID> getByModele(String modele, int debut, int parPage) {
        List<LecteurRFID> lec = null;
        try {
            if (!modele.isEmpty()) {
                if (debut >= 0 && parPage > 0) {
                    lec = lecteurRFIDDataSrv.getByModele(modele, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lec;
    }

    @Override
    public int getCountByModele(String modele) {
        int count = 0;
        try {
            if (!modele.isEmpty()) {
                count = lecteurRFIDDataSrv.getCountByModele(modele);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<String> getListModele(int debut, int parPage) {
        List<String> listStr = null;
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = lecteurRFIDDataSrv.getListModele(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListModele() {
        int count = 0;
        try {
            count = lecteurRFIDDataSrv.getCountListModele();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<LecteurRFID> getByEtatOn(boolean etatOn, int debut, int parPage) {
        List<LecteurRFID> lec = new ArrayList<LecteurRFID>();
        try {
            if (debut >= 0 && parPage > 0) {
                lec = lecteurRFIDDataSrv.getByEtatOn(etatOn, debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return lec;
    }

    @Override
    public int getCountByEtatOn(boolean etatOn) {
        int count = 0;
        try {
            count = lecteurRFIDDataSrv.getCountByEtatOn(etatOn);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
