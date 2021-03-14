window.addEventListener('load', function(){
    if( $('#toggle_val').val() == 1){
        $('#toggle_submit').attr('value', 'Automatic');
        //$('#toggle_form').css('background-color','Green');
        $('#toggle_submit').css('background-color','Green');
        $('#text_input').prop('disabled', true);
        $('#text_submit').prop('disabled', true);
        $('#increment').prop('disabled', true);
        $('#decrement').prop('disabled', true);
    }else{
        $('#text_input').prop('disabled', false);
        $('#text_submit').prop('disabled', false);
        $('#increment').prop('disabled', false);
        $('#decrement').prop('disabled', false);
    }
    $('#toggle_submit').on('click', function(e){
        if( e.target.nodeName == 'INPUT')
            e.preventDefault();
        var toggleNode = $('#toggle_val');
        var submit = $('#toggle_submit');
        var form = $(this);
        var value = toggleNode.val();
        if (value == 0){
            value = 1;
            submit.attr('value', 'Automatic');
            //form.css('background-color','Green')
            submit.css('background-color','green');
            $('#text_input').prop('disabled', true);
            $('#text_submit').prop('disabled', true);
            $('#increment').prop('disabled', true);
            $('#decrement').prop('disabled', true);
        }else{
            value = 0;
            submit.attr('value', 'Manual');
            //form.css('background-color','Red')
            submit.css('background-color','Red');
            $('#text_input').prop('disabled', false);
            $('#text_submit').prop('disabled', false);
            $('#increment').prop('disabled', false);
            $('#decrement').prop('disabled', false);
        }
        toggleNode.val(value);
        //console.log(toggleNode.val());    
    });  

    $('#text_form').on('submit', function(e){
        if( $('#toggle_val').val() == 1){
            e.preventDefault();
            alert("You cannot override in automatic mode");
        }
    })

    
});