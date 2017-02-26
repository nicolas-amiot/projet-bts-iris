package metier;

public class Type {
    long id;
    String nomType;
    String nomImage;

    public Type(){
        
    }
    
    public Type(String nomType, String nomImage) {
        this.nomType = nomType;
        this.nomImage = nomImage;
    }

    public long getId() {
        return id;
    }

    public String getNomType() {
        return nomType;
    }

    public String getNomImage() {
        return nomImage;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setNomType(String nomType) {
        this.nomType = nomType;
    }

    public void setNomImage(String nomImage) {
        this.nomImage = nomImage;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 71 * hash + (int) (this.id ^ (this.id >>> 32));
        hash = 71 * hash + (this.nomType != null ? this.nomType.hashCode() : 0);
        hash = 71 * hash + (this.nomImage != null ? this.nomImage.hashCode() : 0);
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
        final Type other = (Type) obj;
        if (this.id != other.id) {
            return false;
        }
        if ((this.nomType == null) ? (other.nomType != null) : !this.nomType.equals(other.nomType)) {
            return false;
        }
        if ((this.nomImage == null) ? (other.nomImage != null) : !this.nomImage.equals(other.nomImage)) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Type{" + "id=" + id + ", nomType=" + nomType + ", nomImage=" + nomImage + '}';
    }
}
