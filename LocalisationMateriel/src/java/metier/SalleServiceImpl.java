package metier;

import java.util.ArrayList;
import java.util.List;
import physique.PhysiqueFactory;
import physique.SalleDataService;

public class SalleServiceImpl implements SalleService {

    private final SalleDataService salleDataSrv;
    private final LocalisationService localisationSrv;
    private final PortiqueService portiqueSrv;

    SalleServiceImpl() {
        salleDataSrv = PhysiqueFactory.getSalleDataService();
        localisationSrv = MetierFactory.getLocalisationService();
        portiqueSrv = MetierFactory.getPortiqueService();
    }

    @Override
    public Salle add(Salle salle) {
        Salle sal = null;
        try {
            if (salle.getNumSalle() > 0 && salle.getX_fin() >= 0 && salle.getX_ini() >= 0 && salle.getY_fin() >= 0 && salle.getY_ini() >= 0) {
                sal = salleDataSrv.add(salle);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return sal;
    }

    @Override
    public boolean remove(Salle salle) {
        boolean execute = false;
        try {
            if (salle.getId() > 0) {
                List<Localisation> localisations = localisationSrv.getBySalle(salle, 0, localisationSrv.getCountBySalle(salle));
                for (Localisation localisation : localisations) {
                    localisationSrv.remove(localisation);
                }
                List<Portique> portiques = portiqueSrv.getBySalle(salle, 0, portiqueSrv.getCountBySalle(salle));
                for (Portique portique : portiques) {
                    if(portique.getSalle1().getId() > 0 && portique.getSalle2().getId() <= 0){
                        portiqueSrv.remove(portique);
                    } else { // Le portique contient 2 salles
                        if(salle.getId() == portique.getSalle1().getId()){
                            portique.setSalle1(portique.getSalle2());
                            portique.setSalle2(null);
                            portiqueSrv.update(portique);
                        }
                    }
                }
                execute = salleDataSrv.remove(salle);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Salle salle) {
        boolean execute = false;
        try {
            if (salle.getId() > 0) {
                if (salle.getNumSalle() > 0 && salle.getX_fin() >= 0 && salle.getX_ini() >= 0 && salle.getY_fin() >= 0 && salle.getY_ini() >= 0) {
                    execute = salleDataSrv.update(salle);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Salle> getAll(int debut, int parPage) {
        List<Salle> sal = new ArrayList<Salle>();
        try {
            if (debut >= 0 && parPage > 0) {
                sal = salleDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return sal;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = salleDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Salle getById(long id) {
        Salle sal = null;
        try {
            if (id > 0) {
                sal = salleDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return sal;
    }

    @Override
    public List<Salle> getByNomSalle(String nomSalle, int debut, int parPage) {
        List<Salle> sal = new ArrayList<Salle>();
        try {
            if (!nomSalle.isEmpty()) {
                if (debut >= 0 && parPage > 0) {
                    sal = salleDataSrv.getByNomSalle(nomSalle, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return sal;
    }

    @Override
    public int getCountByNomSalle(String nomSalle) {
        int count = 0;
        try {
            if (!nomSalle.isEmpty()) {
                count = salleDataSrv.getCountByNomSalle(nomSalle);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<String> getListNomSalle(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = salleDataSrv.getListNomSalle(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListNomSalle() {
        int count = 0;
        try {
            count = salleDataSrv.getCountListNomSalle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Salle getByNumSalle(int numSalle) {
        Salle sal = null;
        try {
            if (numSalle > 0) {
                sal = salleDataSrv.getByNumSalle(numSalle);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return sal;
    }

    @Override
    public List<Integer> getListNumSalle(int debut, int parPage) {
        List<Integer> listNumSalle = new ArrayList<Integer>();
        try {
            if (debut >= 0 && parPage > 0) {
                listNumSalle = salleDataSrv.getListNumSalle(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listNumSalle;
    }

    @Override
    public int getCountListNumSalle() {
        int count = 0;
        try {
            count = salleDataSrv.getCountListNumSalle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Salle> getByNomAtelier(String nomAtelier, int debut, int parPage) {
        List<Salle> sal = new ArrayList<Salle>();
        try {
            if (!nomAtelier.isEmpty()) {
                if (debut >= 0 && parPage > 0) {
                    sal = salleDataSrv.getByNomAtelier(nomAtelier, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return sal;
    }

    @Override
    public int getCountByNomAtelier(String nomAtelier) {
        int count = 0;
        try {
            if (!nomAtelier.isEmpty()) {
                count = salleDataSrv.getCountByNomAtelier(nomAtelier);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<String> getListNomAtelier(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = salleDataSrv.getListNomAtelier(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListNomAtelier() {
        int count = 0;
        try {
            count = salleDataSrv.getCountListNomAtelier();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
