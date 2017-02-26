function RedirectionPage(urlPage) {
    var pageNumber = document.getElementById("pageNumber").value;
    window.location.href = "?page="+pageNumber+urlPage;
}

function RegexPage(evt) {
    var regex = new RegExp("[0-9]");
    var car = String.fromCharCode(evt.which); // Réccupère le caractère tapé grâce à son code
    if (!regex.test(car)) {
        return false;
    }
}