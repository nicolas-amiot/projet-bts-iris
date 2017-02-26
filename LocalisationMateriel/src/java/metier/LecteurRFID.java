package metier;

public class LecteurRFID {
    long id;
    String ip;
    String modele;
    boolean etatOn;

    public LecteurRFID() {
    }

    public LecteurRFID(String ip, String modele, boolean etatOn) {
        this.ip = ip;
        this.modele = modele;
        this.etatOn = etatOn;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getModele() {
        return modele;
    }

    public void setModele(String modele) {
        this.modele = modele;
    }

    public boolean getEtatOn() {
        return etatOn;
    }

    public void setEtatOn(boolean etatOn) {
        this.etatOn = etatOn;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 79 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 79 * hash + (this.ip != null ? this.ip.hashCode() : 0);
        hash = 79 * hash + (this.modele != null ? this.modele.hashCode() : 0);
        hash = 79 * hash + (this.etatOn ? 1 : 0);
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
        final LecteurRFID other = (LecteurRFID) obj;
        if (this.id != other.id) {
            return false;
        }
        if ((this.ip == null) ? (other.ip != null) : !this.ip.equals(other.ip)) {
            return false;
        }
        if ((this.modele == null) ? (other.modele != null) : !this.modele.equals(other.modele)) {
            return false;
        }
        if (this.etatOn != other.etatOn) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "LecteurRFID{" + "id=" + id + ", ip=" + ip + ", modele=" + modele + ", etatOn=" + etatOn + '}';
    }
    
}
