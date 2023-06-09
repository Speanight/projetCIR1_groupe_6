function main(){
    disabledSearch();
}
main();


function disabledSearch(){
    let input1 = document.getElementById("real");
    let input2 = document.getElementById("time");
    let but = document.getElementById("searchbutton");
    input1.addEventListener('input', toggleSearchButton);
    input2.addEventListener('input', toggleSearchButton);
    but.disabled = true;

    function toggleSearchButton() {
        if (input1.value == NULL && input2.value == NULL) {
            but.disabled = true;
        } else {
            but.disabled = false;
        }
    }
}
