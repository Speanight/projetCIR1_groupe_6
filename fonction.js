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
    console.log("export from realisateurs !");
    writeFile("input1","exportAllFromRealisateurs");
    readFile();
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
    console.log(xhr.responseText);
    return xhr.responseText;
}

function readFile(){
    readFileByName("ready.txt");
    console.log("readFile");
    return readFileByName("result.txt");
}
// -------------------------



form_button = document.getElementById("go")