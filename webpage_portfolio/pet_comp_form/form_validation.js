window.addEventListener("load", addListeners)

function addListeners() {
	document.getElementById("submit").addEventListener("click", validate)
}

function validate() {
	var re_sound = /\S+\.(mp3|wav)/i;
	var re_pics = /\S+\.(jpg|png|gif)/i;
	var re_date_31_days = /(0[13578]|1[02])\/(0[1-9]|[12]\d|3[01])\/(9[7-9]|0\d|1[0-7])///used for months w/ 31 days
	var re_date_30_days = /(0[469]|11)\/(0[1-9]|[12]\d|30)\/(9[7-9]|0\d|1[0-7])///used for months w/ 30 days
	var re_date_29_days = /(02)\/(0[1-9]|[12]\d)\/(9[7-9]|0\d|1[0-7])///used for months w/ 30 days
	var re_phone = /[2-9]\d\d-[2-9]\d\d-\d{4}/
	var re_username = /[A-z]{5,8}/
	var re_pass_length = /\S{8,}/
	var re_pass_lower = /[a-z]/
	var re_pass_upper = /[A-Z]/
	var re_pass_digit = /\d/
	var re_pass_special = /[~`!@#$%\^&\*]/
	
	if (document.getElementById("sing").checked){
		document.getElementById("sing_title").required = true;
		
		if(re_sound.test(document.getElementById("sing_file").value) === false) {
			
			document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
			
			if(document.getElementById("sing_file").value === ""){
				document.getElementById("sing_file_par").innerHTML = "Please choose a file to upload";
			}
			else {
				document.getElementById("sing_file_par").innerHTML = "Please make sure you have the right file type";
			}
			
		}//end sing_file if
		else {
			document.getElementById("sing_file_par").innerHTML = ""
		}
		
	}//end sing if
	
	if (document.getElementById("cute").checked) {
		
		document.getElementById("cute_title").required = true;
		
		if(re_pics.test(document.getElementById("cute_file1").value) === false){
			
			document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
			
			if(document.getElementById("cute_file1").value === ""){
				document.getElementById("cute_file1_par").innerHTML = "Please choose a picture to upload";
			}
			else {
				document.getElementById("cute_file1_par").innerHTML = "Please make sure you have the right file type"
			}
			
		}//end cute_file1 if
		else {
			document.getElementById("cute_file1_par").innerHTML = ""
		}
		
		
		if(document.getElementById("cute_file2").value !== ""){
			
			if(re_pics.test(document.getElementById("cute_file2").value) === false){
				
				document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
				document.getElementById("cute_file2_par").innerHTML = "Please make sure you have the right file type"
				
			}
			else {
			document.getElementById("cute_file2_par").innerHTML = ""
		}
			
		}//end cute_file2 if
		else {
			document.getElementById("cute_file2_par").innerHTML = ""
		}
		
		if(document.getElementById("cute_file3").value !== ""){
			
			if(re_pics.test(document.getElementById("cute_file3").value) === false){
				
				document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
				document.getElementById("cute_file3_par").innerHTML = "Please make sure you have the right file type"
				
			}
			else {
			document.getElementById("cute_file2_par").innerHTML = ""
		}
			
		}//end cute_file3 if
		else {
			document.getElementById("cute_file3_par").innerHTML = ""
		}
		
	}//end cute if
	
	if(document.getElementById("tricks").checked) {
		
		document.getElementById("tricks_title").required = true;
		document.getElementById("trick_type").required = true;
		
	}//end tricks if
	
	if(document.getElementById("b_day").value === "") {
		
		document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
		document.getElementById("b_day_par").innerHTML = "Please enter your pet's birthday";
		
	}
	else if(re_date_29_days.test(document.getElementById("b_day").value) === false &&
		re_date_30_days.test(document.getElementById("b_day").value) === false && 
		re_date_31_days.test(document.getElementById("b_day").value) === false){
			
			document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
			document.getElementById("b_day_par").innerHTML = "Please make sure your date is formatted correctly"
		
	}
	else {
		document.getElementById("b_day_par").innerHTML = ""
	}//end b_day test
	
	if(re_phone.test(document.getElementById("number").value) === false) {
		
		document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
		
		if(document.getElementById("number").value === ""){
			document.getElementById("number_par").innerHTML = "Please enter your phone number"
		}
		else{
			document.getElementById("number_par").innerHTML = "Please make sure the number is formatted correctly"
		}
		
	}
	else {
		document.getElementById("number_par").innerHTML = ""
	}//end phone number
	
	if(re_username.test(document.getElementById("username").value) === false) {
		
		document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
		
		if(document.getElementById("username").value === ""){
			document.getElementById("username_par").innerHTML = "Please enter a username"
		}
		else{
			document.getElementById("username_par").innerHTML = "Please make sure the username is the right length on consists of only letters"
		}
		
	}
	else {
		document.getElementById("username_par").innerHTML = ""
	}//end phone number
	
	if(document.getElementById("password").value === "") {
		
		document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
		document.getElementById("password_par").innerHTML = "Please enter a password"
		
	}
	else if (re_pass_length.test(document.getElementById("password").value) === false) {
		
		document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
		document.getElementById("password_par").innerHTML = "Your password must be at least 8 characters long"
		
	}
	else {
		
		var num_matches = 0
		
		if (re_pass_lower.test(document.getElementById("password").value) === true) {
			num_matches += 1
		}
		if (re_pass_upper.test(document.getElementById("password").value) === true) {
			num_matches += 1
		}
		if (re_pass_digit.test(document.getElementById("password").value) === true) {
			num_matches += 1
		}
		if (re_pass_special.test(document.getElementById("password").value) === true){
			num_matches += 1
		}
		
		if (num_matches < 3) {
			
			document.getElementById("submit").addEventListener("click", function(event){event.preventDefault()});
			document.getElementById("password_par").innerHTML = "Please make sure your password has at least three of the above required characters"
			
		}
		else {
			document.getElementById("password_par").innerHTML = ""
		}
		
	}//end password
	
}	//end validate