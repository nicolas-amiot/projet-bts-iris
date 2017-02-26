package metier;

public class Salle {
    long id;
    float x_ini;
    float y_ini;
    float x_fin;
    float y_fin;
    int numSalle;
    String nomSalle;
    String nomAtelier;

    public Salle() {
    }

    public Salle(float x_ini, float y_ini, float x_fin, float y_fin, int numSalle, String nomSalle, String nomAtelier) {
        this.x_ini = x_ini;
        this.y_ini = y_ini;
        this.x_fin = x_fin;
        this.y_fin = y_fin;
        this.numSalle = numSalle;
        this.nomSalle = nomSalle;
        this.nomAtelier = nomAtelier;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public float getX_ini() {
        return x_ini;
    }

    public void setX_ini(float x_ini) {
        this.x_ini = x_ini;
    }

    public float getY_ini() {
        return y_ini;
    }

    public void setY_ini(float y_ini) {
        this.y_ini = y_ini;
    }

    public float getX_fin() {
        return x_fin;
    }

    public void setX_fin(float x_fin) {
        this.x_fin = x_fin;
    }

    public float getY_fin() {
        return y_fin;
    }

    public void setY_fin(float y_fin) {
        this.y_fin = y_fin;
    }

    public int getNumSalle() {
        return numSalle;
    }

    public void setNumSalle(int numSalle) {
        this.numSalle = numSalle;
    }

    public String getNomSalle() {
        return nomSalle;
    }

    public void setNomSalle(String nomSalle) {
        this.nomSalle = nomSalle;
    }

    public String getNomAtelier() {
        return nomAtelier;
    }

    public void setNomAtelier(String nomAtelier) {
        this.nomAtelier = nomAtelier;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 67 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 67 * hash + Float.floatToIntBits(this.x_ini);
        hash = 67 * hash + Float.floatToIntBits(this.y_ini);
        hash = 67 * hash + Float.floatToIntBits(this.x_fin);
        hash = 67 * hash + Float.floatToIntBits(this.y_fin);
        hash = 67 * hash + this.numSalle;
        hash = 67 * hash + (this.nomSalle != null ? this.nomSalle.hashCode() : 0);
        hash = 67 * hash + (this.nomAtelier != null ? this.nomAtelier.hashCode() : 0);
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
        final Salle other = (Salle) obj;
        if (this.id != other.id) {
            return false;
        }
        if (Float.floatToIntBits(this.x_ini) != Float.floatToIntBits(other.x_ini)) {
            return false;
        }
        if (Float.floatToIntBits(this.y_ini) != Float.floatToIntBits(other.y_ini)) {
            return false;
        }
        if (Float.floatToIntBits(this.x_fin) != Float.floatToIntBits(other.x_fin)) {
            return false;
        }
        if (Float.floatToIntBits(this.y_fin) != Float.floatToIntBits(other.y_fin)) {
            return false;
        }
        if (this.numSalle != other.numSalle) {
            return false;
        }
        if ((this.nomSalle == null) ? (other.nomSalle != null) : !this.nomSalle.equals(other.nomSalle)) {
            return false;
        }
        if ((this.nomAtelier == null) ? (other.nomAtelier != null) : !this.nomAtelier.equals(other.nomAtelier)) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Salle{" + "id=" + id + ", x_ini=" + x_ini + ", y_ini=" + y_ini + ", x_fin=" + x_fin + ", y_fin=" + y_fin + ", numSalle=" + numSalle + ", nomSalle=" + nomSalle + ", nomAtelier=" + nomAtelier + '}';
    }
    
}
