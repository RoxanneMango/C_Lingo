let i = 60;
let tries = 5;
let interval;
let isRunning;
let isWon = false;

function lingo_init(){
	get_lingoSize();
	get_lingoBoard();
	get_lingoStats();
}

function startLingo(data){post({"lingo_game":"start"})}
function stopLingo(){post({"lingo_game":"quit"});}
function setLingoSize(data){post({"lingo_size":data});}

async function post(data){
	const response = await fetch("/lingo",{method: 'POST',body: JSON.stringify(data)})
	.then(response => response.text())
	.catch(error => console.log(error));
}

async function get_lingoSize(){
	const response = await fetch("lingo_size",{method: 'GET'})
	.then(response => response.text())
	.then(responseData => {document.getElementById("input").maxLength = responseData;})
	.catch(error => console.log(error));
}

async function get_lingoBoard(){
	const response = await fetch("lingo_board",{method: 'GET'})
	.then(response => response.text())
	.then(responseData => {
		let lingoBoard = "";
		for(i = 0; i < responseData.length; ++i){
			if(responseData[i] == '('){
				lingoBoard += "<ul>";}
			else if(responseData[i] == ')'){
				lingoBoard += "</ul>"}
			else{
				if(responseData[i] == '_'){
					lingoBoard += "<li><div class=\"letter letter_default letter_pending\">" + responseData[i] + "</div></li>";}	
				else if(responseData[i] == '='){
					lingoBoard += "<li><div class=\"letter letter_correct\">";}
				else if(responseData[i] == '?'){
					lingoBoard += "<li><div class=\"letter letter_wrong_place\">";}
				else if(responseData[i] == '!'){
					lingoBoard += "<li><div class=\"letter letter_default\">";}
				else{
					lingoBoard += responseData[i] + "</div></li>";
				}
			}
		}
		document.getElementById("lingo_word").innerHTML = lingoBoard;
	})
	.catch(error => console.log(error));
}

async function get_lingoStats()
{
	const guesses = await fetch("lingo_guesses_remaining",{method: 'GET'})
	.then(guesses => guesses.text())
	.catch(error => console.log(error));
	tries = parseInt(guesses);
	
	const timeSeconds = await fetch("lingo_time_remaining",{method: 'GET'})
	.then(timeSeconds => timeSeconds.text())
	.catch(error => console.log(error));
	i = parseInt(timeSeconds-1);
	
	const runningStatus = await fetch("lingo_is_running",{method: 'GET'})
	.then(runningStatus => runningStatus.text())
	.catch(error => console.log(error));
	
	isRunning = parseInt(runningStatus);
	
	if(isRunning){
		document.getElementById('lingo_stats').innerHTML="tries remaining: <strong>"+tries+"</strong>	|	Time left: <strong>"+i+"</strong>";}
	else{
		if(isWon){
			document.getElementById('lingo_stats').innerHTML = "You won!";}
		else{
			document.getElementById('lingo_stats').innerHTML = "You lost";}
	}
}

async function submitForm(event){
	event.preventDefault();
	let formData = new URLSearchParams(new FormData(document.querySelector('#lingo')));
	let data = {"lingo_guess" : formData.get("input")}

	get_lingoStats();

	if(((formData.get("input").length < document.getElementById("input").maxLength)) || (!isRunning)){
		document.getElementById("input").style.background = "#240000";}
	else{
		let correctLetters = 0;
		document.getElementById("input").style.background = "black";
		const response = await fetch("/lingo", {method: 'POST',body: JSON.stringify(data)})
		.then(response => response.text())
		.then(responseData => {
			let lingoBoard = "";
			for(i = 0; i < responseData.length; ++i){
				if(responseData[i] == '('){
					lingoBoard += "<ul>";}
				else if(responseData[i] == ')'){
					lingoBoard += "</ul>"}
				else{
					if(responseData[i] == '_'){
						lingoBoard += "<li><div class=\"letter letter_default letter_pending\">" + responseData[i] + "</div></li>";}	
					else if(responseData[i] == '='){
						correctLetters += 1;
						lingoBoard += "<li><div class=\"letter letter_correct\">";}
					else if(responseData[i] == '?'){
						lingoBoard += "<li><div class=\"letter letter_wrong_place\">";}
					else if(responseData[i] == '!'){
						lingoBoard += "<li><div class=\"letter letter_default\">";}
					else{
						lingoBoard += responseData[i] + "</div></li>";
					}
				}
			}
			document.getElementById("lingo_word").innerHTML = lingoBoard;
		})
		.catch(error => console.log(error));
		console.log(correctLetters);
		if(correctLetters >= document.getElementById("input").maxLength)
		{
			isWon = true;
		}
		document.getElementById("lingo").reset();
	}
}
function timer(){
	get_lingoStats();
	if(!isRunning){
		clearInterval(interval);}
}