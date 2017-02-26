package metier;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import physique.PhysiqueFactory;
import physique.MaterielDataService;

// classe qui implémente les concept de l'interface UtilisateurService
public class MaterielServiceImpl implements MaterielService {
    // Une Liste dynamique est une collection comme les tableaux, mais beaucoup plus souple d'utilisation
    // celle-ci ne peut contenir que des objet de nature Materiel : issue de cette classe ou d'un classe dérivée (héritage / extends)

    private final MaterielDataService materielDataSrv;
    private final LocalisationService localisationSrv;

    // Le constructeur qui initialise l'objet materiel (création d'une liste mais pour le moment vide)
    MaterielServiceImpl() {
        materielDataSrv = PhysiqueFactory.getMaterielDataService();
        localisationSrv = MetierFactory.getLocalisationService();
    }

    @Override
    public Materiel add(Materiel materiel) {
        Materiel mat = null;
        try {
            if (!materiel.getIdBadge().isEmpty() && !materiel.getNomMateriel().isEmpty() && materiel.getDateControle() != null && materiel.getNewDateControle() != null && materiel.getType().getId() > 0) {
                mat = materielDataSrv.add(materiel);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public boolean remove(Materiel materiel) {
        boolean execute = false;
        try {
            if (materiel.getId() > 0) {
                Localisation localisation = localisationSrv.getByMateriel(materiel);
                if(localisation.getId() > 0){
                    localisationSrv.remove(localisation);
                }
                execute = materielDataSrv.remove(materiel);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Materiel materiel) {
        boolean execute = false;
        try {
            if (materiel.getId() > 0) {
                if (!materiel.getIdBadge().isEmpty() && !materiel.getNomMateriel().isEmpty() && materiel.getDateControle() != null && materiel.getNewDateControle() != null && materiel.getType().getId() > 0) {
                    execute = materielDataSrv.update(materiel);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Materiel> getAll(int debut, int parPage) {
        List<Materiel> mat = new ArrayList<Materiel>();
        try {
            if (debut >= 0 && parPage > 0) {
                mat = materielDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = materielDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Materiel getById(long id) {
        Materiel mat = null;
        try {
            if (id > 0) {
                mat = materielDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public Materiel getByIdBadge(String idBadge) {
        Materiel mat = null;
        try {
            if (!idBadge.isEmpty()) {
                mat = materielDataSrv.getByIdBadge(idBadge);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public List<String> getListIdBadge(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = materielDataSrv.getListIdBadge(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListIdBadge() {
        int count = 0;
        try {
            count = materielDataSrv.getCountListIdBadge();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Materiel> getByDateControle(Date dateControle, int debut, int parPage) {
        List<Materiel> mat = null;
        try {
            if (dateControle != null) {
                if (debut >= 0 && parPage > 0) {
                    mat = materielDataSrv.getByDateControle(dateControle, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public int getCountByDateControle(Date dateControle) {
        int count = 0;
        try {
            if (dateControle != null) {
                count = materielDataSrv.getCountByDateControle(dateControle);

            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Date> getListDateControle(int debut, int parPage) {
        List<Date> listDate = new ArrayList<Date>();
        try {
            if (debut >= 0 && parPage > 0) {
                listDate = materielDataSrv.getListDateControle(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listDate;
    }

    @Override
    public int getCountListDateControle() {
        int count = 0;
        try {
            count = materielDataSrv.getCountListDateControle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }
    
    @Override
    public List<Materiel> getByNewDateControle(Date newDateControle, int debut, int parPage) {
        List<Materiel> mat = null;
        try {
            if (newDateControle != null) {
                if (debut >= 0 && parPage > 0) {
                    mat = materielDataSrv.getByNewDateControle(newDateControle, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public int getCountByNewDateControle(Date newDateControle) {
        int count = 0;
        try {
            if (newDateControle != null) {
                count = materielDataSrv.getCountByNewDateControle(newDateControle);

            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Date> getListNewDateControle(int debut, int parPage) {
        List<Date> listDate = new ArrayList<Date>();
        try {
            if (debut >= 0 && parPage > 0) {
                listDate = materielDataSrv.getListNewDateControle(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listDate;
    }

    @Override
    public int getCountListNewDateControle() {
        int count = 0;
        try {
            count = materielDataSrv.getCountListNewDateControle();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Materiel> getByPeriode(Date date, boolean avant, int debut, int parPage) {
        List<Materiel> mat = null;
        try {
            if (date != null) {
                if (debut >= 0 && parPage > 0) {
                    mat = materielDataSrv.getByPeriode(date, avant, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public int getCountByPeriode(Date date, boolean avant) {
        int count = 0;
        try {
            if (date != null) {
                count = materielDataSrv.getCountByPeriode(date, avant);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Materiel> getByType(Type type, int debut, int parPage) {
        List<Materiel> mat = new ArrayList<Materiel>();
        try {
            if (type.getId() > 0) {
                if (debut >= 0 && parPage > 0) {
                    mat = materielDataSrv.getByType(type, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public int getCountByType(Type type) {
        int count = 0;
        try {
            if (type.getId() > 0) {
                count = materielDataSrv.getCountByType(type);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Type> getListType(int debut, int parPage) {
        List<Type> types = new ArrayList<Type>();
        try {
            if (debut >= 0 && parPage > 0) {
                types = materielDataSrv.getListType(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return types;
    }

    @Override
    public int getCountListType() {
        int count = 0;
        try {
            count = materielDataSrv.getCountListType();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<Materiel> getByNomMateriel(String nomMateriel, int debut, int parPage) {
        List<Materiel> mat = new ArrayList<Materiel>();
        try {
            if (!nomMateriel.isEmpty()) {
                if (debut >= 0 && parPage > 0) {
                    mat = materielDataSrv.getByNomMateriel(nomMateriel, debut, parPage);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return mat;
    }

    @Override
    public int getCountByNomMateriel(String nomMateriel) {
        int count = 0;
        try {
            if (!nomMateriel.isEmpty()) {
                count = materielDataSrv.getCountByNomMateriel(nomMateriel);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public List<String> getListNomMateriel(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = materielDataSrv.getListNomMateriel(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListNomMateriel() {
        int count = 0;
        try {
            return materielDataSrv.getCountListNomMateriel();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

}
