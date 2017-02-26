<%@ page pageEncoding="UTF-8" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script src="Template/Default/default.js" type="text/javascript"></script>
        <link rel="stylesheet" href="Template/Default/default.css" type="text/css">
        <link rel="icon" type="image/png" href="Image/icon.png">
        <title>Localisation de matériel</title>
    </head>
    <body>
        <div id="en_tete">
            <jsp:include page="/Template/Default/menu.jsp" flush="false"/>
        </div>
        <div id="corps">
            <c:choose>
                <c:when test="${view != null}">
                    <jsp:include page="${view}" flush="false"/>
                </c:when>
                <c:otherwise>
                    <jsp:include page="/accueil.jsp" flush="false"/>    
                </c:otherwise>
            </c:choose>
        </div>
        <div id="pied_de_page">
            <c:if test="${debutPage != null && finPage != null}">
                <div class="pagination">
                    <span class="barrePagination">
                    <c:choose>
                        <c:when test="${page == debutPage}">
                            <span class="disabled">&Lt;</span>
                            <span class="disabled">&lt;</span>
                        </c:when>
                        <c:otherwise>
                            <a href="?page=${debutPage}${urlPage}">&Lt;</a>
                            <a href="?page=${page-1}${urlPage}">&lt</a>
                        </c:otherwise>
                    </c:choose>
                    <c:forEach var="index" begin="${debutPage}" end="${finPage}">
                        <c:choose>
                            <c:when test="${index == page}">
                                <span class="currentPage">${index}</span>
                            </c:when>
                            <c:otherwise>
                                <a href="?page=${index}${urlPage}">${index}</a>
                            </c:otherwise>
                        </c:choose>
                    </c:forEach>
                    <c:choose>
                        <c:when test="${page == finPage}">
                            <span class="disabled">&gt;</span>
                            <span class="disabled">&Gt;</span>
                        </c:when>
                        <c:otherwise>
                            <a href="?page=${page+1}${urlPage}">&gt</a>
                            <a href="?page=${maxPage}${urlPage}">&Gt;</a>
                        </c:otherwise>
                    </c:choose>
                    </span>
                    <span class="pageNumber">Page : <input type="number" id="pageNumber" min="${debutPage}" max="${maxPage}" value="${page}" onkeypress="return RegexPage(event)" onchange="RedirectionPage('${urlPage}');"> / ${maxPage}</span>
                </div>
            </c:if>
        </div>
    </body>
</html>