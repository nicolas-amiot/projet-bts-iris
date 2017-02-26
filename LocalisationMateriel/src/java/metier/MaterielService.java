package metier;

import java.util.Date;
import java.util.List;

// Ceci est une interface : aucun attribut, que des méthode abstraites (sans corps) 
// => c'est un pur concept qui ne peut être instancié (on ne pas créer d'objet MaterielService, c'est a dire que new MaterielService est impossible)
// On doit faire une classe concrète qui implémente le concept !!!
public interface MaterielService {
    // Les interface de service des classe entités offre ce que l'on appelle les service CRUD :
    // service qui permettent l'ajout, la supression, la modifications, la récupération d'information dans un contexte de persistance : ICI ON GERE L'ASPECT REGLES METIERS UNIQUEMENT
    public Materiel add(Materiel materiel);
    public boolean remove(Materiel materiel);
    public boolean update(Materiel materiel);
    List<Materiel> getAll(int debut, int parPage);
    int getCount();
    Materiel getById(long id);
    Materiel getByIdBadge(String idBadge);
    List<String> getListIdBadge(int debut, int parPage);
    int getCountListIdBadge();
    List<Materiel> getByDateControle(Date dateControle, int debut, int parPage);
    int getCountByDateControle(Date dateControle);
    List<Date> getListDateControle(int debut, int parPage);
    int getCountListDateControle();
    List<Materiel> getByNewDateControle(Date newDateControle, int debut, int parPage);
    int getCountByNewDateControle(Date newDateControle);
    List<Date> getListNewDateControle(int debut, int parPage);
    int getCountListNewDateControle();
    List<Materiel> getByPeriode(Date date, boolean avant, int debut, int parPage);
    int getCountByPeriode(Date date, boolean avant);
    List<Materiel> getByType(Type type, int debut, int parPage);
    int getCountByType(Type type);
    List<Type>getListType(int debut, int parPage);
    int getCountListType();
    List<Materiel>getByNomMateriel(String nomMateriel, int debut, int parPage);
    int getCountByNomMateriel(String nomMateriel);
    List<String>getListNomMateriel(int debut, int parPage);
    int getCountListNomMateriel();
}
