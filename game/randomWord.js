// Chase Brown
// Random Word Generator for game.js

function getRandomWord(words)
{
    const random = Math.floor(Math.random() * words.length);
    var word = words[random].toUpperCase();
    return word;
}

module.exports = {getRandomWord};