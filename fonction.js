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
























function password(){
    let pageAdmin = document.getElementById("pageAdmin")
    let mot_de_passe = 'ratio';
    pageAdmin.addEventListener("click", function(){
        let mdp = prompt("Entrez le mot de passe pour accéder à la page admin");
        if(mdp == mot_de_passe){
            alert("Mot de passe correct");
            window.location.href = "admin.html";
        }
        else{
            alert("Mot de passe incorrect");
            return;
        }
    }
    )
}


form_button = document.getElementById("go")