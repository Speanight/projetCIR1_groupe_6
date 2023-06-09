function main(){
    disabledSearch();
}
main();


function disabledSearch(){
    const realInput = document.getElementById('real');
        const timeInput = document.getElementById('time');
        const searchButton = document.getElementById('searchbutton');

        // Ajoutez des écouteurs d'événements "input" pour les champs d'entrée
        realInput.addEventListener('input', toggleSearchButton);
        timeInput.addEventListener('input', toggleSearchButton);

        // Fonction pour activer ou désactiver le bouton en fonction des champs d'entrée
        function toggleSearchButton() {
            if (realInput.value && timeInput.value) {
                searchButton.disabled = false;
            } else {
                searchButton.disabled = true;
            }
        }
}