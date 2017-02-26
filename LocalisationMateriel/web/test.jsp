<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Test</title>
    </head>
    <body>
        <form method="POST" action="Test">
            <fieldset>
                <label for="id">Id </label>
                <input type="text" id="id" name="id" value=""/><br/>
                <br />
                <label for="idBadge">IdBadge </label>
                <input type="text" id="idBadge" name="idBadge" value=""/><br/>
                <br />
                <label for="dateControle">Date de controle </label>
                <input type="text" id="dateControle" name="dateControle" value=""/><br/>
                <br />
                <label for="dateControle">Prochaine date de controle </label>
                <input type="text" id="newDateControle" name="newDateControle" value=""/><br/>
                <br />
                <label for="nomMateriel">Nom de materiel </label>
                <input type="text" id="nomMateriel" name="nomMateriel" value=""/><br/>
                <br />
                <label for="nomType">Nom du type </label>
                <input type="text" id="nomType" name="nomType" value=""/><br/>
                <br />
                <label for="page">Page </label>
                <input type="number" id="page" name="page" value=""/><br/>
                <br />
                <label for="parPage">Élément par page </label>
                <input type="number" id="parPage" name="parPage" value=""/><br/>
                <br />
                <label for="avant">Obtenir les date précédent: </label>
                <input type="checkbox" id="avant" name="avant" value="avant"/><br/>
                <br />
                <input type="radio" name="choixMateriel" value="add">Add
                <input type="radio" name="choixMateriel" value="remove">Remove
                <input type="radio" name="choixMateriel" value="update">Update
                <input type="radio" name="choixMateriel" value="getById">GetById
                <br /><br />
                <input type="radio" name="choixMateriel" value="getAll">GetAll
                <input type="radio" name="choixMateriel" value="getCount">GetCount
                <br /><br />
                <input type="radio" name="choixMateriel" value="getBiIdBadge">GetBiIdBadge
                <input type="radio" name="choixMateriel" value="getListIdBadge">GetListIdBadge
                <input type="radio" name="choixMateriel" value="getCountListIdBadge">GetCountListIdBadge
                <br /><br />
                <input type="radio" name="choixMateriel" value="getByDateControle">GetByDateControle
                <input type="radio" name="choixMateriel" value="getCountByDateControle">GetCountByDateControle
                <input type="radio" name="choixMateriel" value="getListDateControle">GetListDateControle
                <input type="radio" name="choixMateriel" value="getCountListDateControle">GetCountListDateControle
                <br /><br />
                <input type="radio" name="choixMateriel" value="getByNewDateControle">GetByNewDateControle
                <input type="radio" name="choixMateriel" value="getCountByNewDateControle">GetCountByNewDateControle
                <input type="radio" name="choixMateriel" value="getListNewDateControle">GetListNewDateControle
                <input type="radio" name="choixMateriel" value="getCountListNewDateControle">GetCountListNewDateControle
                <br /><br />
                <input type="radio" name="choixMateriel" value="getByPeriode">GetByPeriode
                <input type="radio" name="choixMateriel" value="getCountByPeriode">GetCountByPeriode
                <br /><br />
                <input type="radio" name="choixMateriel" value="getByNomMateriel">GetByNomMateriel
                <input type="radio" name="choixMateriel" value="getCountByNomMateriel">GetCountByNomMateriel
                <input type="radio" name="choixMateriel" value="getListNomMateriel">GetListNomMateriel
                <input type="radio" name="choixMateriel" value="getCountListNomMateriel">GetCountListNomMateriel
                <br /><br />
                <input type="radio" name="choixMateriel" value="getByType">GetByType
                <input type="radio" name="choixMateriel" value="getCountByType">GetCountByType
                <input type="radio" name="choixMateriel" value="getListType">GetListType
                <input type="radio" name="choixMateriel" value="getCountListType">GetCountListType
                <br /><br />
                <input type="submit" name="valider" value="Valider">
            </fieldset>
        </form>
        <c:forEach var="object" items="${list}">
            ${object}<br />
        </c:forEach>
    </body>
</html>
