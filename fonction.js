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

    // waitForDeletedFile("request.txt");

    // writeFile("input1", "deleteReady");

    // writeFile("input1", "deleteReady");
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











function password(){
    let pageAdmin = document.getElementById("pageAdmin") //On recupère l'id de la balise permettant d'aller à la page admin
    let mot_de_passe = 'motdepasse'; //definition du mot de passe à entrer pour accéder à la page admin
    pageAdmin.addEventListener("click", function(){ 
        let mdp = prompt("Entrez le mot de passe pour accéder à la page admin"); //Lorsuq'on clique sur le logo admin, un prompt nous demande d'entrer le mot de passe
        if(mdp == mot_de_passe){
            alert("Mot de passe correct");
            window.location.href = "admin.html"; //Si le mot de passe est correct, on est redirigé vers la page admin
        }
        else{
            alert("Mot de passe incorrect");
        }
    }
    )
}




function closeServer(){
      writeFile("buttonCloseServer","endServer;")
}

function realisateurPlusDeFilms(){
    writeFile("input3","realisateurPlusDeFilms;");
}