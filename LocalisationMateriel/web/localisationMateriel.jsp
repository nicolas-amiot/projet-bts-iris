<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" href="style.css" type="text/css">
        <title>Test</title>
    </head>
    <body>
        <c:choose>
            <c:when test="${!empty materiels}">
                <fmt:formatDate pattern="dd/MM/yyyy" value="${now}" var="dateNow" />
                <c:set var="index" value="0" />
                <div class="divTable">
                    <table>
                        <tr>
                            <td colspan="4">Information sur l'emplacement</td>
                            <td colspan="4">Information sur le materiel</td>
                        </tr>
                        <tr>
                            <td>Nom du batiment</td>
                            <td>Numéro de salle</td>
                            <td>Nom de la salle</td>
                            <td>Nom de l'atelier</td>
                            <td>N° du matériel</td>
                            <td>Période de validation</td>
                            <td>Nom du matériel</td>
                            <td>Type de matériel</td>
                        </tr>
                        <c:forEach var="materiel" items="${materiels}">
                            <tr>
                                <td>${batiments[index].nomBatiment}</td>
                                <td>${salles[index].numSalle}</td>
                                <td>${salles[index].nomSalle}</td>
                                <td>${salles[index].nomAtelier}</td>
                                <td>${materiel.idBadge}</td>
                                <fmt:formatDate pattern="dd/MM/yyyy" value="${materiel.dateControle}" var="dateControle" />
                                <fmt:formatDate pattern="dd/MM/yyyy" value="${materiel.newDateControle}" var="newDateControle" />
                                <td>
                                    <c:choose>
                                        <c:when test="${materiel.newDateControle <= now}">
                                            <span class="dateIncorrecte">du ${dateControle}<br/>au ${newDateControle}</span>
                                        </c:when>
                                        <c:otherwise>
                                            du ${dateControle}<br/>au ${newDateControle}
                                        </c:otherwise>
                                    </c:choose>
                                </td>
                                <td>${materiel.nomMateriel}</td>
                                <td>${materiel.type.nomType}</td>
                            </tr>
                            <c:set var="index" value="${index + 1}" />
                        </c:forEach>
                    </table>
                </div>
            </c:when>
            <c:otherwise>
                <span class="margin">Aucun résultat ne correspond à votre recherche</span>
            </c:otherwise>
        </c:choose>
    </body>
</html>
