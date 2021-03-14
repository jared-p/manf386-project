window.addEventListener('load', function () {
    var toggleForm = document.querySelector('#toggle_form');
    var toggleSubmit = document.querySelector('#toggle_submit');
    var toggleVal = document.querySelector('#toggle_val');
    var textForm = document.querySelector('#text_form');
    var textSubmit = document.querySelector('#text_submit');
    var textInput = document.querySelector('#text_input');
    var increment = document.querySelector('#increment');
    var decrement = document.querySelector('#decrement');

    if (toggleVal.value == 1) {
        toggleSubmit.value = "Automatic";
        toggleSubmit.style.backgroundColor = "green";
        textSubmit.disabled = true;
        textInput.disabled = true;
        increment.disabled = true;
        decrement.disabled = true;
    } else {
        textSubmit.disabled = false;
        textInput.disabled = false;
        increment.disabled = false;
        decrement.disabled = false;
    }
    toggleSubmit.addEventListener('click', function (e) {
        var toggleForm = document.querySelector('#toggle_form');
        var toggleSubmit = document.querySelector('#toggle_submit');
        var toggleVal = document.querySelector('#toggle_val');
        var textForm = document.querySelector('#text_form');
        var textSubmit = document.querySelector('#text_submit');
        var textInput = document.querySelector('#text_input');
        var increment = document.querySelector('#increment');
        var decrement = document.querySelector('#decrement');
        if (e.target.nodeName == 'INPUT')
            e.preventDefault();
        var value = toggleVal.value;
        if (value == 0) {
            value = 1;
            toggleSubmit.value = "Automatic";
            toggleSubmit.style.backgroundColor = "green";
            textSubmit.disabled = true;
            textInput.disabled = true;
            increment.disabled = true;
            decrement.disabled = true;
        } else {
            value = 0;
            toggleSubmit.value = "Manual";
            toggleSubmit.style.backgroundColor = "red";
            textSubmit.disabled = false;
            textInput.disabled = false;
            increment.disabled = false;
            decrement.disabled = false;
        }
        toggleVal.value = value;
    });
    textForm.addEventListener('submit', function(e){
        var toggleVal = document.querySelector('#toggle_val');
        if( toggleVal.value == 1){
            e.preventDefault();
            alert("You cannot override in automatic mode");
        }
    });
});