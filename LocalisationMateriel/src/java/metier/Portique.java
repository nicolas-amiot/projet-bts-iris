package metier;

public class Portique {
    long id;
    float x;
    float y;
    Salle salle1;
    Salle salle2;
    LecteurRFID lecteur;

    public Portique() {
    }

    public Portique(float x, float y, Salle salle1, Salle salle2, LecteurRFID lecteur) {
        this.x = x;
        this.y = y;
        this.salle1 = salle1;
        this.salle2 = salle2;
        this.lecteur = lecteur;
    }
    
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }
    
    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public Salle getSalle1() {
        return salle1;
    }

    public void setSalle1(Salle salle1) {
        this.salle1 = salle1;
    }

    public Salle getSalle2() {
        return salle2;
    }

    public void setSalle2(Salle salle2) {
        this.salle2 = salle2;
    }

    public LecteurRFID getLecteurRFID() {
        return lecteur;
    }

    public void setLecteurRFID(LecteurRFID lecteur) {
        this.lecteur = lecteur;
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 17 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 17 * hash + Float.floatToIntBits(this.x);
        hash = 17 * hash + Float.floatToIntBits(this.y);
        hash = 17 * hash + (this.salle1 != null ? this.salle1.hashCode() : 0);
        hash = 17 * hash + (this.salle2 != null ? this.salle2.hashCode() : 0);
        hash = 17 * hash + (this.lecteur != null ? this.lecteur.hashCode() : 0);
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
        final Portique other = (Portique) obj;
        if (this.id != other.id) {
            return false;
        }
        if (Float.floatToIntBits(this.x) != Float.floatToIntBits(other.x)) {
            return false;
        }
        if (Float.floatToIntBits(this.y) != Float.floatToIntBits(other.y)) {
            return false;
        }
        if (this.salle1 != other.salle1 && (this.salle1 == null || !this.salle1.equals(other.salle1))) {
            return false;
        }
        if (this.salle2 != other.salle2 && (this.salle2 == null || !this.salle2.equals(other.salle2))) {
            return false;
        }
        if (this.lecteur != other.lecteur && (this.lecteur == null || !this.lecteur.equals(other.lecteur))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Portique{" + "id=" + id + ", x=" + x + ", y=" + y + ", salle1=" + salle1 + ", salle2=" + salle2 + ", lecteur=" + lecteur + '}';
    }

}
