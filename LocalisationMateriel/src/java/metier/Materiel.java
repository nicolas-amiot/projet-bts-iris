package metier;

import java.util.Date;

// Definition de la classe Materiel : celle-ci est de type entitée,
// elle ne contient que des données et les méthodes d'accès à celles-ci, pas de services
public class Materiel {

    // LES ATTRIBUTS : représente l'état instantané d'un objet issue de cette classe,
    // ils sont stockés dans le TAS
    // certains sont directement les valeurs (types primitifs)
    private long id;
    // d'autres sont des référence à d'autres objet situés dans le TAS
    private String idBadge;
    private Date dateControle;
    private Date newDateControle;
    private String nomMateriel;
    private Type type;

    // LES METHODES : représente l'ensemble des services (ou comportement) ofert par 
    //                les objets qui seront issue de cette classe    
    // LE (ou les) CONSTRUCTEUR : permettent d'initialiser l'objet (états initial des attributs)
    public Materiel() { // CONSTRUCTEUR par défault
    }

    public Materiel(String idBadge, Date dateControle, Date newDateControle, String nomMateriel, Type type) {
        // ici on affecte à l'attribut (this.XX) la valeur du paramètre (XX) passé en argument
        this.idBadge = idBadge;
        this.dateControle = dateControle;
        this.newDateControle = newDateControle;
        this.nomMateriel = nomMateriel;
        this.type = type;
    }

    // LES ASSECEURS (getXX isXX): permettent de récupérer la valeur d'un 
    //                             attribut depuis l'extérieur de la classe
    
    public long getId() {
        return this.id;
    }

    public String getIdBadge() {
        return idBadge;
    }

    public Date getDateControle() {
        return dateControle;
    }
    
    public Date getNewDateControle() {
        return newDateControle;
    }

    public String getNomMateriel() {
        return nomMateriel;
    }

    public Type getType() {
        return type;
    }

    // LES MUTATEURS (setXX) : permettent de changer la valeur d'un attribut 
    // depuis l'extérieur, tout en pouvant le cas échéant faire des vérifications
    
    public void setId(long id) {
        this.id = id;
    }

    public void setIdBadge(String idBadge) {
        this.idBadge = idBadge;
    }

    public void setDateControle(Date dateControle) {
        this.dateControle = dateControle;
    }
    
    public void setNewDateControle(Date newDateControle) {
        this.newDateControle = newDateControle;
    }

    public void setNomMateriel(String nomMateriel) {
        this.nomMateriel = nomMateriel;
    }

    public void setType(Type type) {
        this.type = type;
    }

    // METHODE equals : permet de savoir si deux objet sont de même nature (o instanceof Utilisateur)
    //                  et s'ils sont dans le même états via la vérification de leurs hascode (o.hashCode() == this.hashCode())
    
    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Materiel other = (Materiel) obj;
        if (this.id != other.id) {
            return false;
        }
        if ((this.idBadge == null) ? (other.idBadge != null) : !this.idBadge.equals(other.idBadge)) {
            return false;
        }
        if (this.dateControle != other.dateControle && (this.dateControle == null || !this.dateControle.equals(other.dateControle))) {
            return false;
        }
        if (this.newDateControle != other.newDateControle && (this.newDateControle == null || !this.newDateControle.equals(other.newDateControle))) {
            return false;
        }
        if ((this.nomMateriel == null) ? (other.nomMateriel != null) : !this.nomMateriel.equals(other.nomMateriel)) {
            return false;
        }
        if (this.type != other.type && (this.type == null || !this.type.equals(other.type))) {
            return false;
        }
        return true;
    }

    // METHODE hashCode : permet de calculer l'empreinte numérique caractéristique de l'état d'un objet 
    //                    avec une selection d'attributs dits caractéristiques
    
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 97 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 97 * hash + (this.idBadge != null ? this.idBadge.hashCode() : 0);
        hash = 97 * hash + (this.dateControle != null ? this.dateControle.hashCode() : 0);
        hash = 97 * hash + (this.newDateControle != null ? this.newDateControle.hashCode() : 0);
        hash = 97 * hash + (this.nomMateriel != null ? this.nomMateriel.hashCode() : 0);
        hash = 97 * hash + (this.type != null ? this.type.hashCode() : 0);
        return hash;
    }

    // METHODE toString : permet de récupérer une chaine de caractère (objet de classe String) 
    //                    qui représente l'états actuel de l'objet sur lequels on appelle la méthode
    
    @Override
    public String toString() {
        return "Materiel{" + "id=" + id + ", idBadge=" + idBadge + ", dateControle=" + dateControle + ", newDateControle=" + newDateControle + ", nomMateriel=" + nomMateriel + ", type=" + type + '}';
    }

}
