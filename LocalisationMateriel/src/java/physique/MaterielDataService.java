package physique;

import java.util.Date;
import java.util.List;
import metier.Materiel;
import metier.Type;

public interface MaterielDataService {
    // Les interface de service des classe entités offre ce que l'on appelle les service CRUD :
    // service qui permettent l'ajout, la supression, la modifications, la récupération d'information dans un contexte de persistance : ICI ON GERE L'ASPECT PERSISTANCE UNIQUEMENT
    public Materiel add(Materiel materiel) throws Exception;
    public boolean remove(Materiel materiel) throws Exception;
    public boolean update(Materiel materiel) throws Exception;
    List<Materiel> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Materiel getById(long id) throws Exception;
    Materiel getByIdBadge(String idBadge) throws Exception;
    List<String> getListIdBadge(int debut, int parPage) throws Exception;
    int getCountListIdBadge() throws Exception;
    List<Materiel> getByDateControle(Date dateControle, int debut, int parPage) throws Exception;
    int getCountByDateControle(Date dateControle) throws Exception;
    List<Date> getListDateControle(int debut, int parPage) throws Exception;
    int getCountListDateControle() throws Exception;
    List<Materiel> getByNewDateControle(Date newDateControle, int debut, int parPage) throws Exception;
    int getCountByNewDateControle(Date newDateControle) throws Exception;
    List<Date> getListNewDateControle(int debut, int parPage) throws Exception;
    int getCountListNewDateControle() throws Exception;
    List<Materiel> getByPeriode(Date date, boolean avant, int debut, int parPage) throws Exception;
    int getCountByPeriode(Date date, boolean avant) throws Exception;
    List<Materiel> getByType(Type type, int debut, int parPage) throws Exception;
    int getCountByType(Type type) throws Exception;
    List<Type>getListType(int debut, int parPage) throws Exception;
    int getCountListType() throws Exception;
    List<Materiel>getByNomMateriel(String nomMateriel, int debut, int parPage) throws Exception;
    int getCountByNomMateriel(String nomMateriel) throws Exception;
    List<String>getListNomMateriel(int debut, int parPage) throws Exception;
    int getCountListNomMateriel() throws Exception;
}