package metier;

public class Localisation {
    long id;
    Materiel materiel;
    Salle salle;
    boolean sortie;

    public Localisation() {
    }

    public Localisation(Materiel materiel, Salle salle, boolean sortie) {
        this.materiel = materiel;
        this.salle = salle;
        this.sortie = sortie;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public Materiel getMateriel() {
        return materiel;
    }

    public void setMateriel(Materiel materiel) {
        this.materiel = materiel;
    }

    public Salle getSalle() {
        return salle;
    }

    public void setSalle(Salle salle) {
        this.salle = salle;
    }

    public boolean getSortie() {
        return sortie;
    }

    public void setSortie(boolean sortie) {
        this.sortie = sortie;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 67 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 67 * hash + (this.materiel != null ? this.materiel.hashCode() : 0);
        hash = 67 * hash + (this.salle != null ? this.salle.hashCode() : 0);
        hash = 67 * hash + (this.sortie ? 1 : 0);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Localisation other = (Localisation) obj;
        if (this.id != other.id) {
            return false;
        }
        if (this.materiel != other.materiel && (this.materiel == null || !this.materiel.equals(other.materiel))) {
            return false;
        }
        if (this.salle != other.salle && (this.salle == null || !this.salle.equals(other.salle))) {
            return false;
        }
        if (this.sortie != other.sortie) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Localisation{" + "id=" + id + ", materiel=" + materiel + ", salle=" + salle + ", sortie=" + sortie + '}';
    }
    
}
