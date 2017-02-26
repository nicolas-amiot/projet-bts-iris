<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script src="function.js" type="text/javascript"></script>
        <link rel="stylesheet" href="style.css" type="text/css">
        <title>Recherche de materiels</title>
    </head>
    <body onload="AjaxListeDeroulanteMateriel();">
        <c:choose>
            <c:when test="${attribut == 'controleAFaire' || attribut == 'idBadge' || attribut == 'dateControle' || attribut == 'nomMateriel' || attribut == 'nomType'}">
                <form method="GET" action="LocalisationMateriel" class="formMateriel" autocomplete="off"> <!-- autocmplete permet de désactiver la sugestion de saisie automatique d'un champ -->
                    <div class="layout">
                        <c:choose>
                            <c:when test="${attribut == 'controleAFaire'}">
                                Contrôles à effectuer dans les
                                <input type="number" name="recherche" id="recherche" min="0" value="0" onblur="NombrePositif();" onkeypress="return RegexNombrePositif(event)">
                                <div class="divControle">
                                    prochains jours à partir d'aujourd'hui.
                                </div>
                                </c:when>
                                <c:when test="${attribut == 'idBadge'}">
                                <label for="recherche">
                                    N° du matériel :&nbsp;
                                    <input type="text" name="recherche" id="recherche">
                                </label>
                                <c:set var="nomFonction" value="TransferTextToText();"/>
                            </c:when>
                            <c:when test="${attribut == 'dateControle'}">
                                <label for="recherche">
                                    Date de controle :&nbsp;
                                    <input type="date" name="recherche" id="recherche" placeholder="jj/mm/aaaa">
                                </label>
                                <c:set var="nomFonction" value="TransferTextToFrDateFormat('/');"/>
                            </c:when>
                            <c:when test="${attribut == 'nomMateriel'}">
                                <label for="recherche">
                                    Nom du matériel :&nbsp;
                                    <input type="text" name="recherche" id="recherche">
                                </label>
                                <c:set var="nomFonction" value="TransferTextToText();"/>
                            </c:when>
                            <c:when test="${attribut == 'nomType'}">
                                <label for="recherche">
                                    Type de matériel :&nbsp;
                                    <input type="text" name="recherche" id="recherche">
                                </label>
                                <c:set var="nomFonction" value="TransferTextToText();"/>
                            </c:when>
                        </c:choose>
                    </div>
                    <c:if test="${attribut != 'controleAFaire'}">
                        <div class="layout">
                            <select name ="selectElement" id="selectElement" class="selectElement" onchange="${nomFonction}">
                                <option value="" disabled selected>Séléctionner la recherche</option>
                            </select>
                            <input type="number" min="1" max="1" name="selectPage" id="selectPage" class="selectPage" value="1" onkeypress="return RegexNombrePositif(event)" onblur="VerifPage();" onchange="AjaxListeDeroulanteMateriel();"> / <span id="total">1</span>
                        </div>
                    </c:if>
                    <input type="hidden" name="attribut" id="attribut" value="${attribut}">
                    <div class="layoutButton">
                        <input type="reset" value="Réinitialiser" class="button reset"/> <input type="submit" value="Valider" class="button submit"/> 
                    </div>
                </form>
            </c:when>
            <c:otherwise>
                <span class="margin">Recherche impossible, l'attribut ne correspond à aucune option de recherche.</span>
            </c:otherwise>
        </c:choose>
    </body>
</html>
