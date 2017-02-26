package metier;

import java.util.List;

public class Batiment {
    long id;
    String nomBatiment;
    List<Salle> salles;
    String plan;

    public Batiment() {
    }

    public Batiment(String nomBatiment, List<Salle> salles, String plan) {
        this.nomBatiment = nomBatiment;
        this.salles = salles;
        this.plan = plan;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getNomBatiment() {
        return nomBatiment;
    }

    public void setNomBatiment(String nomBatiment) {
        this.nomBatiment = nomBatiment;
    }

    public List<Salle> getSalles() {
        return salles;
    }

    public void setSalles(List<Salle> salles) {
        this.salles = salles;
    }

    public String getPlan() {
        return plan;
    }

    public void setPlan(String plan) {
        this.plan = plan;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 13 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 13 * hash + (this.nomBatiment != null ? this.nomBatiment.hashCode() : 0);
        hash = 13 * hash + (this.salles != null ? this.salles.hashCode() : 0);
        hash = 13 * hash + (this.plan != null ? this.plan.hashCode() : 0);
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
        final Batiment other = (Batiment) obj;
        if (this.id != other.id) {
            return false;
        }
        if ((this.nomBatiment == null) ? (other.nomBatiment != null) : !this.nomBatiment.equals(other.nomBatiment)) {
            return false;
        }
        if (this.salles != other.salles && (this.salles == null || !this.salles.equals(other.salles))) {
            return false;
        }
        if ((this.plan == null) ? (other.plan != null) : !this.plan.equals(other.plan)) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Batiment{" + "id=" + id + ", nomBatiment=" + nomBatiment + ", salles=" + salles + ", plan=" + plan + '}';
    }
    
}
