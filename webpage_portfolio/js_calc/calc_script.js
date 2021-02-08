window.addEventListener("load", addListeners)

function addListeners() {
	//add listeners to nums, ops and decimal
	
	var screen = document.getElementById("calc_screen")
	var buttons = document.getElementsByClassName("buttons")
	var size = buttons.length
	
	for (var i = 0; i < size; i++) {
		//change color on mouseover/out on nums and operation buttons
		buttons[i].addEventListener("mouseover", function(){
			this.style.backgroundColor = "#2DFF09"
		})
		buttons[i].addEventListener("mouseout", function(){
			this.style.backgroundColor = "#24CC07"
		})
		buttons[i].addEventListener("focus", function(){
			this.style.borderColor = "#6FFF55"
		})
		buttons[i].addEventListener("blur", function(){
			this.style.borderColor = "#137F00"
		})
		//button clicks
		buttons[i].addEventListener("click", function(){
			if (screen.value == "ERROR"){
				screen.value = this.value
			}
			else{
				screen.value += this.value
			}
		})
		
	}//end for
	
	//clear function
	document.getElementById("clear").addEventListener("click", function(){
		screen.value = ""
	})
	
	//equals function
	document.getElementById("equals").addEventListener("click", function(){
		screen.value = evaluate()
	})
	
	//square function
	document.getElementById("square").addEventListener("click", function(){
		var temp = evaluate()
		if (temp == "ERROR") {
			screen.value = temp
		}
		else {
			temp *= temp
			screen.value = temp.toFixed(2)
		}
	})
	
	//1/2 function
	document.getElementById("halve").addEventListener("click", function(){
		var temp = evaluate()
		if (temp == "ERROR") {
			screen.value = temp
		}
		else {
			temp /= 2
			screen.value = temp.toFixed(2)
		}
	})
	
	//area function
	document.getElementById("area").addEventListener("click", function(){
		var temp = evaluate()
		if (temp == "ERROR") {
			screen.value = temp
		}
		else {
			temp = temp * temp * 3.14159
			screen.value = temp.toFixed(2)
		}
	})
	
	//colorchanging for other buttons
	var other = document.getElementsByClassName("other")//not number and operation buttons
	var size2 = other.length
	
	for (var i = 0; i < size2; i++){
		other[i].addEventListener("mouseover", function(){
				this.style.backgroundColor = "#2DFF09"
			})
		other[i].addEventListener("mouseout", function(){
			this.style.backgroundColor = "#24CC07"
		})	
		other[i].addEventListener("click", function(){	
			this.style.borderColor = "#6FFF55"
		})
		other[i].addEventListener("focus", function(){
			this.style.borderColor = "#6FFF55"
		})
		other[i].addEventListener("blur", function(){
			this.style.borderColor = "#137F00"
		})
	}//end border change
	
}//end addEventListener

//evaluate function
function evaluate() {
	var temp
	var answer
	try {
		temp = eval(document.getElementById("calc_screen").value)
		answer = temp.toFixed(2)
	}
	catch (ex) {
		answer = "ERROR"
	}
	return answer
}	