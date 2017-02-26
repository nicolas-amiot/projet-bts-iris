package metier;

import java.util.List;

public interface TypeService {
    Type add(Type type);
    boolean remove(Type type);
    boolean update(Type type);
    List<Type> getAll(int debut, int parPage);
    int getCount();
    Type getById(long id);
    Type getByNomType(String nomType);
    List<String> getListNomType(int debut, int parPage);
    int getCountListNomType();
    Type getByNomImage(String nomImage);
    List<String> getListNomImage(int debut, int parPage);
    int getCountListNomImage();
}
