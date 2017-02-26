function TransferTextToText() {
    var selectText = document.getElementById('selectElement').value;
    document.getElementById('recherche').value = selectText;
}

function TransferTextToFrDateFormat(separateur) {
    var type = document.getElementById('recherche').type;
    if (type === "date") { // Si c'est un input date
        var selectText = document.getElementById('selectElement').value;
        // A chaque fois que le caractère rencontré correspond au séparateur
        // le mot est éclaté et donne donc un tableau de sous-mot
        var parts = selectText.split(separateur);
        // Il est impossible d'insérer une date dans un input date
        // si celui ne correspond pas au format yyyy-MM-dd
        var date = parts[2] + "-" + parts[1] + "-" + parts[0];
        document.getElementById('recherche').value = date;
    } else { // Sinon c'est un input text
        TransferTextToText();
    }
}
function AjaxListeDeroulanteMateriel() {
    var selectElement = document.getElementById("selectElement");
    if (selectElement) { // false if null, undefined, NaN, empty, 0 or false
        selectElement.disabled = true;
        /*Objet http permettant "d'éxécuter" une page */
        var http = null;
        if (window.XMLHttpRequest || window.ActiveXObject) {
            if (window.ActiveXObject) {
                try {
                    http = new ActiveXObject("Msxml2.XMLHTTP");
                } catch (e) {
                    http = new ActiveXObject("Microsoft.XMLHTTP");
                }
            } else {
                http = new XMLHttpRequest();
            }
        } else {
            alert("Votre navigateur ne supporte pas l'objet XMLHTTPRequest...");
        }
        if (http !== null) {
            http.onreadystatechange = function()
            {
                if (http.readyState === 4) {
                    if (http.status === 200) {
                        // la page a été exécuté correctement
                        var json = JSON.parse("[" + http.responseText + "]")[0];
                        var selectElement = document.getElementById("selectElement");
                        selectElement.length = 1;
                        document.getElementById("selectPage").max = json[0];
                        document.getElementById("total").innerHTML = json[0];
                        for (var k = 1; k < json.length; k++) {
                            selectElement.options[selectElement.length] = new Option(json[k], json[k], false, false);
                        }
                        selectElement.options[0].selected = true;
                    }
                    selectElement.disabled = false;
                }
            };
            // on spécifie la page à exécuter en passant en post la valeur entré par l'utilisateur 
            var selectPage = document.getElementById("selectPage").value;
            var attribut = document.getElementById("attribut").value;
            http.open("POST", "AjaxListeDeroulanteMateriel", true);
            http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            http.send("attribut=" + attribut + "&page=" + selectPage);
        } else {
            selectElement.disabled = false;
        }
    }
}

function VerifPage() {
    var inputNumber = document.getElementById("selectPage");
    var selectPage = parseInt(inputNumber.value);
    var total = parseInt(document.getElementById("total").innerHTML);
    if (selectPage <= 0 || isNaN(selectPage)) {
        inputNumber.value = 1;
    } else if (selectPage > total) {
        inputNumber.value = total;
    }
}

function RegexNombrePositif(evt) {
    var regex = new RegExp('[0-9]');
    var car = String.fromCharCode(evt.which); // Réccupère le caractère tapé grâce à son code
    if (!regex.test(car)) {
        return false;
    } else {
        return true;
    }
}

function NombrePositif(){
    var recherche = document.getElementById("recherche");
    var nombre = parseInt(recherche.value);
    if (nombre < 0 || isNaN(nombre)) {
        recherche.value = 1;
    }
}