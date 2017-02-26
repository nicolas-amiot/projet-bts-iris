package metier;

import java.util.ArrayList;
import java.util.List;
import physique.PhysiqueFactory;
import physique.TypeDataService;

public class TypeServiceImpl implements TypeService {

    private final TypeDataService typeDataSrv;
    private final MaterielService materielSrv;

    TypeServiceImpl() {
        typeDataSrv = PhysiqueFactory.getTypeDataService();
        materielSrv = MetierFactory.getMaterielService();
    }

    @Override
    public Type add(Type type) {
        Type typ = null;
        try {
            if (!type.getNomType().isEmpty() && !type.getNomImage().isEmpty()) {
                typ = typeDataSrv.add(type);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return typ;
    }

    @Override
    public boolean remove(Type type) {
        boolean execute = false;
        try {
            if (type.getId() > 0) {
                List<Materiel> materiels = materielSrv.getByType(type, 0, materielSrv.getCountByType(type));
                if(materiels.isEmpty()){
                    execute = typeDataSrv.remove(type);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public boolean update(Type type) {
        boolean execute = false;
        try {
            if (type.getId() > 0) {
                if (!type.getNomType().isEmpty() && !type.getNomImage().isEmpty()) {
                    execute = typeDataSrv.update(type);
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return execute;
    }

    @Override
    public List<Type> getAll(int debut, int parPage) {
        List<Type> typ = new ArrayList<Type>();
        try {
            if (debut >= 0 && parPage > 0) {
                typ = typeDataSrv.getAll(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return typ;
    }

    @Override
    public int getCount() {
        int count = 0;
        try {
            count = typeDataSrv.getCount();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Type getById(long id) {
        Type typ = null;
        try {
            if (id > 0) {
                typ = typeDataSrv.getById(id);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return typ;
    }

    @Override
    public Type getByNomType(String nomType) {
        Type typ = null;
        try {
            if (!nomType.isEmpty()) {
                typ = typeDataSrv.getByNomType(nomType);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return typ;
    }

    @Override
    public List<String> getListNomType(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = typeDataSrv.getListNomType(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListNomType() {
        int count = 0;
        try {
            count = typeDataSrv.getCountListNomType();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }

    @Override
    public Type getByNomImage(String nomImage) {
        Type typ = null;
        try {
            if (!nomImage.isEmpty()) {
                typ = typeDataSrv.getByNomImage(nomImage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return typ;
    }

    @Override
    public List<String> getListNomImage(int debut, int parPage) {
        List<String> listStr = new ArrayList<String>();
        try {
            if (debut >= 0 && parPage > 0) {
                listStr = typeDataSrv.getListNomImage(debut, parPage);
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return listStr;
    }

    @Override
    public int getCountListNomImage() {
        int count = 0;
        try {
            count = typeDataSrv.getCountListNomImage();
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        return count;
    }
}
