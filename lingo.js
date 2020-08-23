let i = 0;
let tries = 0;
let interval = 0;
let isRunning = true;
let isLost = 0;
let isWon = false;
let score = 0;
let isReady = true;

async function lingo_init(){
	await get_lingoSize();
	await get_lingoBoard();
	await get_lingoTime();
	await get_lingoGuessesRemaining();
	await get_lingoIsLost();
	await get_lingoIsWon();
	await get_lingoIsRunning();
//	isWon = false;
	isReady = true;
//	isRunning = true;
//	isLost = false;
}

function startLingo(data){post({"lingo_game":"start"})}
function stopLingo(){post({"lingo_game":"quit"});}
function setLingoSize(data){post({"lingo_size":data});}
function lingo_isWonAck(){post({"lingo_is_won_ack":"ack"});}
function lingo_addName(name){post({"lingo_add_name":name});}

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

async function get_lingoScore(){
	const response = await fetch("lingo_score",{method: 'GET'})
	.then(response => response.text())
	.catch(error => console.log(error));
	score = parseInt(response);
	console.log("score : " + score + "\n");}

async function get_lingoIsLost(){
	const response = await fetch("lingo_is_lost",{method: 'GET'})
	.then(response => response.text())
	.catch(error => console.log(error));
	isLost = parseInt(response);
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

async function get_lingoTime(){
	const timeSeconds = await fetch("lingo_time_remaining",{method: 'GET'})
	.then(timeSeconds => timeSeconds.text())
	.catch(error => console.log(error));
	i = parseInt(timeSeconds);
}

async function get_lingo_high_scores(){
	const response = await fetch("lingo_high_scores",{method: 'GET'})
	.then(response => response.text())
	.catch(error => console.log(error));
	let split_response = response.split(";");
	document.getElementById("lingo_word").innerHTML = "-=- HIGH SCORES -=-</br></br>";
	
	let x = 16;
	let y = 8;
	let isName = true;
	
	console.log("length : " + split_response.length + "\n");
	
	for(let i = 0; i < split_response.length; ++i)
	{
		console.log("length[i] : " + split_response[i].length + "\n");
		for(let j = 0; j < split_response[i].length; ++j)
		{
			if(isName){x -= 1;}
			if(split_response[i][j] == ':')
			{
				isName = false;
				for(let index = x+1; index > 0; --index){document.getElementById("lingo_word").innerHTML += ".";}
				document.getElementById("lingo_word").innerHTML += " : ";		
				for(let index = y - (split_response[i].length - j) + 1; index > 0; --index){document.getElementById("lingo_word").innerHTML += "0";}
			}
			else
			{
				document.getElementById("lingo_word").innerHTML += split_response[i][j];
			}

		}
		document.getElementById("lingo_word").innerHTML += "</br>";
		x = 16;
		y = 8;
		isName = true;
	}
}

async function get_lingoIsRunning(){
	const runningStatus = await fetch("lingo_is_running",{method: 'GET'})
	.then(runningStatus => runningStatus.text())
	.catch(error => console.log(error));
	isRunning = parseInt(runningStatus);
}

async function get_lingoGuessesRemaining(){
	const guesses = await fetch("lingo_guesses_remaining",{method: 'GET'})
	.then(guesses => guesses.text())
	.catch(error => console.log(error));
	tries = parseInt(guesses);	
}

async function get_lingoIsWon(){
	const winStatus = await fetch("lingo_is_won", {method: 'GET'})
	.then(winStatus => winStatus.text())
	.catch(error => console.log(error));
	isWon = parseInt(winStatus);
}

let x = 5;
async function get_lingoStats(){
	if(!i){
		await get_lingoTime();
		x -= 1;
		if(!x)
		{
			isRunning = false;
		}
	}else{i>0 ? --i : 0;x = 10;}
	if((i <= 0) || (tries <= 0)){
		await get_lingoIsLost();}
	if(!isLost){
		document.getElementById('lingo_stats').innerHTML="score : <strong>"+score+"</strong> |	tries remaining: <strong>"+tries+"</strong>	|	Time left: <strong>"+i+"</strong>";}
	else{
		if(!isRunning)
		{
			document.getElementById('lingo_stats').innerHTML = "the game has stopped.";	
		}
		else
		{
			document.getElementById("lingo").removeEventListener("submit", submitForm, true);
			if(score)
			{
				document.getElementById("input").maxLength = 14;
				document.getElementById("lingo").addEventListener("submit", submitHighScore, true);
				
				document.getElementById("lingo_word").innerHTML = "<h1>final score: "+score+"</br>Enter Name:</h1>";
			}
			else
			{
				document.getElementById("lingo").innerHTML = "";
				get_lingo_high_scores();
			}
			document.getElementById('lingo_stats').innerHTML = "The game will automatically deallocate in about a minute.";}
		}
}

async function submitHighScore(event){
	event.preventDefault();
	if(isRunning)
	{
		let formData = new URLSearchParams(new FormData(document.getElementById("lingo")));
		if(!formData.get("input").length){
			document.getElementById("input").style.background = "#240000";}
		else{
			document.getElementById("input").style.background = "black";
			let data = {"lingo_add_name" : formData.get("input")};
			const response = await fetch("/lingo_add_name", {method: 'POST',body: JSON.stringify(data)})
			.then(formData => formData.text())
			.catch(error => console.log(error))
			
			document.getElementById("lingo").removeEventListener("submit", submitHighScore, true);
			document.getElementById("lingo").innerHTML = "";
			isRunning = false;
			
			get_lingo_high_scores();
		}
	}
}

async function submitForm(event){
	event.preventDefault();
	let formData = new URLSearchParams(new FormData(document.querySelector('#lingo')));
	let data = {"lingo_guess" : formData.get("input")};

	if(((formData.get("input").length < document.getElementById("input").maxLength)) || (isLost) || !(isRunning)){
		document.getElementById("input").style.background = "#240000";}
	else{
		//let correctLetters = 0;
		document.getElementById("input").style.background = "black";
		const response = await fetch("/lingo", {method: 'POST',body: JSON.stringify(data)})
		.then(response => response.text())
		.then(responseData => {
			let lingoBoard = "";
			for(let i = 0; i < responseData.length; ++i){
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
						lingoBoard += responseData[i] + "</div></li>";}
				}
			}
			document.getElementById("lingo_word").innerHTML = lingoBoard;
		})
		.catch(error => console.log(error));
		document.getElementById("lingo").reset();
		await get_lingoIsLost();
		await get_lingoScore();
		await get_lingoIsWon();
		if(isWon)
		{
			isReady = false;
			lingo_isWonAck();		
		}
		if(!isReady)
		{
			get_lingoIsWon();
			if(!isWon)
			{
				lingo_init();
			}					
		}
		await get_lingoTime();
		await get_lingoStats();
		await get_lingoGuessesRemaining();
	}
}
async function timer(){
	if(isWon)
	{
		isReady = false;
		lingo_isWonAck();
	}
	if(!isReady)
	{
		get_lingoIsWon();
		if(!isWon)
		{
			lingo_init();
		}		
	}
	else
	{
		await get_lingoStats();	
	}
	if(isLost){
		clearInterval(interval);}
}