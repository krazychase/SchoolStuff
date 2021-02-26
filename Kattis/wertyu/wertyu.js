// WERTYU Kattis Problem
// Chase  Brown

const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

var keyboard = ['`','1','2','3','4','5','6','7','8','9','0','-','=',
                'Q','W','E','R','T','Y','U','I','O','P','[',']','\\',
                'A','S','D','F','G','H','J','K','L',';',"'",
                'Z','X','C','V','B','N','M',',','.','/'];

function wertyu(data)
{
    var output = ''
    for (var i = 0; i < data.length; i++)
    {
        if (data[i] == ' ')
        {
            output = output + ' ';
        }
        else
        {
            for (var j = 0; j < keyboard.length; j++)
            {
                if (data[i] == keyboard[j])
                {
                    output = output + keyboard[j - 1];
                }
            }
        }
    }
    return output;
}

function solve()
{
    rl.on('line', (line) => {
        var answer = wertyu(line.toUpperCase());
        console.log(answer);
    });
}

if (require.main == module) {
    solve();
}

module.exports = { wertyu: wertyu };