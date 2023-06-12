function main(){
    disabledSearch();
}
main();


function disabledSearch(){
    let input1 = document.getElementById("real");
    let input2 = document.getElementById("time");
    let but1 = document.getElementById("butName");
    let but2 = document.getElementById("butTime");
    let divbut1 = document.getElementById("divbut1");
    let divbut2 = document.getElementById("divbut2");
    input1.addEventListener('input', disabledBut1);
    input2.addEventListener('input', disabledBut2);
    
    
    
    function disabledBut2() {
        if (input2.checkValidity() == false) {  //Vérifie si le format est respecté
            //on remplace le bouton par un icon "interdit"
            but2.innerHTML = '<svg class="send" xmlns="http://www.w3.org/2000/svg" viewBox="0 -960 960 960"><path d="M480-80q-83 0-156-31.5T197-197q-54-54-85.5-127T80-480q0-83 31.5-156T197-763q54-54 127-85.5T480-880q83 0 156 31.5T763-763q54 54 85.5 127T880-480q0 83-31.5 156T763-197q-54 54-127 85.5T480-80Zm0-60q142.375 0 241.188-98.812Q820-337.625 820-480q0-60.662-21-116.831Q778-653 740-699L261-220q45 39 101.493 59.5Q418.987-140 480-140ZM221-261l478-478q-46-39-102.169-60T480-820q-142.375 0-241.188 98.812Q140-622.375 140-480q0 61.013 22 117.507Q184-306 221-261Z"/></svg>';        
        }
        else {
            // on met Search dans le bouton et on l'active si le on format est respecté
            but2.innerHTML = 'Search';
            divbut2.innerHTML = '<button id="butTime" type="submit" name="search2" onclick="exportFromDuration()">Search</button>';
        }
        
    }
    
    function disabledBut1(){    
        if(input1.checkValidity() == false){    //Vérifie si le format est respecté
            //on remplace le bouton par un icon "interdit"
            but1.innerHTML= '<svg class="send" xmlns="http://www.w3.org/2000/svg" viewBox="0 -960 960 960"><path d="M480-80q-83 0-156-31.5T197-197q-54-54-85.5-127T80-480q0-83 31.5-156T197-763q54-54 127-85.5T480-880q83 0 156 31.5T763-763q54 54 85.5 127T880-480q0 83-31.5 156T763-197q-54 54-127 85.5T480-80Zm0-60q142.375 0 241.188-98.812Q820-337.625 820-480q0-60.662-21-116.831Q778-653 740-699L261-220q45 39 101.493 59.5Q418.987-140 480-140ZM221-261l478-478q-46-39-102.169-60T480-820q-142.375 0-241.188 98.812Q140-622.375 140-480q0 61.013 22 117.507Q184-306 221-261Z"/></svg>';
        }
        else{
            // on met Search dans le bouton et on l'active si le on format est respecté
            but1.innerHTML = 'Search';
            divbut1.innerHTML = '<button id="butName" type="submit" name="search1" onclick="exportAllFromRealisateurs()">Search</button>';
        }
    }
}

function writeMovies(movies, doc) {
    while(doc.firstChild) {
        console.log(doc.firstChild);
        doc.removeChild(doc.firstChild);
    }

    console.log(movies);

    for (let i = 0; i < movies.length -1; i++) {
        let movieDetails = movies[i].split(";");

        let flexElement = document.createElement("div");
        flexElement.id = "moviesFlexElement";
        let movie = document.createElement("div");
        movie.id = "movie";

        let titre = document.createElement("p");
        titre.id = "titre";
        titre.innerHTML = movieDetails[0];
        
        let realisateur = document.createElement("p");
        realisateur.id = "realisateur";
        realisateur.innerHTML = movieDetails[1];
        
        let duree = document.createElement("p");
        duree.id = "duree";
        duree.innerHTML = movieDetails[2];
        
        let genre = document.createElement("p");
        genre.id = "genre";
        genre.innerHTML = movieDetails[3];

        doc.appendChild(flexElement);
        flexElement.appendChild(movie);
        movie.appendChild(titre);
        movie.appendChild(realisateur);
        movie.appendChild(duree);
        movie.appendChild(genre);
    }
}