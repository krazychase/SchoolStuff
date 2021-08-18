// Chase Brown
// Hangman Game

var fs = require('fs');
var readline = require('readline-sync');
var printer = require('./printer');             // User defined
var randomWord = require('./randomWord');       // User defined

function play(words)
{
    var word = randomWord.getRandomWord(words);
    var fails = 0;
    var out = ''
    var correctGuesses = '';

    printer.printTitle();
    for (i=0; i<word.length; i++)
    {
        out = out + '_ ';
    }
    console.log(out);
    console.log(word);

    while (true)
    {
        var guess = readline.question('\nGuess a letter: ').toUpperCase();
        if (word.includes(guess))
        {
            out = ''
            correctGuesses = correctGuesses + guess;
            var win  =  true;
            printer.printGallows(fails, word);
            for (i=0; i<word.length; i++)
            {
                if (correctGuesses.includes(word[i]))
                {
                    out = out + word[i] + ' ';
                } 
                else
                {
                    win = false;
                    out = out + '_ ';
                }
            }
            console.log(out);
            if (win == true)
            {
                printer.winner(word);
                playAgain(words);
            }
        }
        else
        {
            fails++;
            printer.printGallows(fails, word);
            if (fails == 6)
            {
                playAgain(words);
            }
        }
    }
}

function playAgain(words)
{
    var answer = readline.question('Play Again? (Y/N) ');
    if (answer.toUpperCase() == 'Y')
        play(words);
    else if (answer.toUpperCase() == 'N')
        process.exit(0)
    else
        playAgain(words);
}

var data = fs.readFileSync("./dictionary.txt").toString();
var words = data.split("\n");

play(words);
