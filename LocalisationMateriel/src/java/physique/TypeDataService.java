package physique;

import java.util.List;
import metier.Type;


public interface TypeDataService {
    Type add(Type type) throws Exception;
    boolean remove(Type type) throws Exception;
    boolean update(Type type) throws Exception;
    List<Type> getAll(int debut, int parPage) throws Exception;
    int getCount() throws Exception;
    Type getById(long id) throws Exception;
    Type getByNomType(String nomType) throws Exception;
    List<String> getListNomType(int debut, int parPage) throws Exception;
    int getCountListNomType() throws Exception;
    Type getByNomImage(String nomImage) throws Exception;
    List<String> getListNomImage(int debut, int parPage) throws Exception;
    int getCountListNomImage() throws Exception;
}
