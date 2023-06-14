// ------- WRITE FILE -------
function writeFile(id_form,func) {

    var element = document.createElement('a');

    let text1 = document.getElementById(id_form);
    let count = text1.elements.length;
    let textToSave = func;
    for(let i = 0;i<count-1;i++){
        textToSave += ";" + text1[i].value;
    }

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

   // text1.submit();
}
// -------------------------
function exportAllFromRealisateurs(event){ // fonction annexe appelée lorsqu'on appui sur le bouton
    event.preventDefault();

    let doc = document.getElementById("moviesFlex");
    // deleteChildrens(doc);
    writeFile("input1","exportAllFromRealisateurs");
    let text = readFile();

    let array = text.split("\n");

    writeMovies(array, doc);
}

function exportFromDuration(event){// fonction annexe appelée lorsqu'on appui sur le bouton
    event.preventDefault();

    let doc = document.getElementById("moviesFlex");
    writeFile("input2","exportFromDuration");
    let text = readFile();

    let array = text.split("\n");
    writeMovies(array, doc);
    // writeFile("input2", "deleteReady");
}

function exportFromInterval(event) {
    console.log("e");
    event.preventDefault();

    let doc = document.getElementById("moviesFlex");
    writeFile("input5", "exportFromInterval");
    let text = readFile();

    let array = text.split("\n");
    writeMovies(array, doc);
}

//--------------------------
function rechercheliee(){
    writeFile("input6","rechercheliee");
}

// ------- READ FILE -------
function readFileByName(fileName){

    let xhr = new XMLHttpRequest();
    do {
        xhr.open("GET", fileName, false);
        xhr.send(null);

    }while(xhr.status === 404);

    // assumes status 200
    return xhr.responseText;
}

function readFile(){
    readFileByName("ready.txt");
    return readFileByName("result.txt");
}
// -------------------------

function deleteChildrens(doc) {
    while(doc.firstChild) {
        doc.removeChild(doc.firstChild);
    }
}


form_button = document.getElementById("go")




// ----- TEST ------
function waitForDeletedFile(fileName) {
    let xhr = new XMLHttpRequest();
    do {
        xhr.open("GET", fileName, false);
        xhr.send(null);
        console.log("waiting...");
    } while(xhr.status !== 404);

    return;
}



function writeNewMovie(titre, realisateur, duree, genre, save, func) {
    var element = document.createElement('a');

    let textToSave = func;
    textToSave += ";" + titre;
    textToSave += ";" + realisateur;
    textToSave += ";" + duree;
    textToSave += ";" + genre;
    textToSave += ";" + save;

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);
}

function addMovie(event) {
    event.preventDefault();
    let titre = prompt("Entrer le titre du film que vous souhaitez ajouter");
    while (titre == "") {
        titre = prompt("Le titre ne peut pas être null, merci de remplir le champ ci-dessous !");
    }
    let realisateur = prompt("Entrer le nom du réalisateur du film que vous souhaitez ajouter");
    while (realisateur == "") {
        realisateur = prompt("Le réalisateur ne peut pas être null, merci de remplir le champ ci-dessous !");
    }
    let duree = prompt("Entrer la durée du film que vous souhaitez ajouter");
    while (duree == "" || duree != parseInt(duree)) {
        duree = prompt("La durée ne peut pas être null et doit être égal à un nombre entier, merci de remplir le champ ci-dessous !");
    }
    let genre = prompt("Entrer le genre du film que vous souhaitez ajouter");
    while (genre == "") {
        genre = prompt("Le genre ne peut pas être null, merci de remplir le champ ci-dessous !");
    }

    let save = prompt("Souhaitez-vous sauvegarder votre film dans la base de données ? (Y pour oui, sinon non.)");


    writeNewMovie(titre, realisateur, duree, genre, save, "addMovie");
    readFile();
    alert("Votre film a bien été ajouté à la base de données.");
}


function deleteMovie(event) {
    event.preventDefault();

    let doc = document.getElementById("moviesFlex");
    var element = document.createElement('a');
    let textToSave = "exportWholeDB;";
    

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

    let text = readFile();

    let array = text.split("\n");

    writeMoviesForDelete(array, doc);

    // readFile();
}




function password(){
    let pageAdmin = document.getElementById("pageAdmin") //On recupère l'id de la balise permettant d'aller à la page admin
    let mot_de_passe = 'motdepasse'; //definition du mot de passe à entrer pour accéder à la page admin
    let mdp = prompt("Entrez le mot de passe pour accéder à la page admin"); //Lorsuq'on clique sur le logo admin, un prompt nous demande d'entrer le mot de passe
    if(mdp == mot_de_passe){
        alert("Mot de passe correct");
        window.location.href = "admin.html"; //Si le mot de passe est correct, on est redirigé vers la page admin
    }
    else{
        alert("Mot de passe incorrect");
    }
}




function closeServer(){
      writeFile("buttonCloseServer","endServer;")
}

function realisateurPlusDeFilms(event){
    event.preventDefault();
    writeFile("input3","realisateurPlusDeFilms;");
    let text = readFile();

    writeBestRealisators(text);
}

function exportWholeDB(event) {
    event.preventDefault();

    let doc = document.getElementById("moviesFlex");
    writeFile("input4", "exportWholeDB;");
    let text = readFile();

    let array = text.split("\n");
    writeMovies(array, doc);
}