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
function exportAllFromRealisateurs(){ // fonction annexe appelée lorsqu'on appui sur le bouton
    writeFile("input1","exportAllFromRealisateurs");
}
function exportFromDuration(){// fonction annexe appelée lorsqu'on appui sur le bouton
    writeFile("input2","exportFromDuration"); 
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
    return readFileByName("results.txt");
}
// -------------------------



form_button = document.getElementById("go")




















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
            return;
        }
    }
    )
}


function closeServe(){
    writeFile("buttonCloseServer","endServer");
}





