let i = 0;
let tries = 0;
let interval = 0;
let isRunning = 0;
let isWon = false;
let score = 0;
let isReady = true;

async function lingo_init(){
	console.log("INIT!");
	await get_lingoSize();
	await get_lingoBoard();
	await get_lingoTime();
	await get_lingoGuessesRemaining();
	isWon = false;
	isReady = true;
	isRunning = true;
}

function startLingo(data){post({"lingo_game":"start"})}
function stopLingo(){post({"lingo_game":"quit"});}
function setLingoSize(data){post({"lingo_size":data});}
function lingo_isWonAck(){post({"lingo_is_won_ack":"ack"});}

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

async function get_lingoTime(){
	const timeSeconds = await fetch("lingo_time_remaining",{method: 'GET'})
	.then(timeSeconds => timeSeconds.text())
	.catch(error => console.log(error));
	i = parseInt(timeSeconds);
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

async function get_lingoStats(){
	if(!i){
		await get_lingoTime();
	}else{i>0 ? --i : 0;}
	if((i <= 0) || (tries <= 0)){
		get_lingoIsRunning(); }
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

	if(((formData.get("input").length < document.getElementById("input").maxLength)) || (!isRunning)){
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
		await get_lingoGuessesRemaining();
		await get_lingoTime();
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
	
	if(!isRunning){
		clearInterval(interval);}
}