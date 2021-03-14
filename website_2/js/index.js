window.addEventListener('load', function () {
    var toggleForm = document.querySelector('#toggle_form');
    var toggleSubmit = document.querySelector('#toggle_submit');
    var toggleVal = document.querySelector('#toggle_val');
    var textForm = document.querySelector('#text_form');
    var textSubmit = document.querySelector('#text_submit');
    var textInput = document.querySelector('#text_input');
    var increment = document.querySelector('#increment');
    var decrement = document.querySelector('#decrement');
    var inc_form = document.querySelector('#increment_form');
    var dec_form = document.querySelector('#decrement_form');

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
    inc_form.addEventListener('submit', function(e){
        e.preventDefault();
        var increment = document.querySelector('#increment_value');
        var decrement = document.querySelector('#decrement_value');
        var incVal = parseInt(increment.value);
        var decVal = parseInt(decrement.value);
        increment.value = incVal + 1;
        decrement.value = decVal + 1;
    });
    dec_form.addEventListener('submit', function(e){
        e.preventDefault();
        var increment = document.querySelector('#increment_value');
        var decrement = document.querySelector('#decrement_value');
        var incVal = increment.value;
        var decVal = decrement.value;
        increment.value = incVal - 1;
        decrement.value = decVal - 1;
    });
});